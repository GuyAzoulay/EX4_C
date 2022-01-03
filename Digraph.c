//
// Created by Guy on 12/29/2021.
//

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"
#include <limits.h>
#include <stdbool.h>

// this is the node struct
void del_in_Edges(pnode head, pnode node);
int pow1( int x, unsigned int y);
int findmin(int arr[],int arraysize);
void prevAndweight (pnode head);
pnode push_if_null(pnode head, int data,int weight);
pnode copy( pnode node_to_cop);
pnode pop ( pnode head);
int isEmpty (pnode head);
pnode push(pnode head, int data, int w);
int peek(pnode head);
int contain (int elem, const int arr []);
static int How_Much_Nodes;

int pow1( int x, unsigned int y){
    if(y==0) return 1;
    else if (y%2 == 0) return pow1(x,y/2)*pow1(x,y/2);
    else return  x*pow1(x,y%2)* pow1(x,y/2);
}
node* newNode( int data){
    node *p= (node*) malloc(sizeof (node));
    p->node_num=data;
    p->next=NULL;
    p->edges =NULL;
    p->prev=-1;
    return p;
}
int is_Number(char *string){
    int len =(int)strlen(string);
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
    int length = (int)strlen(string);
    for (int i = 0; i < length; ++i) {
        res+= (int) pow1(10,length-i-1)*(string[i]-48);
    }
    return res;
}
char build_graph_cmd(pnode *head){
    int v;
    pnode node = *head;
    char f='u';
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
    pedge temp =(edge*) malloc(sizeof(edge));
    temp=src->edges;
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

void insert_node_cmd(pnode head,int data){
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
void delete_node_cmd(pnode head){
    int node_to_del;
    scanf("%d",&node_to_del);
    pnode node_to_del2 = find_node(node_to_del,head);
    pnode start=head;
    pnode temp =head;
    int first = 0;
    if(start->node_num == node_to_del){
        start->edges->weight = 0;
        start->edges->endpoint = NULL;
        start->edges =NULL;
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
        while (start->next->edges->next !=NULL && start->next->edges->endpoint !=NULL) {
            start->next->edges->weight = 0;
            start->next->edges->endpoint = NULL;
            start->next->edges = start->edges->next;
        }
        start->next=start->next->next;

    }
    del_in_Edges( head,node_to_del2);
   // free(start);
    free(temp);
}

void  printGraph_cmd(pnode head){
    pnode temp = head;
    while (temp){
        printf("Node : %d" , temp->node_num);
        pedge e = temp->edges;
        while (e){
            printf(" - >(D :%d ,W :%d)" , e->endpoint->node_num,e->weight);
            e = e->next;
        }
        printf("\n");
        temp = temp->next;
    }
}
void sp_cmd(pnode head){
    int src,dest;
    scanf("%d", &src);
    scanf("%d", &dest);
    int shortest = shortsPath_cmd(head,src,dest);
    printf("Dijsktra shortest path: %d\n", shortest);
}
int shortsPath_cmd(pnode head,int src_id,int dest_id){
    int path_weight=-1;
    pnode helper= head;
    //  pnode temp =head;
    pnode pq;
    int i =0;
    int visit[How_Much_Nodes];
    for (int j = 0; j < How_Much_Nodes; ++j) {    //initialize an array to -1 , it will help me to se if I visit node
        visit[j]=-1;
    }
    while(helper){   // updating all node "weights" to inf
        helper->node_weight=INT_MAX;
        helper = helper->next;
    }
    pnode src_node;// find_node(src_id,helper);
    helper = find_node(src_id,head);   // always the helper and src node have connection, in aim to run on all the
    helper->node_weight=0;                  // edges of each node
    src_node = copy(helper);     // creating a copy in aim that my data wont be lost
    src_node->node_weight=0;                // first node weight is 0
    if(src_node->edges != NULL) {
        pq = newNode(src_id);              // my priority queue
        while (!isEmpty(pq)) {             // run until my queue is not empty
            if (i > 0) {                        // dont want it get in the first time
                helper = find_node(pq->node_num, head);   // taking the first in queue
                src_node = copy(helper);            // copy again
            }
            if (peek(pq) == dest_id) {      // condition to stop if i reach the dest node
                visit[i] = pq->node_num;
                break;
            }
            int nodeId = peek(pq);   // always add the first node we pop from the queue to the visit array
            pq = pop(pq);
            visit[i] = nodeId;
            i++;
            while (src_node->edges) {    // run on all the edges
                int weight = src_node->edges->weight;    // taking the weight
                if (!contain(src_node->edges->endpoint->node_num, visit)) {  // checking if i visit or nor in this node
                    int old_cost = src_node->edges->endpoint->node_weight;    //calculating the new and old cost
                    int new_cost = src_node->node_weight + weight;
                    if (new_cost <= old_cost) {
                        if (pq == NULL) {  // in situation the queue is null,  putting the first
                            pq = push_if_null(pq, src_node->edges->endpoint->node_num, new_cost);
                            helper = find_node(src_node->edges->endpoint->node_num, head);
                            helper->prev = src_node->node_num;
                            helper->node_weight = new_cost; // updating the new weight in the original graph
                        } else {
                            pq = push(pq, src_node->edges->endpoint->node_num,
                                      new_cost); // if there are more than 2 nodes in the
                            helper = find_node(src_node->edges->endpoint->node_num,
                                               head);      // queue we put the smallest weight first
                            helper->node_weight = new_cost;
                            helper->prev = src_node->node_num;
                        }
                    }

                } else {
                    if (src_node->edges->endpoint->node_weight >
                        src_node->node_weight + weight) {   // if the node already visit in and need to update again
                        helper = find_node(src_node->edges->endpoint->edges->endpoint->node_num, head);
                        helper->node_weight = src_node->node_weight + weight;
                        helper->prev = src_node->node_num;
                    }
                }
                src_node->edges = src_node->edges->next; // going through all the edges
            }
        }

        pnode temp2 = find_node(dest_id, head);
        path_weight = temp2->node_weight;
        pnode des = find_node(dest_id, head);
//        printf("%d<-", dest_id);
//        while (des->prev != src_id) {
//            printf("%d <-", des->prev);
//            des = find_node(des->prev, head);
//        }
//        printf("%d", des->prev);
//        printf("\n");
        // printf("Dijsktra shortest path: %d\n", path_weight);
        free(pq);

        //      free(helper);
//        free(temp);
        //free(temp2);
        // free(des);
    }
    return path_weight;
}
int peek(pnode head){
    pnode temp=head;
    return (temp)->node_num;
}
int TSP_cmd(pnode head) {
    int i=0;
    scanf("%d", &i);
    int size = i;
    int tsp[i];
    int dest=0;
    int ans=-1;
    i=0;
    while (i<size) {
        if (scanf("%d", &dest) == 1) {
            tsp[i] = dest;
            i++;
        } else
            break;
    }
    bool b = true;
//    int pathweight[size * size - size];
//    for (int i = 0; i < size * size - size; ++i) {
//        pathweight[i] = INT_MAX;
//    }
    int index = 0;

    int contains[size];
    // --------this part check if all the numbers in the path are in the cities--------------//
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (j != k) {

                if (find_node(tsp[j], head)->edges != NULL) {
                    for (int i = 0; i < size ; ++i) {
                        contains[i] = 0;
                    }
                    int while_index = 0;
                    prevAndweight(head);
                   int x= shortsPath_cmd(head, tsp[j], tsp[k]);
                    pnode check = find_node(tsp[k], head);
                    while (check && while_index < size)  {
                        for (int l = 0; l <size; ++l) {
                            if(check->node_num == tsp[l]) contains[while_index++] = 1;
                        }
                        check = find_node(check->prev,head);


//                        if (contain(check->node_num, tsp)) {
//                            contains[while_index++] = 1;
//                            check = find_node(check->prev, head);
//                        } else {
//                            check = find_node(check->prev, head);
//                        }
                    }

                    for (i = 0; i < size; i++) {
                        if (contains[i] != 1) {
                           b =  false;
                            break;
                        }
                    }
                    if (b) {
                        if(x<=ans || ans == -1) {
                            ans=x;
                            //pnode tmp = find_node(tsp[k], head);
                           // pathweight[index] = tmp->node_weight;
                          //  index++;
                        }
                    }
                    b = true;
                }
            }
        }
    }

   // int ans= findmin(pathweight,size * size - size);
    return ans;
}
void deleteGraph_cmd(pnode head){
    pnode curr =head;
    pnode prev =head;
    while(curr){
        pedge curr_e =prev->edges;
        pedge prev_e = prev->edges;
        while (curr_e){
            prev_e=curr_e;
            curr_e=curr_e->next;
            free(prev_e);
        }
        prev=curr;
        curr=curr->next;
        free(prev);
    }
}




pnode push(pnode head, int data,int weight) { // function that pushes a new node by his weight, small weight will be first
    if (head != NULL) {
        pnode start = head;
        pnode tmp = newNode(data);
        tmp->node_weight=weight;
        if (head->node_weight > weight) {
            tmp->next = head;
            head= tmp;
            return head;
        } else {
            while (start->next != NULL && start->next->node_weight < weight) {
                start = start->next;
            }
            tmp->next = start->next;
            start->next = tmp;
        }
    }
    return head;

}


pnode pop ( pnode head){  //deleting the first node in the queue
    pnode temp = head;
    (temp)= (temp)->next;
    head= temp;
    //free(temp);
    return head;
}

pnode copy( pnode node_to_cop){
    pnode p = (pnode) malloc(sizeof(node));
    p->edges= node_to_cop->edges;
    p->next=NULL;
    p->node_num =node_to_cop->node_num;
    p->node_weight=node_to_cop->node_weight;
    return p;
}
pnode push_if_null(pnode head, int data,int weight){
    pnode temp = newNode(data);
    temp->node_weight=weight;
    head=temp;
    return head;
}
void prevAndweight (pnode head){
    while (head){
        head->node_weight=-1;
        head->prev =-1;
        head= head->next;
    }
}
int findmin(int arr[],int arraysize){
    int min;
    min=arr[0];
    for (int i = 1; i < arraysize; ++i) {
        if(min>arr[i]){
            min=arr[i];
        }
    }
    return min;
}
int contain (int elem, const int *arr){
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
int isEmpty (pnode head){
    return (head) == NULL;
}
void del_in_Edges(pnode head, pnode node) {
    pnode run = head;
    while (run != NULL) {
        // if run is node -> continue
        if (run == node) {
            run = run->next;
            continue;
        }

        // Run on all edges of "run" and check if there any dest edge equals to "node"
        pedge prev, curr = run->edges;
        // if the first edge dest point is "node" delete it and continue to next node edges
        if (curr != NULL) {
            if (curr->endpoint == node) {
                run->edges = curr->next;
                free(curr);
                run = run->next;
                continue;
            }
        }
        // if edge with endpoint equal to "node" is in middle or in the end;
        while (curr != NULL) {
            prev = curr;
            curr = curr->next;
            if (curr->endpoint == node) {
                if (curr->next != NULL) {
                    prev->next = curr->next->next;
                    free(curr);
                    break;
                } else {
                    prev->next = NULL;
                    free(curr);
                    break;
                }

            }
            curr = curr->next;
        }
        run = run->next;
    }
}