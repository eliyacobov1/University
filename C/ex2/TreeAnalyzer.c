#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

#define MAX_LINE 1024
#define DELIMITERS "  \t\r\n"
#define HYPHEN "-"
#define MEMORY_ERROR -1

static const char *tree_msg =
        "The given graph is not a tree\n";

static const char *invalid_msg =
        "Invalid input\n";

static const char *args_msg =
        "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n";

static const char *mem_msg =
        "Memory allocation failed\n";

//clock variable for the DFS algorithm
static int clock = 0;

/**
 * define a struct for a node which represents a vertex in a graph
 */

typedef struct node
{
    //key number of the node
    int key;
    //degree of the node
    int degree;
    //parent of the node (if existent)
    struct node *parent;
    //array of pointers to node's sons
    struct node **sons;
    //boolean value indication for
    // if node is root of graph
    int is_root;
    //used in DFS
    int visited;
    //used in DFS
    int pre;
    //used in DFS
    int post;
    //used in BFS
    double distance;
    //used in BFS
    struct node *previous;
} Node ;

/**
 * define a struct for a graph (any graph, not necessarily a tree)
 */

typedef struct
{
    Node *root;
    int V;
    Node **vertex_list;
    int Min;
    int Max;
    int diameter;
} Graph;

/**
 * a function that creates a new Node
 * @param number number that the Node is represented by
 * @param degree the degree of the Node
 * @param sons pointer to an array of the nodes that
 * are adjacent to the given node
 * @return a pointer to the newly created Node
 */

static Node* newNode(int number)
{
    Node *node = (Node*)malloc(sizeof(Node));

    node->key = number;
    node->degree = 0;
    node->parent = (Node*)malloc(sizeof(Node));
    //indication that no other parent was set
    node->parent->key = -1;
    (node->sons) = (Node**)malloc(sizeof(Node*));
    *(node->sons) = NULL;
    node->is_root = 1;
    node->previous =(Node*)malloc(sizeof(Node));

    return node;
}

/**
 * A function that creates a new Graph
 * @param Root the root node of the Graph
 * @param V Number of vertices(nodes) in the graph
 * @param E Number of edges in the graph
 * @return A pointer to the newly created Graph
 */

static Graph* newGraph(int V)
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    graph->root = NULL;
    graph->V = V;
    graph->vertex_list = NULL;
    graph->Min = 0;
    graph->Max = 0;

    return graph;
}

/**
 * Free allocated memory for Node pointer array
 * @param ptr Pointer to pointer to the dynamically allocated memory
 */

void freeNode(Node ***ptr)
{
    free(*ptr);
    *ptr = NULL;
}

/**
 * Helper function for DFS Algorithm
 * @param v Node in the graph
 */

void preVisit(Node *v)
{
    v->pre = clock;
    clock ++;
}

/**
 * Helper function for DFS Algorithm
 * @param v Node in the graph
 */

void postVisit(Node *v)
{
    v->post = clock;
    clock ++;
}

/**
 * Helper function for DFS Algorithm
 * @param v Node in the graph
 * @param g Pointer to the graph
 */

void explore(Graph *g, Node *v)
{
    v->visited = 1;
    preVisit(v);

    for(int i = 0; i < v->degree; i++)
    {
        //if node has a parent, traverse that parent
        if (i == (v->degree - 1))
        {
            if (v->parent)
            {
                if(!v->parent->visited)
                {
                    explore(g, v->parent);
                }
                continue;
            }
        }
        Node *w = v->sons[i];
        if(!w->visited)
        {
            explore(g, w);
        }
    }
    postVisit(v);
}

/**
 * DFS Algorithm that traverses through all the vertices in the
 * given graph and sets their pre, post data so that conclusions
 * on the graph would be later understood
 * @param g the graph
 */

void DFS(Graph *g)
{
    for (int v = 0; v < g->V; v++ )
    {
        g->vertex_list[v]->visited = 0;

    }
    //set clock to 0 prior to DFS traversal
    clock = 0;

    explore(g, g->root);
}

/**
 * BFS algorithm that gets a starting node and find's the distance
 * of all the
 * @param g The graph
 * @param s Start vertex
 */

void BFS(Graph *g, Node *s)
{
    for(int i = 0; i < g->V; i++)
    {
        g->vertex_list[i]->distance = INFINITY;
    }
    s->distance = 0;
    s->previous = NULL;

    Queue *q = allocQueue();
    //enqueue key of s
    enqueue(q, s->key);

    while(!queueIsEmpty(q))
    {
        int key = (int)dequeue(q);
        Node *u = g->vertex_list[key];

        for(int i = 0; i < u->degree; i++)
        {
            //if there is a parent, iterate over it
            if (i == u->degree-1)
            {
                 if(u->parent)
                {
                    Node *w = (u->parent);

                    if(w->distance == INFINITY)
                    {
                        enqueue(q, w->key);
                        w->previous = u;
                        w->distance = (u->distance) + 1;
                    }

                    continue;
                }
            }
            Node *w = (u->sons[i]);

            if(w->distance == INFINITY)
            {
                enqueue(q, w->key);
                w->previous = u;
                w->distance = (u->distance) + 1;
            }
        }
    }
}

/**
 * Function that uses BFS and sets Minimum and Maximum height
 * of the given tree graph
 * @param g A tree graph (function will be used only after asserting
 * that the graph is indeed a tree).
 */

void findHeight(Graph *g)
{
    BFS(g, g->root);

    int max_height = 0;
    int min_height = 0;

    for(int i = 0; i < g->V; i++)
    {
        Node *v = g->vertex_list[i];
        //check if we reached a leaf
        if (!v->sons)
        {
            if (v->distance < min_height && v->distance > 0)
            {
                min_height = (int) g->vertex_list[i]->distance;
            }

            if(g->vertex_list[i]->distance > max_height)
            {
                max_height = (int) g->vertex_list[i]->distance;
            }
        }
    }

    g->Max = max_height;
    g->Min = min_height;
}

/**
 * Function that uses BFS and sets Diameter of the given tree graph
 * @param g A tree graph (function will be used only after asserting
 * that the graph is indeed a tree).
 */

void findDiam(Graph *g)
{
    int *max_heights = (int*)malloc(g->V * sizeof(int));

    for(int i = 0; i < g->V; i++)
    {
        Node *v = g->vertex_list[i];
        //for each vertex Run BFS, find max distance, and
        //set it as the i'th value in max_heights
        BFS(g, v);
        {
            for (int j = 0; j < g->V; j++)
            {
                Node *u = g->vertex_list[j];
                if (u->distance > max_heights[i] && u != v)
                {
                    max_heights[i] = (int) g->vertex_list[i]->distance;
                }
            }
        }
    }

    int diameter = 0;
    //set delimiter as max value of the array
    for(int i = 0; i < g->V; i++)
    {
        if(max_heights[i] > diameter)
        {
            diameter = max_heights[i];
        }
    }

    //free the memory allocated for max_heights
    int **ptr = &max_heights;
    free(*ptr);
    *ptr = NULL;

    g->diameter = diameter;
}

/**
 * Finds and prints the shortest path
 * between the two given vertices in the graph
 * (represented  by their keys)
 * @param u key of first vertex
 * @param v key of second vertex
 * @param g The Graph
 */

void printPath(Graph *g, int u, int v)
{
    BFS(g, g->vertex_list[u]);

    int distance = (int)g->vertex_list[v]->distance;
    Node *previous;
    int *values = (int*)malloc((distance + 2) * sizeof(int));
    values[0] = v;
    Node *current = g->vertex_list[v];

    //store path values using the BFS data
    for(int i = 1; i <= distance ; i++)
    {
        previous = current->previous;
        values[i] = previous->key;
        current = previous;
    }
    values[distance + 2] = u;

    //print the path
    for(int i = distance + 2; i >= 0 ; i--)
    {
        printf("%d ", values[i]);
    }

    //free the pointer "values"
    int **ptr = &values;
    free(*ptr);
    *ptr = NULL;
}

/**
 * Function that checks if graph is connected and contains no circles.
 * If both conditions apply, the graph is a tree (Also runs DFS algorithm
 * on the graph)
 * @param G The given graph to check.
 * @return 1 if graph is a tree, 0 otherwise.
**/

int isTree(Graph *g)
{
    DFS(g);

    //for each edge in the graph, look for
    // a circle using the results of the DFS run
    for (int v = 0; v < g->V; v++ )
    {
        Node *u = (g->vertex_list[v]);
        //if there's a non-visited vertex, graph
        // is not connected and therefore no a tree
        if(!u->visited)
        {
            return 0;
        }
        for(int i = 0; i < u->degree; i++)
        {
            //if node has a parent, check condition for that parent
            if (i == u->degree-1)
            {
                if(u->parent)
                {
                    Node *w = u->parent;

                    if(u->pre < w->pre && w->pre < w->post
                       && w->post < u->post)
                    {
                        return 0;
                    }
                    continue;
                }
            }

            Node *w = u->sons[i];
            if(w->pre < u->pre && u->pre < u->post
               && u->post < w->post)
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Iterate through the graph's vertexes and in case it is a tree,
 * find which vertex is the root (using the is_root attribute which was
 * already set) if more than one root was found, set root to NULL
 * @param g A pointer to the graph
 */

void setRoot(Graph *g)
{
    for(int i = 0; i< g->V; i++)
    {
        //look for a vertex that dose'nt have a parent
        //and set it as a root
        if(g->vertex_list[i]->is_root)
        {
            g->root = g->vertex_list[i];
            return;
        }
    }
}

/**
 * checks if the given number is a natural number (or 0)
 * @param number the number to check
 * @return int value of the number if number is natural,
 * -1 otherwise
 */

static int isNatural(const char *number)
{
    char *ptr;
    double d = strtod(number, &ptr);

    //check if conversion was successful
    if(number != ptr && d >= 0)
    {
        if(floor(d) == d)
        {
            return (int)d;
        }
    }
    return -1;
}

/**
 * check if given value can be a vertex representation
 * in the given graph
 * @param value The value to check
 * @param length The length of the value char array
 * @param graph The graph that it should fit as a vertex
 * @return The value in int if valid, -1 otherwise
 */

static int parseValue(char *value, Graph *g)
{
    //asserts that the number is natural and is a legal vertex
    // representation and returns it. If not, returns -1.
    int num = isNatural(value);
    if (num == -1 || num > g->V - 1)
    {
        return -1;
    }

    return num;
}

/**
 * Converts file to a graph struct
 * @param Filepath The path of the file
 * @param graph A graph ptr to assign the file values to
 * @return EXIT_SUCCESS if file is not empty and valid input.
 * EXIT_FAILURE otherwise. (MEMORY_FAILURE code in case of memory failure)
 * -2 in case graph is not a tree.
 */

static int fileToGraph(const char *Filepath, Graph *g)
{
    FILE *file = fopen(Filepath, "r");
    if (file == NULL)
    {
        return EXIT_FAILURE;
    }
    int line_counter = 1;
    char line[MAX_LINE];
    char *value;
    //iterate through the file's lines
    while (fgets(line, MAX_LINE, file))
    {
        //set the number of vertices according to the first line
        if (line_counter == 1)
        {
            int V = isNatural(line);
            if (V == -1)
            {
                return EXIT_FAILURE;
            }
            else
            {
                g->V = V;
            }
            //a list representing all the vertices in the graph
            Node **graph_nodes = (Node**)malloc(g->V * sizeof(Node*));
            // in case of memory allocation error
            if(graph_nodes == NULL)
            {
                return MEMORY_ERROR;
            }
            //Initialize all the nodes
            for(int i = 0; i < g->V; i++)
            {
                graph_nodes[i] = newNode(i);
                // in case of memory allocation
                if(graph_nodes[i] == NULL)
                {
                    return MEMORY_ERROR;
                }
            }
            g->vertex_list = graph_nodes;

            line_counter++;
            continue;
        }
        //if number of lines exceeds the number of
        //vertices in the graph
        if(line_counter > g->V + 1)
        {
            return EXIT_FAILURE;
        }

        value = strtok(line, DELIMITERS);
        Node *ptr = g->vertex_list[line_counter-2];

        //check if line represents a leaf
        if (strcmp(value, HYPHEN) == 0)
        {
            value = strtok(NULL, DELIMITERS);
            if (!value)
            {
                //current node has no sons, free memory allocated
                //for sons array
                freeNode(&ptr->sons);
            }
            //if line starts with hyphen and has other values in it
            else
            {
                return EXIT_FAILURE;
            }
        }
        //iterate through the values in the given line
        while (value != NULL)
        {
            int num = parseValue(value, g);
            //if number cannot be a vertex representation,
            //return EXIT_FAILURE code
            if(num == -1)
            {
                return EXIT_FAILURE;
            }
            //given root has a parent, hence it is not the root of the tree
            Node *son = g->vertex_list[num];
            son->is_root = 0;
            //add ptr as parent to it's son's Node
            son->degree ++;
            if(son->parent->key == -1)
            {
                son->parent = ptr;
            }
            else
            {
                //return -2 to indicate that graph is not a tree
                //(because there are 2 parents to a single vertex)
                return -2;
            }

            //increase parent degree and add son to sons list
            //(after increasing the list's size)
            int extra_vertex = 0;
            if(ptr->parent->key != -1)
            {
                extra_vertex = 1;
            }

            //increase degree and allocate additional space to son's pointer
            ptr->degree++;
            Node **ptr1 = realloc(ptr->sons, ptr->degree * sizeof(Node*));
            ptr->sons = ptr1;

            //add son to sons list of ptr
            ptr->sons[ptr->degree - 1 - extra_vertex] = son;

            value = strtok(NULL, DELIMITERS);
        }
        line_counter++;
    }
    fclose(file);

    setRoot(g);
    //free the root's parent pointer (it is not needed)
    if(g->root)
    {
        Node **ptr = &g->root->parent;
        free(*ptr);
        *ptr = NULL;
    }
    else
    {
        //if no parent-less root was found,
        // graph is not a tree
        return -2;
    }
    return EXIT_SUCCESS;
}

void printData(Graph *g, int u, int v)
{
    printf("Root Vertex: %d\nVertices Count: %d\nEdges Count: %d\n"
           "Length of Minimal Branch: %d\nLength of Maximal Branch:"
           " %d\nDiameter Length: %d\nShortest Path Between %d and %d: ",
           g->root->key, g->V, g->V - 1, g->Min, g->Max, g->diameter, u, v);

    printPath(g, u, v);
}

/**
 * Function that frees all the memory
 * allocated for the graph and it's nodes
 * @param g The graph
 */

void freeGraph(Graph *g)
{
    for(int i = 0; i < g->V; i++)
    {
        Node *ptr = g->vertex_list[i];

        //free parent node
        if(ptr->parent)
        {
            free(ptr->parent);
        }

        if(ptr->sons)
        {
            freeNode(&ptr->sons);
        }

        if(ptr->previous)
        {
            free(ptr->previous);
        }

        //free each node in the graph's node list
        free(ptr);
    }

    if(g->vertex_list)
    {
        freeNode(&g->vertex_list);
    }

    if(g->root)
    {
        Node **ptr = &g->root;
        free(*ptr);
    }

    //free up the memory allocated for the graph
    Graph **ptr = &g;
    free(*ptr);
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "%s", args_msg);
        return EXIT_FAILURE;
    }

    //define a default graph to sent to the function
    Graph *g ;
    g = newGraph(-1);

    int num = fileToGraph(argv[1], g);

    //return appropriate error if needed
    if (num == EXIT_FAILURE)
    {
        fprintf(stderr, "%s", invalid_msg);
        freeGraph(g);
        return EXIT_FAILURE;
    }
    //in case of memory failure
    if(num == -1)
    {
        fprintf(stderr, "%s", mem_msg);
        freeGraph(g);
        return EXIT_FAILURE;
    }

    if(num == -2)
    {
        fprintf(stderr, "%s", tree_msg);
        freeGraph(g);
        return EXIT_FAILURE;
    }

    if(!isTree(g))
    {
        fprintf(stderr, "%s", tree_msg);
        freeGraph(g);
        return EXIT_FAILURE;
    }

    int u = parseValue(argv[2], g), v = parseValue(argv[3], g);

    //if given vertices are bad values, return invalid error
    if(v == -1 || u == -1)
    {
        fprintf(stderr, "%s", invalid_msg);
        freeGraph(g);
        return EXIT_FAILURE;
    }

    //assign max height, min height and diameter to the tree
    findHeight(g);
    findDiam(g);

    //print the necessary data
    printData(g, u, v);

    // free all the memory that was
    // allocated for the graph and the nodes
    freeGraph(g);

    return EXIT_SUCCESS;
}



