#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int prev;
    int node_num;
    int node_weight;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char build_graph_cmd(pnode *head); // case A
void insert_node_cmd(pnode head,int data); // case B
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode *head);
int shortsPath_cmd(pnode head,int src, int dest);
int TSP_cmd(pnode head);
pnode find_node(int data,  pnode head);
int is_Number(char *string);
int turn_To_Num(char *string);
void insert_Edge(int w, pnode src, pnode dest);
void sp_cmd(pnode head);
void deleteOutEdges(pnode *head, pnode node);

#endif
