#include <stdio.h>
#include "listpos.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPos(ListPos *l){
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
  /* KAMUS LOKAL*/
  int i ;
  /* ALGORITMA */
  for(i= 0; i < CAPACITY;i++) {
    ELMT(*l,i) = VAL_UNDEF;
  }
}
/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l){
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
  /* KAMUS LOKAL*/
  int i = 0;
  /* ALGORITMA */
  while ((i < CAPACITY) && (ELMT(l,i) != VAL_UNDEF)) {
    i++;
  }
  return i;
}
/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListPos l, int i){
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
  /* ALGORITMA */
  return((i>= 0) && (i < CAPACITY));
}
boolean isIdxEff(ListPos l, int i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
  /* ALGORITMA */
  return((i>=0) && (i <= length(l)-1));
}
/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListPos l){
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
  /* ALGORITMA */
  return(ELMT(l,0) == VAL_UNDEF);
}
/* *** Test List penuh *** */
boolean isFull(ListPos l){
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
  /* ALGORITMA */
  return(ELMT(l,CAPACITY-1) != VAL_UNDEF);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListPos *l){
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITY; Lakukan n kali:
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
  /* KAMUS LOKAL*/
  int n;
  int i = 0;
  CreateListPos(l);
  /* ALGORITMA */
  scanf("%d", &n);
  while(!(0<=n && n<=CAPACITY)){
    scanf("%d", &n);
  }
  for(i=0; i < n; i++){
    scanf("%d", &ELMT(*l,i));
  }
}
void displayList(ListPos l){
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */
  /* KAMUS LOKAL*/
  int i;
  /* ALGORITMA */
  printf("[");
  for(i=0;i<length(l);i++){
    if (i != length(l)-1) {
      printf("%d,", ELMT(l,i));
    }
    else{
      printf("%d", ELMT(l,i));
    }
  }
  printf("]");
}
/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus){
/* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada
   indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi
  elemen l2 pada indeks yang sama */
  /* KAMUS LOKAL*/
  ListPos l3;
  /* ALGORITMA */
  CreateListPos(&l3);
  int i;
  for(i=0; i<length(l1); i++){
    if (plus == true) {
      ELMT(l3,i) = ELMT(l1,i) + ELMT(l2,i);
    }
    else{
      ELMT(l3,i) = ELMT(l1,i) - ELMT(l2,i);
    }
  }
  return l3;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListPos l1, ListPos l2){
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua
   elemennya sama */
   /* KAMUS LOKAL*/
  boolean eq = true;
  int i = 0;
  /* ALGORITMA */
  if (length(l1) != length(l2)) {
    eq = false;
  }
  else {
    while(i < length(l1) && eq == true) {
      if(ELMT(l1,i) != ELMT(l2,i)) {
        eq = false;
      }
      i++;
    }
  }
  return eq;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListPos l, ElType val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
  /* KAMUS LOKAL*/
  int i;
  int idx = IDX_UNDEF;
  boolean found = false;
  /* ALGORITMA */
  if (length(l) != 0) {
    i = 0;
    while(i < length(l) && found == false){
      if (ELMT(l,i) == val){
        found = true;
        idx = i;
      }
      i++;
    }
  }
  return idx;
}
/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, ElType *max, ElType *min){
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
  /* KAMUS LOKAL*/
  int i ;
  int el;
  /* ALGORITMA */
  *max = ELMT(l,0);
  *min = ELMT(l,0);
  for(i=0;i<length(l);i++){
    el = ELMT(l,i);
    if(el > *max){
      *max = el;
    }
    if(el < *min){
      *min = el;
    }
  }
}
/* ********** OPERASI LAIN ********** */
boolean isAllEven(ListPos l){
/* Menghailkan true jika semua elemen l genap */
  /* KAMUS LOKAL*/
  boolean genap = true;
  int i = 0;
  /* ALGORITMA */
  while(i < length(l) && genap == true){
    if (ELMT(l,i)%2 != 0) {
      genap = false;
    }
    i++;
  }
  return genap;
}
/* ********** SORTING ********** */
void sort(ListPos *l, boolean asc){
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
   /* KAMUS LOKAL*/
  int i = 0;
  int j = 0 ;
  int len;
  int temp;
  /* ALGORITMA */
  len = length(*l);
  if (len != 0){
    if (asc == true){
      for(i=0; i < len-1; i++){
        for(j=0; j < len-i-1; j++){
          if (ELMT(*l,j) > ELMT(*l,j+1)){
            temp = ELMT(*l,j+1);
            ELMT(*l,j+1) = ELMT(*l,j);
            ELMT(*l,j) = temp;
          }
        }
      }
    }
    else{
      for(i=0; i < len-1; i++){
        for(j=0; j < len-i-1; j++){
          if (ELMT(*l,j) < ELMT(*l,j+1)){
            temp = ELMT(*l,j+1);
            ELMT(*l,j+1) = ELMT(*l,j);
            ELMT(*l,j) = temp;
          }
        }
      }
    }
  }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, ElType val){
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
  /* ALGORITMA */
  ELMT(*l,length(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, ElType *val){
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
  /* ALGORITMA */
  *val = ELMT(*l,length(*l)-1);
  ELMT(*l,length(*l)-1) = VAL_UNDEF;
}
