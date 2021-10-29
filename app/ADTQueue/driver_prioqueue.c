#include "prioqueue.c"
#include <stdio.h>

int main()
{
    int n, i;
    int time, exp;
    char pickup, dropoff, type;
    Pesanan elemen;
    PrioQueue pq;
    printf("Masukkan Jumlah Data: ");
    scanf("%d", &n);
    CreatePrioQueue(&pq);
    for (i = 0; i < n; i++)
    {
        scanf("%d %c %c %c", &time, &pickup, &dropoff, &type);
        if (type == 'P')
        {
            scanf("%d", &exp);
            elemen.exp = exp;
        }
        else
        {
            elemen.exp = -1;
        }
        elemen.time = time;
        elemen.pickup = pickup;
        elemen.dropoff = dropoff;
        elemen.itype = type;
        penqueue(&pq, elemen);
    }
    displayPQueue(pq);
    return 0;
}
