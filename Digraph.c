//
// Created by Guy on 12/29/2021.
//
#include "math.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <intrin.h>
#include "../graph.h"
#include <limits.h>

// this is the node struct


pnode pop ( pnode head);
int isEmpty (pnode *head);
pnode push(pnode head, int data);
int peek(pnode *head);
int contain (int elem, int arr []);
static char How_Much_Nodes;
pnode change_place(pnode head);

node* newNode( int data){
    node *p= (node*) malloc(sizeof (node));
    p->node_num=data;
    p->next=NULL;
    p->edges =NULL;
    return p;
}
int is_Number(char *string){
    int len =strlen(string);
    for (int i = 0; i < len ; ++i) {
        if(!isdigit(string[i])){
            return 0;
        } else{
            continue;
        }
    }
    return 1;
}
int turn_To_Num(char *string){
    int res=0;
    int length = strlen(string);
    for (int i = 0; i < length; ++i) {
        res+= (int) pow(10,length-i-1)*(string[i]-48);
    }
    return res;
}
char build_graph_cmd(pnode *head){
    int v;
    pnode node = *head;
    char f="";
    int temp;
    scanf("%d",&v);
    How_Much_Nodes=v;
    for (int i = 1; i < v; ++i) {
        insert_node_cmd(node,i);
    }
    scanf("%s",&f);
    while (is_Number(&f)||f=='n'){
        if( f == 'n') {
            scanf("%s", &f);
        } else{
            int sr= turn_To_Num(&f);// first after n is src
            pnode src = find_node(sr,node);
            scanf("%s", &f);
            while (is_Number(&f)){   //if next after src is dest
                int a= turn_To_Num(&f);   // turn ut to num
                pnode dest = find_node(a,node); // check the node id exist
                scanf("%s", &f); //now we are getting weight
                int weight = turn_To_Num(&f);
                insert_Edge(weight,src,dest);
                scanf("%s",&f);
            }
        }
    }
    return f;

}
pnode find_node(int data,  pnode head){
    pnode temp =head;
    while (temp){
        if(temp->node_num==data){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
void insert_Edge(int w, pnode src, pnode dest){
    edge *temp = src->edges;
    if (temp == NULL){
        edge *e =(edge*) malloc(sizeof(edge));
        e->next=NULL;
        e->weight=w;
        e->endpoint=dest;
        src->edges = e;
        return;
    }
    while (temp->next){
        if (temp->endpoint->node_num == dest->node_num) { // there is an edge
            temp->weight = w;
            return;
        }
        temp = temp->next;
    }
    edge *e =(edge*) malloc(sizeof(edge));
    e->next=NULL;
    e->weight=w;
    e->endpoint=dest;
    temp->next=e;
    }

void insert_node_cmd(pnode *head,int data){
    struct GRAPH_NODE_ *something = head;
    int id;
    while (something->next){
        id = (something->next->node_num);
        if(id != data) {
            something = something->next;
        }
        else{
            struct edge_ **edges_to_update= &((something)->edges);
            if(*edges_to_update == NULL){
                something->next = NULL;
                break;
            } else {
                something->next->edges = *edges_to_update;
                something->next = newNode(data);
                break;
            }
        }

    }
    something->next = newNode(data);
}
void delete_node_cmd(pnode *head){
    int node_to_del;
    scanf("%d",&node_to_del);
    pnode start=head;
    pnode temp =head;
    int first = 0;
    if(start->node_num == node_to_del){
        start->edges->weight = NULL;
        start->edges->endpoint = NULL;
        start->edges =NULL;
       // temp = start->next;
        first = 1;
        temp->node_num = temp->next->node_num;
        temp->edges = temp->next->edges;
        temp->next = temp->next->next;
        head = temp;
    }
    else {
        while (start->next->node_num != node_to_del) {
            start = start->next;
        }
        while (start != NULL && start->edges) {
            start->edges->weight = NULL;
            start->edges->endpoint = NULL;
            start = start->edges->next;
        }
    }
    while (temp != NULL) {
        if (temp->edges != NULL && temp->edges->endpoint != NULL && temp->edges->endpoint->node_num == node_to_del) {
            temp->edges = temp->edges->next;
        } else {
            while (temp->edges) {
                if (temp->edges->next != NULL && temp->edges != NULL && temp->next->edges->endpoint != NULL &&
                    temp->next->edges->endpoint->node_num == node_to_del) {
                    temp->next->edges->weight = NULL;
                    temp->next->edges->endpoint = NULL;
                    temp = temp->next->next;
                    break;
                }
                temp->edges = temp->edges->next;
            }
            temp = temp->next;
        }
    }
    if(first == 0) {
        start->next = start->next->next;
    }
    return;
}

void  printGraph_cmd(pnode head){
    pnode temp = head;
    while (temp){
        printf("Node : %d" , temp->node_num);
        edge *e = temp->edges;
        while (e){
            printf(" - >%d " , e->endpoint->node_num);
            e = e->next;
        }
        printf("\n");
        temp = temp->next;
    }
}
void shortsPath_cmd(pnode head){
    int src_id;
    int dest_id;
    int path_weight;
    pnode *helper= head;
    pnode temp =head;
    pnode pq;
    int i =0;
    int there_is_path;
    int visit[How_Much_Nodes];
    for (int j = 0; j < How_Much_Nodes; ++j) {
        visit[j]=-1;
    }
    scanf("%d",&src_id);
    scanf("%d",&dest_id);
    while(temp){
        temp->node_weight=INT_MAX;
        temp = temp->next;
    }

    pnode src_node;// find_node(src_id,helper);
    src_node = find_node(src_id,helper);
    src_node->node_weight=0;
    pq = newNode(src_id);
    while (!isEmpty(pq)){
        if(peek(pq)== dest_id){
            there_is_path=1;
            break;
        }
        int nodeId= peek(pq);
        pq=pop(pq);
        visit[i]=nodeId;
        i++;
        while(src_node && src_node->edges){
            int weight= src_node->edges->weight;
            if(!contain(src_node->edges->endpoint->node_num,visit)){
                int old_cost= src_node->edges->endpoint->node_weight;
                int new_cost= src_node->node_weight+ weight;
                if(new_cost<old_cost) {
                    if (pq == NULL) {
                        pq = push(pq, src_node->edges->endpoint->node_num);
                        pq->node_weight=new_cost;
                        src_node->edges->endpoint->node_weight = new_cost;
                    } else {
                        pnode tt;
                        tt = push(pq, src_node->edges->endpoint->node_num);
                        tt->edges= src_node->edges;
                        pq->next = tt;
                        pq->next->node_weight=new_cost;
                        pq=change_place(pq);
                        src_node->edges->endpoint->node_weight = new_cost;
                    }
                }
                } else{
                if(src_node->edges->endpoint->node_weight > src_node->node_weight+weight){
                    src_node->edges->endpoint->node_weight = src_node->node_weight +weight;
                }
            }
            src_node->edges=src_node->edges->next; //delete my edge need to fix
        }
        src_node= find_node(pq->node_num,helper);
    }
    pnode temp2 = find_node(dest_id,head);
    path_weight = temp2->node_weight;
    printf("this is the path weight: %d\n", path_weight);

}
int peek(pnode *head){
    pnode temp=head;
    return (temp)->node_num;
}
pnode pop ( pnode head){
    pnode temp = head;
    (temp)= (temp)->next;
    head= temp;
    //free(temp);
    return head;
}
pnode push(pnode head, int data){
    pnode change;
    pnode temp = newNode(data);
    head=temp;
    return head;
}
int isEmpty (pnode *head){
    return (*head) == NULL;
}
int contain (int elem, int *arr){
    int ans=0;
    for (int i = 0; i < How_Much_Nodes ; ++i) {
        if(arr[i] == elem){
            ans=1;
            break;
        } else{
            continue;
        }
    }
    return ans;
}
pnode change_place(pnode head){
    pnode temp =head;
    pnode change;
    while (temp){
        if(head->node_weight > head->next->node_weight){
              change = newNode(head->node_num);
              change->edges= head->edges;
              change->node_weight = head->node_weight;
              change->next=head->next->next;
              head=head->next;
              head->next=change;
              temp=temp->next;
        } else{
            temp= temp->next;
        }
    }
    return head;
}

