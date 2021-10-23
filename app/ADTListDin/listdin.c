
#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity){
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
  /*KAMUS*/
  /*ALGORITMA*/
  NEFF(*l) = 0;
  CAPACITY(*l) = capacity;
  BUFFER(*l) = (Loc *) malloc(sizeof(Loc) * capacity);
}
void dealocate(ListDin *l){
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
  /*KAMUS*/
  /*ALGORITMA*/
  free(BUFFER(*l));
  CAPACITY(*l) = 0;
  NEFF(*l) = 0;
}
/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int lengthList(ListDin l){
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
  /*KAMUS*/
  /*ALGORITMA*/
  return NEFF(l);
}
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l){
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
  /*KAMUS*/
  /*ALGORITMA*/
  return (NEFF(l)-1);
}
/* ********** Test Indeks yang valid ********** */
boolean isListIdxValid(ListDin l, int i){
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
  /*KAMUS*/
  /*ALGORITMA*/
  return(i >= 0 && i < CAPACITY(l));
}
boolean isListIdxEff(ListDin l, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
  /*KAMUS*/
  /*ALGORITMA*/
  return(i>= 0 && i < NEFF(l));
}
/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isListEmpty(ListDin l){
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
  /*KAMUS*/
  /*ALGORITMA*/
  return(NEFF(l) == 0);
}
/* *** Test list penuh *** */
boolean isListFull(ListDin l){
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
  /*KAMUS*/
  /*ALGORITMA*/
  return(NEFF(l) == CAPACITY(l));
}
/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l){
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
  /*KAMUS*/
  int i,n,x,y;
  char name;
  /*ALGORITMA*/
  do{
    scanf("%d", &n);
  } while(!(0<=n && n <= CAPACITY(*l)));
  for(i=0; i < n ; i++){
    scanf(" %c", &name);
    scanf("%d", &x);
    scanf("%d", &y);
    ELMT(*l, i) = MakeLoc(name,x,y);
  }
  NEFF(*l) = n;
}
void displayList(ListDin l){
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
  /*KAMUS*/
  int i;
  /*ALGORITMA*/
  for(i = 0; i < NEFF(l); i++){
    DispLoc(ELMT(l,i));
    printf("\n");
  }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, char locname){
/* Search apakah ada elemen List l dengan nama loc yang bernilai locname */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = locname */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */
  /*KAMUS*/
  int i = 0;
  int idx = IDX_UNDEF;
  boolean found = false;
  /*ALGORITMA*/
  while(found == false && i < NEFF(l)){
    if(Name(ELMT(l,i)) == locname) {
      found = true;
      idx = i;
    }
    else i++;
  }
  return idx;
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut){
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
  /*KAMUS*/
  int i ;
  /*ALGORITMA*/
  CreateListDin(lOut, CAPACITY(lIn));
  for(i=0; i < NEFF(lIn); i++){
    ELMT(*lOut,i) = ELMT(lIn,i);
  }
  NEFF(*lOut) = NEFF(lIn);
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, Loc t){
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
  /*KAMUS*/
  /*ALGORITMA*/
  ELMT(*l,NEFF(*l)) = t;
  NEFF(*l)++;
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, Loc *t){
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
  /*KAMUS*/
  /*ALGORITMA*/
  *t = ELMT(*l,NEFF(*l)-1);
  NEFF(*l)--;
}
/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(ListDin *l, int num){
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
  /*KAMUS*/
  int curr_cap,i;
  ListDin temp;
  /*ALGORITMA*/
  copyList(*l,&temp);
  curr_cap = CAPACITY(*l);
  dealocate(l);
  CreateListDin(l, curr_cap+num);
  for(i = 0; i < NEFF(temp); i++){
    ELMT(*l,i) = ELMT(temp,i);
  }
  NEFF(*l) = NEFF(temp);
  dealocate(&temp);
}

void shrinkList(ListDin *l, int num){
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
  /*KAMUS*/
  int curr_cap,i;
  ListDin temp;
  /*ALGORITMA*/
  copyList(*l,&temp);
  curr_cap = CAPACITY(*l);
  dealocate(l);
  CreateListDin(l, curr_cap-num);
  for(i = 0; i < NEFF(temp); i++){
    ELMT(*l,i) = ELMT(temp,i);
  }
  if (NEFF(*l) >= CAPACITY(*l)){
    NEFF(*l) = NEFF(temp);
  }
  else NEFF(*l) = CAPACITY(*l);

  dealocate(&temp);
}
void compactList(ListDin *l){
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List lidak kosong */
/* F.S. Ukuran nEff = capacity */
  /*KAMUS*/
  int i,curr_neff;
  ListDin temp;
  /*ALGORITMA*/
  curr_neff = NEFF(*l);
  copyList(*l,&temp);
  dealocate(l);
  CreateListDin(l, curr_neff);
  for(i = 0; i < NEFF(temp); i++){
    ELMT(*l,i) = ELMT(temp,i);
  }
  NEFF(*l) = CAPACITY(*l);
  dealocate(&temp);
}
