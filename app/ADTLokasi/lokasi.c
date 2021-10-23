/* File implementasi lokasi */
#include <stdio.h>
#include "lokasi.h"
Loc MakeLoc (char name, int x, int y){
/* Konstruktor Loc L dengan Name(L) diisi name
   Coor(L) berupa point dengan Absis x dan Ordinat y */
   POINT p;
   Loc l;
   Absis(p) = x;
   Ordinat(p) = y;
   Name(l) = name;
   Coor(l) = p;
   return l;
}
void DispLoc (Loc l){
/* Menuliskan Loc dalam bentuk : lokname Absis(coord) Ordinat(coord) */
  printf("%c %d %d", Name(l), Absis(Coor(l)), Ordinat(Coor(l)));
}
