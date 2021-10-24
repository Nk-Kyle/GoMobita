/* MODUL LIST INTEGER DENGAN ELEMEN POSITIF */
/* Berisi definisi dan semua primitif pemrosesan list integer dengan elemen positif */
/* Banyaknya elemen didefinisikan secara implisit, memori array statik */

#ifndef LISTGADGET_H
#define LISTGADGET_H

#include "../boolean.h"

/*  Kamus Umum */
#define LISTGADGET_CAPACITY 5
/* Kapasitas penyimpanan */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/
#define VAL_UNDEF -999
/* Nilai elemen tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int ElType;  /* type elemen List */
typedef struct {
   ElType contents[LISTGADGET_CAPACITY]; /* memori tempat penyimpan elemen (container) */
} ListGadget;
/* Indeks yang digunakan [0..CAPACITY-1] */
/* Jika l adalah ListGadget, cara deklarasi dan akses: */
/* Deklarasi : l : ListGadget */
/* Maka cara akses:
   ELMT(l,i) untuk mengakses elemen ke-i */
/* Definisi :
   List kosong: semua elemen bernilai VAL_UNDEF
   Definisi elemen pertama: ELMT(l,i) dengan i=0 */

/* ********** SELEKTOR ********** */
#define ELMT(l, i) (l).contents[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListGadget(ListGadget *l);
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* ********** Test Indeks yang valid ********** */
boolean isIdxGadgetEff(ListGadget l, int i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isGadgetEmpty(ListGadget l);
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isGadgetFull(ListGadget l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void displayListGadget(ListGadget l);
/* Proses : Menuliskan isi List dengan traversal */
/* I.S. l boleh kosong */
/* F.S. l ditampilkan ke layar */

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListGadget l, ElType val);
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN ********** */
/* *** Menambahkan elemen *** */
void insertGadget(ListGadget *l, ElType val);
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void deleteGadget(ListGadget *l, int idxDelete, ElType *val);
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */

#endif
