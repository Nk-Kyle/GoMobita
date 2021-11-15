#include "list_linked.c"
#include "node.c"
#include "../ADTItem/item.c"
#include "../ADTQueue/prioqueue.c"
#include "../ADTStack/stackTas.c"
#include <stdio.h>

int main(){
    LinkedList l;
    Pesanan p;
    CreateLinkedList(&l);
    displayToDoList(l);
    printf("============================\n");
    p.dropoff = 'C';
    p.exp = -1;
    p.itype = 'H';
    p.pickup = 'B';
    p.pickuptime = 0;
    p.time = 1;
    insertLinkedListFirst(&l,p);
    displayToDoList(l);
    printf("============================\n");
    p.itype='V';
    p.pickup='C';
    insertLinkedListLast(&l,p);
    displayToDoList(l);
    printf("============================\n");
    deleteLinkedListFirst(&l,&p);
    displayToDoList(l);
    printf("============================\n");
    deleteLinkedListLast(&l,&p);
    displayToDoList(l);
    printf("============================\n");   
    return 0;
}