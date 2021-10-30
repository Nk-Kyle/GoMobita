#include <stdio.h>
#include "listGadget.c"

int main()
{
    ListGadget l;
    int val;
    int n, x;

    printf("Jumlah gadget: ");
    scanf("%d", &n);    

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        LGELMT(l, i) = val;
    }

    printf("\nInventory gadget:\n");
    displayListGadget(l);

    printf("\nHapus gadget ke: ");
    scanf("%d", &x); 
    x--;
    deleteGadget(&l, x, &val);

    printf("\nInventory gadget:\n");
    displayListGadget(l);

    printf("\nTambah gadget: ");
    scanf("%d", &val); 
    insertGadget(&l, val);

    printf("\nInventory gadget:\n");
    displayListGadget(l);

    return 0;
}