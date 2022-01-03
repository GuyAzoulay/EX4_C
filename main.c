#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "graph.h"

int main() {

    pnode list_head;
    pnode *head = &list_head;
    int b, temp1,tspp;
    char choose;
    bool a= true;
//    scanf("%s", &choose);
    while (scanf("%c", &choose)){
        if(choose == '\n') break;
        if(choose == 'A') {
            if (a == false) {
                deleteGraph_cmd(head);
            }
            list_head = (pnode) malloc(sizeof(node)); // dont forget to check if null
            list_head->node_num = 0;
            list_head->next = NULL;
            list_head->edges = NULL;
            pnode *temp = &list_head;
            choose = build_graph_cmd(head);
            list_head = *temp;
            a = false;
        }

        if(choose == 'B') {
            while (scanf("%d", &temp1)) {
                b = temp1;
                if (find_node(b, list_head) == NULL) { //if it doesn't exist
                    insert_node_cmd(list_head, b);
                    pnode src2 = find_node(b, list_head);
                    while (scanf("%d", &b)) {
                        pnode dest2 = find_node(b, list_head);
                        scanf("%d", &b);
                        int weight = b;
                        insert_Edge(weight, src2, dest2);
                    }
                } else {
                    pnode src1 = find_node(b, list_head);
                    deleteOutEdges(head, src1);
                    while (scanf("%d", &b)) {
                        pnode dest2 = find_node(b, list_head);
                        scanf("%d", &b);
                        int weight = b;
                        insert_Edge(weight, src1, dest2);
                    }
                }

            }

        }
        if(choose == 'D') {
            delete_node_cmd(head);
        }

        if(choose == 'S') {
            sp_cmd(list_head);
        }
        if(choose == 'T') {
            tspp = TSP_cmd(list_head);
            printf("TSP shortest path: %d \n", tspp);

        }

        }
    deleteGraph_cmd(head);
    return 0;
}

// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 B 5 0 4 2 1 B 2 1 3 5 1 T 3 2 1 3 D 2