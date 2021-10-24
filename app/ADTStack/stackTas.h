/* File : stacktas.h */
/* Definisi ADT Stack Tas dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef STACKTAS_H
#define STACKTAS_H

#include "../boolean.h"
#include "../ADTItem/item.h"

#define IDX_UNDEF -1
#define CAPACITY 100

typedef struct {
  Item buffer[CAPACITY]; /* tabel penyimpan elemen */
  int idxTop;            /* alamat TOP: elemen puncak */
  int currentCap;        /* menyimpan kapasitas sementara tas*/ 
} Stack;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Stack, maka akses elemen : */
#define     IDX_TOP(s) (s).idxTop
#define         TOP(s) (s).buffer[(s).idxTop]
#define CURRENT_CAP(s) (s).currentCap

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isEmpty(Stack s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isFull(Stack s);
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, Item item);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, Item *item);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

#endif
