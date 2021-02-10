#include <algorithm>
#include <cmath>
#include "PhysicalMemory.h"

void clearTable(uint64_t frameIndex)
{
    for (uint64_t i = 0; i < PAGE_SIZE; ++i)
    {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

/**
 * Initialize the virtual memory
 */
void VMinitialize()
{
    clearTable(0);
}

/**
 * This function traverses through the frame tree, looking for the parent
 * of f that was given as an argument and deletes it's reference to frame
 */
void remove_reference(word_t predecessorFrame, int depth, word_t f)
{
    word_t frame_index; // The current frame index

    for(int i = 0; i < PAGE_SIZE; i++)
    {
        PMread(predecessorFrame * PAGE_SIZE + i, &frame_index); // Read the current index entry

        if(frame_index == f)
        {
            PMwrite(predecessorFrame * PAGE_SIZE + i, 0);
            return;
        }

        if(frame_index > 0 && depth < TABLES_DEPTH - 1)
            remove_reference(frame_index, depth + 1, f);

    } // Find the desired frame and remove the reference from it's parent
}

/**
 * This function returns the cyclical
 * distance of page p2 from page p1
 */
int cyclicalDistance(uint64_t p1, uint64_t p2)
{
    return std::min((word_t)NUM_PAGES - abs(p1 - p2),
                    abs(p1 - p2));
}

/**
 * Evicts a page from the physical memory, then
 * returns it's frame's index for further usage.
 * @param virtualAddress Potential page's virtualAddress according to tree path
 * @param f An already found Frame with the maximal cyclical distance from
 */
void evict_frame(word_t predecessorFrame, int depth, uint64_t virtualAddress,
                 word_t& f, uint64_t& p, uint64_t page_swapped_in)
{
    word_t frame_index; // The current frame index

    for(int i = 0; i < PAGE_SIZE; i++)
    {
        PMread(predecessorFrame * PAGE_SIZE + i, &frame_index); // Read the current index entry

        if(depth == TABLES_DEPTH - 1 && frame_index!=0)// Upon reaching a leaf, check cyclical distance
        {
            if(f == 0 || (cyclicalDistance(page_swapped_in,virtualAddress + i) > cyclicalDistance(page_swapped_in, p)))
            {
                f = frame_index;
                p = virtualAddress + i;
            }
        } // Update f if a frame with better cyclical distance is found
        if(frame_index > 0 && depth < TABLES_DEPTH - 1)
            evict_frame(frame_index, depth + 1,
                        virtualAddress + i*pow(PAGE_SIZE, TABLES_DEPTH - (depth+1)), f, p, page_swapped_in);



    } // Keep track of maximal frame visited during DFS traversal
}

/**
 * Find the index of the first empty frame in the, other than f, which
 * resides in the physical memory. If there isn't one, return NUM_FRAMES.
 */
word_t find_empty_frame(word_t predecessorFrame, int depth, word_t f)
{
    word_t frame_index; // The current frame index
    word_t min_index = NUM_FRAMES; // The minimal empty frame index that was accessed during DFS

    int emptyRows = 0; // A counter for the empty rows in predecessorFrame

    for(int i = 0; i < PAGE_SIZE; i++)
    {
        PMread(predecessorFrame * PAGE_SIZE + i, &frame_index); // Read the current index entry

        if(frame_index > 0 && depth < TABLES_DEPTH - 1)
            min_index = std::min(min_index, find_empty_frame(frame_index, depth + 1, f));
        else if (frame_index == 0)
            emptyRows++;
        if(emptyRows == PAGE_SIZE && predecessorFrame != f)
            min_index = predecessorFrame; // If all of the rows are empty, frame answers the criteria
    }

    return min_index;
}

/**
 * Find the index of the first unused available frame in the
 * physical memory. If there isn't one, return NUM_FRAMES.
 */
word_t find_unused_frame(word_t predecessorFrame, int depth)
{
    word_t frame_index; // The current frame index
    word_t max_index = 0; // The maximal frame index that was accessed during DFS

    for(int i = 0; i < PAGE_SIZE; i++)
    {
        PMread(predecessorFrame * PAGE_SIZE + i, &frame_index); // Read the current index entry

        (frame_index > max_index) ? max_index = frame_index : max_index = max_index;

        max_index = (frame_index > 0 && depth < TABLES_DEPTH - 1) ?
                    std::max(max_index, find_unused_frame(frame_index, depth + 1) - 1) : max_index;
    } // Keep track of maximal frame visited during DFS traversal

    return max_index + 1;
}

/**
 * Get the virtual memory page index in which this address resides
 */
word_t getPage(uint64_t virtualAddress)
{
    return virtualAddress / PAGE_SIZE;
}

/**
 * This function sets the frame_index with a valid available frame from the physical memory.
 * If the initial frame index value is valid, returns false. Otherwise looks for a valid index and
 * evicts a page from the physical memory (if necessary) in order to do so and finally returns true.
 */
bool authenticateFrame(word_t& frame_index, word_t predecessor_index, uint64_t page_swapped_in)
{
    if(frame_index != 0) // In case frame index is already valid
        return false;

    frame_index = find_empty_frame(0, 0, predecessor_index); // Find minimal empty frame

    if(frame_index < NUM_FRAMES)
    {
        clearTable(frame_index);
        remove_reference(0, 0, frame_index);
        return true; // Clear the empty frame, remove it's parent reference and return
    }

    frame_index = find_unused_frame(0, 0); // Find minimal unused frame

    if(frame_index < NUM_FRAMES)
    {
        clearTable(frame_index);
        return true; // Clear the unused frame and return
    }

    else // Else, evict a page
    {
        frame_index = 0;
        uint64_t evictedPageIndex = 0; // The variable to contain the page that should be evicted

        evict_frame(0, 0, 0,
                    frame_index, evictedPageIndex, page_swapped_in);
        PMevict(frame_index, evictedPageIndex);
        clearTable(frame_index);
        remove_reference(0, 0, frame_index);
    }

    return true; // Evict a page, Clear it's frame, remove it's parent reference and return
}

/**
 * convert the given virtual address to a corresponding physical address
 */
uint64_t virtualToPhysical(uint64_t virtualAddress)
{
    word_t predecessorFrame = 0; // The predecessor frame of a given node in frame tree
    word_t frame_index = 0; // The current frame index

    uint64_t layerOffSet[TABLES_DEPTH + 1];
    uint64_t page_swapped_in = getPage(virtualAddress); // The address's page index

    for (int i = 0; i <= TABLES_DEPTH; i++)
    {
        layerOffSet[TABLES_DEPTH - i] = virtualAddress % PAGE_SIZE;
        virtualAddress = virtualAddress / PAGE_SIZE;
    } // Array containing the appropriate offset for each layer

    for(int i = 0; i < TABLES_DEPTH; i++) // Iterate through the layers of the frame tree
    {
        PMread(predecessorFrame * PAGE_SIZE + layerOffSet[i], &frame_index);

        if(authenticateFrame(frame_index, predecessorFrame, page_swapped_in))
            PMwrite(predecessorFrame * PAGE_SIZE + layerOffSet[i], frame_index);
        // Checks if a frame allocation is needed, and updates frame value accordingly

        if(i == TABLES_DEPTH - 1) // Insert corresponding page to the leaf frame
            PMrestore(frame_index, page_swapped_in);

        predecessorFrame = frame_index;
    }

    return frame_index * PAGE_SIZE + layerOffSet[TABLES_DEPTH];
}

/** reads a word from the given virtual address
 * and puts its content in *value.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMread(uint64_t virtualAddress, word_t* value)
{
    if(virtualAddress >= VIRTUAL_MEMORY_SIZE || (int) virtualAddress < 0)
        return 0; // If address exceeds the legal MEM space

    PMread(virtualToPhysical(virtualAddress), value);
    return 1;
}

/** writes a word to the given virtual address
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMwrite(uint64_t virtualAddress, word_t value)
{
    if(virtualAddress >= VIRTUAL_MEMORY_SIZE || (int) virtualAddress < 0)
    {
        return 0; // If address exceeds the legal MEM space
    }

    PMwrite(virtualToPhysical(virtualAddress), value);
    return 1;
}