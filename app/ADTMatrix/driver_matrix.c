#include "matrix.c"
#include <stdio.h>

int main(){
    Matrix m;
    CreateMatrix(3,3,&m);
    displayMatrix(m);
    return 0;
}