#include"map.h"
#include<stdio.h>

int main(){
    int a = 10;
    int b = 15;
    Loc posisiNow;
    map m;
    Matrix mat;
    ListDin l;
    CreateListDin(&l, 10);
    readList(&l);
    readMatrix(&mat, 3, 3);
    posisiNow = l.buffer[2];
    makeMap(&m,a,b,l);
    printMap(m, l,mat,posisiNow);
    printf("\n");
    printf("NOBITA DIPINDAHKAN");
    move(mat,l,posisiNow);
    printMap(m, l,mat,posisiNow);

    return 0;
}