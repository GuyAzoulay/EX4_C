#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "graph.h"

int main() {

    pnode list_head;
    int i = 0, b, temp1, src, dest, shortest, tspp;
    char choose;
    bool a= true;
    scanf("%s", &choose);
    while (choose != '\n' ) {
        switch (choose) {
            case 'A':
                if(a==false){
                    deleteGraph_cmd(list_head);
                }
                list_head = (pnode) malloc(sizeof(node)); // dont forget to check if null
                if(list_head == NULL){
                    printf("Failed to allocate memory");
                    return -1;
                }
                list_head->node_num = 0;
                list_head->next = NULL;
                list_head->edges = NULL;
                pnode *temp = (pnode*) &list_head;
                choose = build_graph_cmd(temp);
                list_head = *temp;
                a=false;
                break;

            case 'B':
                while (scanf("%d", &temp1)) {
                    b = temp1;
                    if (find_node(b, list_head) == NULL) { //if it doesn't exist
                        insert_node_cmd(list_head, b);
                        pnode src2= find_node(b,list_head);
                        while (scanf("%d", &b)) {
                            pnode dest2 = find_node(b, list_head);
                            scanf("%d", &b);
                            int weight = b;
                            insert_Edge(weight, src2, dest2);
                        }
                    } else {
                        pnode src1 = find_node(b, list_head);
                        while (src1->edges) {
                            src1->edges->weight = 0;
                            src1->edges->endpoint = NULL;
                            src1->edges = src1->edges->next;
                        }
                        while (scanf("%d", &b)) {
                            pnode dest2 = find_node(b, list_head);
                            scanf("%d", &b);
                            int weight = b;
                            insert_Edge(weight, src1, dest2);
                        }
                        }
                    }
                scanf("%c", &choose);
                break;
            case 'D':
                delete_node_cmd(list_head);
                scanf("%c", &choose);
                printGraph_cmd(list_head);
                break;

            case 'S':
                sp_cmd(list_head);
                scanf("%c",&choose);
                break;
            case 'T':
               printGraph_cmd(list_head);

                tspp = TSP_cmd(list_head);
                printf("TSP shortest path: %d \n",tspp);
                scanf("%s",&choose);
                break;

        }

    }
    deleteGraph_cmd(list_head);
    return 0;
}

// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 B 5 0 4 2 1 B 2 1 3 5 1 T 3 2 1 3 D 2