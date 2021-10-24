/* File : stacktas.h */
/* Definisi ADT Stack Tas dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef STACKTAS_H
#define STACKTAS_H

#include "../boolean.h"
#include "../ADTItem/item.h"

#define IDX_UNDEF -1
#define TAS_CAPACITY 100

typedef struct {
  QElType buffer[TAS_CAPACITY]; /* tabel penyimpan elemen */
  int idxTop;                   /* alamat TOP: elemen puncak */
  int currentTasCap;            /* menyimpan kapasitas sementara tas*/ 
} StackTas;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Stack, maka akses elemen : */
#define         IDX_TOP(s) (s).idxTop
#define             TOP(s) (s).buffer[(s).idxTop]
#define CURRENT_TAS_CAP(s) (s).currentTasCap

/* *** Konstruktor/Kreator *** */
void CreateTas(StackTas *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isTasEmpty(StackTas s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isTasFull(StackTas s);
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void pushTas(StackTas *s, QElType item);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void popTas(StackTas *s, QElType *item);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

#endif
