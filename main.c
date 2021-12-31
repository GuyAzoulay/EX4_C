#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <intrin.h>

#include "graph.h"

int main() {

    pnode list_head;
    int b;
    char choose;
    char* caseB;
    int temp1;
    scanf("%s" ,&choose);
    while(choose != 'x') {
        switch (choose) {
            case 'A':
                list_head = (pnode) malloc(sizeof(node)); // dont forget to check if null
                list_head->node_num=0;
                list_head->next=NULL;
                list_head->edges=NULL;
                pnode *temp = (pnode) &list_head;
                choose= build_graph_cmd(temp);
                list_head = *temp;
                break;

           case 'B':
                while (scanf("%d",&temp1)) {
                    b = temp1;
                    if (find_node(b, list_head) == NULL) {
                        insert_node_cmd(list_head, b);
                    } else {
                        pnode src = find_node(b, list_head);
                        while(src->edges){
                            src->edges->weight=NULL;
                            src->edges->endpoint=NULL;
                            src->edges=src->edges->next;
                        }
                        while (scanf("%d", &b)) {
                            pnode dest = find_node(b, list_head);
                            scanf("%d", &b);
                            int weight = b;
                            insert_Edge(weight, src, dest);
                        }
                    }
                }
                scanf("%c",&choose);
                break;
            case 'D':
                delete_node_cmd(list_head);
                scanf("%c",&choose);
                break;

            case 'S':
                shortsPath_cmd(list_head);
                scanf("%c",&choose);
//            case 'T':
            case 'x':
                printGraph_cmd(list_head);
                break;
        }

    }
    return 0;
}

