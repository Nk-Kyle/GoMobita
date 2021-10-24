#include "stackTas.h"
#include <stdio.h>

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* - Kapasitas awal bernilai 3 */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */
  IDX_TOP(*s) = IDX_UNDEF;
  CURRENT_CAP(*s) = 3;
}
/* ************ Prototype ************ */
boolean isEmpty(Stack s){
/* Mengirim true jika s kosong: lihat definisi di atas */
  return(IDX_TOP(s) == IDX_UNDEF);
}
boolean isFull(Stack s){
/* Mengirim true jika tabel penampung nilai s stack penuh */
  return(IDX_TOP(s) == CURRENT_CAP(s) - 1);
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, Item item){
/* Menambahkan item sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. item menjadi TOP yang baru, IDX_TOP bertambah 1 */
  if (isEmpty(*s)) {
    IDX_TOP(*s) = 0;
  }
  else {
    IDX_TOP(*s)++;
  }
  TOP(*s) = item;
}
/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, Item *item){
/* Menghapus item dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. item adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */
  *item = TOP(*s);
  if (IDX_TOP(*s) == 0){
    IDX_TOP(*s) = IDX_UNDEF;
  }
  else{
    IDX_TOP(*s)--;
  }
}