#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include "uthreads.h"
#include "Thread.h"
#include <map>
#include <list>
#include <set>

#define MAIN_TID 0
#define ERROR_CODE -1
#define SECOND 1000000

#define EXIT_PROGRAM -1

using std::endl;
using std::cerr;

/** the thread that is currently running */
Thread* currentThread;

/** the main default thread (id no. 0) */
Thread* mainThread;

/** A pointer to a thread that is to be terminated */
Thread* terminatedThread;

/** counter that keeps track of the total number of quantums elapsed*/
int quantumCounter;

/** map that stores every thread that is currently in the thread library */
std::map<int, Thread*> libraryThreads;

/** map that stores every blocked thread that is currently in the thread library */
std::map<int, Thread*> blockedThreads;

/** pointer to the start of the array containing the
 relevant quantum times for each thread priority */
int* quantumArray;

/**
 * the maximum priority that can be assigned to a thread
 */
int maxPriority;

/**
 * queue containing the library's threads in their running order
 */
std::list<Thread*> readyQueue;

/** queue containing TIDs with the smallest
 available TID at the end of the queue */
std::set<int> availableTID;

/**
 * sigset to contain the signals that are to be blocked
*/
sigset_t sigSet;

/** sigaction struct which is used to define
 non-default signal handlers in the code */
struct sigaction sa;

/** timer struct to set and check the
 different threads running times */
struct itimerval timer;

/**
 * Update the timer values according to the current thread
 */
void updateTimer()
{
    int quantum_usecs = currentThread->getQuantum();

    timer.it_value.tv_sec = quantum_usecs / SECOND;
    timer.it_value.tv_usec = quantum_usecs % SECOND;

    timer.it_interval.tv_sec = quantum_usecs / SECOND;
    timer.it_interval.tv_usec = quantum_usecs % SECOND;

    if(setitimer(ITIMER_VIRTUAL, &timer, NULL))
    {
        cerr << "system error: " << "failed to set timer" << endl;
        exit(SYS_CALL_ERROR);
    }
}

/**
 * Delete a thread from the ready queue of the library.
 * return 0 if deletion is successful and -1 otherwise.
 */
int readyQueueDelete(Thread* thread)
{
    std::list<Thread*>::iterator iterator;

    for(auto it = readyQueue.begin(); it != readyQueue.end(); it++)
    {
        if(*it == thread)
        {
            iterator = it;
            readyQueue.erase(it);

            return EXIT_SUCCESS;
        }
    }

    return ERROR_CODE;
}

/**
 * Custom signal masker (specifically for the SIGVTALRM signal)
 */
void unmaskSignals()
{
    if(sigprocmask(SIG_UNBLOCK, &sigSet, NULL))
    {
        cerr << "sigprocmask failed" << endl;
        exit(SYS_CALL_ERROR);
    }
}

/**
 * Custom signal un-masker (specifically for the SIGVTALRM signal)
 */
void maskSignals()
{
    if(sigprocmask(SIG_BLOCK, &sigSet, NULL))
    {
        cerr << "sigprocmask failed" << endl;
        exit(SYS_CALL_ERROR);
    }
}

void deleteLibrary()
{
    // clear all of the library's data structures
    blockedThreads.clear();
    readyQueue.clear();

    for(auto it = libraryThreads.begin(); it != libraryThreads.end(); it++)
    {
        if(it->first != MAIN_TID) // delete all threads except main thread
        {
            delete it->second;
            it = libraryThreads.erase(it); // increase iterator upon deletion to prevent Seg-Fault
        }
    }

    libraryThreads.erase(MAIN_TID); // delete main thread
    delete mainThread;

    exit(EXIT_SUCCESS);
}

/**
 * Implementation of the Round-Robin timing
 * algorithm as described in the exercise
 */
void roundRobin()
{
    maskSignals();
    quantumCounter++; // update the global quantum counter

    int ret_val = sigsetjmp(currentThread->getEnvironment(),1);

    maskSignals(); // in case returning from siglongjmp

    if(ret_val == EXIT_PROGRAM) // Terminate library
    {
        deleteLibrary();
    }

    else if(ret_val != 0) // in case a thread termination was initiated
    {
        if(terminatedThread != nullptr)
        {
            availableTID.insert(terminatedThread->getID());
            libraryThreads.erase(terminatedThread->getID());

            delete terminatedThread; // terminate thread
            terminatedThread = nullptr;
        }

        unmaskSignals();
        return;
    }

    // Set next thread in queue as the running thread
    if(!readyQueue.empty())
    {
        // if current thread was not blocked or terminated
        if(currentThread->getState() == RUNNING && terminatedThread == nullptr)
        {
            readyQueue.push_back(currentThread);
            currentThread->setState(READY);
        }

        currentThread = readyQueue.front();
        readyQueue.pop_front();

        currentThread->setState(RUNNING);
    }

    if(sigemptyset(&sigSet)) // delete pending signals
    {
        cerr << "system error: " << "sigemptyset failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    if(sigaddset(&sigSet, SIGVTALRM))
    {
        cerr << "system error: " << "sigaddset failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    unmaskSignals();
    updateTimer(); // start timer with the relevant times for this thread

    currentThread->increaseQuantum(); // start the quantum count for current thread
    
    siglongjmp(currentThread->getEnvironment(), 1);
}

/**
 * Custom handler for the SIGVTALRM signal
 */
void timer_handler(int sigNum)
{
    if(sigNum == SIGVTALRM)
    {
        maskSignals();
        roundRobin(); //switch to the next ready thread using the scheduler
    }
}

/**
 * Initialize the tid queue by inserting all
 * potential tid's in ascending order
 * @return 0 on exit
 */
int tidQueue_init()
{
    for(int i = 1; i <= MAX_THREAD_NUM; i++)
    {
        availableTID.insert(i);
    }

    return EXIT_SUCCESS;
}

/**
 * Use the TID queue to pop the next smallest
 * available TID. if the queue is empty, return -1.
 */
int popAvailableID()
{
    if(availableTID.empty())
    {
        return ERROR_CODE;
    }

    int tid = *availableTID.begin();
    availableTID.erase(tid);

    return tid;
}

/**
 * Description: This function initializes the thread library.
 * You may assume that this function is called before any other thread library
 * function, and that it is called exactly once. The input to the function is
 * an array of the length of a quantum in micro-seconds for each priority.
 * It is an error to call this function with an array containing non-positive integer.
 * size - is the size of the array.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_init(int *quantum_usecs, int size)
{
    // assert the validity of the given function arguments
    if(size >= 1) // check if size is valid
    {
        for(int i = 0; i < size; i++)
        {
            if (quantum_usecs[i] <= 0) // check if each quantum value is valid
            {
                cerr << "thread library error: " << "bad argument" << endl;
                return ERROR_CODE;
            }
        }
    }
    else
    {
        cerr << "thread library error: " << "bad argument" << endl;
        return ERROR_CODE;
    }

    quantumArray = quantum_usecs;
    maxPriority = size - 1;

    try
    {
        mainThread =  new Thread(MAIN_TID, quantumArray[MAIN_TID]);
    }
    catch(std::bad_alloc & e) // in case of bad alloc
    {
        cerr << "system error: " << "Memory alloc failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    libraryThreads.insert(std::pair<int, Thread*>(MAIN_TID, mainThread));

    currentThread = mainThread;
    currentThread->setState(RUNNING);

    //initialize the TID queue
    tidQueue_init();
    sa = {0};

    if(sigemptyset(&sigSet))
    {
        cerr << "system error: " << "sigemptyset failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    sa.sa_handler = &timer_handler;

    //define the thread timer and handler for SIGVTALRM
    if(sigaddset(&sigSet, SIGVTALRM))
    {
        cerr << "system error: " << "sigaddset failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    if(sigaction(SIGVTALRM, &sa, NULL))
    {
        cerr << "system error: " << "sigaction failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    updateTimer();

    if(setitimer(ITIMER_VIRTUAL, &timer, NULL))
    {
        cerr << "system error: " << "failed to set timer" << endl;
        exit(SYS_CALL_ERROR);
    }

    roundRobin();

    return EXIT_SUCCESS;
}

/**
 * Description: This function creates a new thread, whose entry point is the
 * function f with the signature void f(void). The thread is added to the end
 * of the READY threads list. The uthread_spawn function should fail if it
 * would cause the number of concurrent threads to exceed the limit
 * (MAX_THREAD_NUM). Each thread should be allocated with a stack of size
 * STACK_SIZE bytes.
 * priority - The priority of the new thread.
 * Return value: On success, return the ID of the created thread.
 * On failure, return -1.
*/
int uthread_spawn(void (*f)(), int priority)
{
    maskSignals();

    if(libraryThreads.size() >= MAX_THREAD_NUM
    || priority > maxPriority || priority < 0)
    {
        cerr << "thread library error: " << "Thread library full or bad priority no." << endl;
        return ERROR_CODE;
    }

    Thread* nextThread;
    int tid = popAvailableID();

    try
    {
        nextThread = new Thread(tid, quantumArray[priority], f);
    }
    catch(std::bad_alloc & e) // in case of bad alloc
    {
        cerr << "system error: " << "Memory alloc failed" << endl;
        exit(SYS_CALL_ERROR);
    }

    libraryThreads.insert(std::pair<int, Thread*>(tid, nextThread));
    readyQueue.push_back(nextThread);

    unmaskSignals();

    return tid;
}

/**
 * Description: This function changes the priority of the thread with ID tid.
 * If this is the current running thread, the effect should take place only the
 * next time the thread gets scheduled.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_change_priority(int tid, int priority)
{
    maskSignals();

    // in case the thread ID is not in the library or bad priority #
    if(libraryThreads.count(tid) == 0 ||
    priority > maxPriority || priority < 0)
    {
        cerr << "thread library error: " << "Thread not in library or bad priority no." << endl;
        return ERROR_CODE;
    }

    libraryThreads.find(tid)->second->setQuantum(quantumArray[priority]);
    unmaskSignals();

    return EXIT_SUCCESS;
}

/**
 * Description: This function terminates the thread with ID tid and deletes
 * it from all relevant control structures. All the resources allocated by
 * the library for this thread should be released. If no thread with ID tid
 * exists it is considered an error. Terminating the main thread
 * (tid == 0) will result in the termination of the entire process using
 * exit(0) [after releasing the assigned library memory].
 * Return value: The function returns 0 if the thread was successfully
 * terminated and -1 otherwise. If a thread terminates itself or the main
 * thread is terminated, the function does not return.
*/
int uthread_terminate(int tid)
{
    maskSignals();

    // in case the thread ID is not in the library
    if(libraryThreads.count(tid) == 0)
    {
        cerr << "thread library error: " << "Thread not in library" << endl;
        return ERROR_CODE;
    }

    Thread *thread = (*libraryThreads.find(tid)).second;

    if(thread == mainThread) // in case thread is ready
    {
        siglongjmp(mainThread->getEnvironment(), EXIT_PROGRAM); // switch to main thread,delete and exit library
    }

    if(thread->getState() == READY) // in case thread is ready
    {
        readyQueueDelete(thread);
        libraryThreads.erase(tid); // delete thread from library
    }

    else if(thread->getState() == BLOCKED) // in case thread is blocked
    {
        blockedThreads.erase(tid);
        libraryThreads.erase(tid); // delete thread from library
    }

    else if(thread->getState() == RUNNING) // in case thread is current thread
    {
        terminatedThread = currentThread;

        roundRobin(); // call the scheduler to switch threads
    }

    availableTID.insert(tid);
    unmaskSignals();

    return EXIT_SUCCESS;
}

/**
 * Description: This function blocks the thread with ID tid. The thread may
 * be resumed later using uthread_resume. If no thread with ID tid exists it
 * is considered as an error. In addition, it is an error to try blocking the
 * main thread (tid == 0). If a thread blocks itself, a scheduling decision
 * should be made. Blocking a thread in BLOCKED state has no
 * effect and is not considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_block(int tid)
{
    maskSignals();

    // in case the thread ID is not in the library or tid is 0
    if(libraryThreads.count(tid) == 0 || tid == MAIN_TID)
    {
        cerr << "thread library error: " << "Thread not in library or not allowed to access" << endl;
        return ERROR_CODE;
    }

    Thread *thread = libraryThreads.find(tid)->second;

    if(thread->getState() == READY) // in case thread is ready
    {
        readyQueueDelete(thread);
        blockedThreads.insert(std::pair<int, Thread*>(tid, thread));
        thread->setState(BLOCKED);

        return EXIT_SUCCESS;
    }

    if(thread->getState() == RUNNING) // in case thread is the current one
    {
        currentThread->setState(BLOCKED);
        blockedThreads.insert(std::pair<int, Thread*>(tid, thread));

        roundRobin(); // call the scheduler to switch threads
    }

    unmaskSignals();

    return EXIT_SUCCESS;
}

/**
 * Description: This function resumes a blocked thread with ID tid and moves
 * it to the READY state if it's not synced. Resuming a thread in a RUNNING or READY state
 * has no effect and is not considered as an error. If no thread with
 * ID tid exists it is considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_resume(int tid)
{
    maskSignals();

    // in case the thread ID is not in the library
    if(libraryThreads.count(tid) == 0)
    {
        cerr << "thread library error: " << "Thread not in library" << endl;
        return ERROR_CODE;
    }

    // In case the thread is blocked
    if(blockedThreads.count(tid) > 0)
    {
        Thread *thread = blockedThreads.find(tid)->second;
        readyQueue.push_back(thread);

        blockedThreads.erase(tid);
        thread->setState(READY);
    }

    unmaskSignals();

    return EXIT_SUCCESS;
}

/**
 * Description: This function returns the thread ID of the calling thread.
 * Return value: The ID of the calling thread.
*/
int uthread_get_tid()
{
    return currentThread->getID();
}

/**
 * Description: This function returns the total number of quantums since
 * the library was initialized, including the current quantum.
 * Right after the call to uthread_init, the value should be 1.
 * Each time a new quantum starts, regardless of the reason, this number
 * should be increased by 1.
 * Return value: The total number of quantums.
*/
int uthread_get_total_quantums()
{
    return quantumCounter;
}

/**
 * Description: This function returns the number of quantums the thread with
 * ID tid was in RUNNING state. On the first time a thread runs, the function
 * should return 1. Every additional quantum that the thread starts should
 * increase this value by 1 (so if the thread with ID tid is in RUNNING state
 * when this function is called, include also the current quantum). If no
 * thread with ID tid exists it is considered an error.
 * Return value: On success, return the number of quantums of the thread with ID tid.
 * On failure, return -1.
*/
int uthread_get_quantums(int tid)
{
    maskSignals();

    // in case the thread ID is not in the library
    if(libraryThreads.count(tid) == 0)
    {
        cerr << "thread library error: " << "Thread not in library" << endl;
        return ERROR_CODE;
    }

    unmaskSignals();
    return libraryThreads.find(tid)->second->getQuantumCount();
}