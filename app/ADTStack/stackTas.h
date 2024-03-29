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
  Pesanan buffer[TAS_CAPACITY]; /* tabel penyimpan elemen */
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
void pushTas(StackTas *s, Pesanan item);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru, IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void popTas(StackTas *s, Pesanan *item);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

/* ************ Menambah kapasitas sementara Stack tas ************ */
void increaseTas(StackTas *s);
/* Meningkatkan kapasitas tas sebesar satu kali */
/* I.S. currentTasCap tas mungkin maksimal */
/* F.S. currentTasCap menjadi bertambah satu tetapi tidak melebihi batas maksimum */

/* ************ Update Stack tas ************ */
void updateTas(StackTas *s, int waktu);
/* Melakukan upate pada tas */
/* I.S. s mungkin memiliki item perishable yang sudah expired */
/* F.S. item perishable yang sudah expired akan hilang */

/* ************ Gadget ************ */
void senterPembesar(StackTas *s);
/* Meningkatkan kapasitas tas sebesar dua kali lipat */
/* I.S. currentTasCap tas mungkin maksimal */
/* F.S. currentTasCap menjadi dua kali lipat tetapi tidak melebihi batas maksimum */
int lengthTas(StackTas s);
/* Mengirimkan banyak isi tas */

void reverseTas(StackTas *s);
/* membalik urutan isi tas */
void dispTas(StackTas s);
#endif
