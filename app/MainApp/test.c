#include <stdio.h>
#include <stdlib.h>

int main( ) {
  FILE * f;
  f = fopen("data.txt", "w");
  fprintf(f, "%d",1);
  return 0;
}
