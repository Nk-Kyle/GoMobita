#include <stdio.h>
#include "point.h"

/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y) {
/* Membentuk sebuah POINT dari komponen-komponennya */
  /* KAMUS */
  POINT p;
  /* Algoritma */
  Absis(p) = X;
  Ordinat(p) = Y;
  return p;
}

void BacaPOINT (POINT * P){
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
  /* KAMUS */
  int x,y;
  /* Algoritma */
  scanf("%d %d", &x, &y);
  *P = MakePOINT(x,y);
}

void TulisPOINT (POINT P){
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
  /* Algoritma */
  printf("(%d,%d)",Absis(P), Ordinat(P));
}
