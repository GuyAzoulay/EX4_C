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
                    if (find_node(b, list_head) == NULL) {
                        insert_node_cmd(list_head, b);
                    } else {
                        pnode src = find_node(b, list_head);
                        while (src->edges) {
                            src->edges->weight = 0;
                            src->edges->endpoint = NULL;
                            src->edges = src->edges->next;
                        }
                        while (scanf("%d", &b)) {
                            pnode dest = find_node(b, list_head);
                            scanf("%d", &b);
                            int weight = b;
                            insert_Edge(weight, src, dest);
                        }
                    }
                }
                scanf("%s", &choose);
                break;
            case 'D':
                delete_node_cmd(list_head);
                scanf("%s", &choose);
                break;

            case 'S':
                sp_cmd(list_head);
                scanf("%c",&choose);
                break;
            case 'T':
                scanf("%d", &i);
                int size = i;
                int tsp[i];
                while (0 < i) {
                    if (scanf("%d", &dest) == 1) {
                        tsp[i-1] = dest;
                        i--;
                    } else
                        break;
                }
                tspp = TSP_cmd(list_head, tsp, size);
                printf("TSP shortest path: %d \n",tspp);
                scanf("%s",&choose);
                break;

        }

    }
    deleteGraph_cmd(list_head);
    return 0;
}

