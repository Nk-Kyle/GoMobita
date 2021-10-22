/*
NIM : 13520040
Nama  : Ng Kyle
Tanggal : 4 Oktober 2021
Topik praktikum :ADT Queue
Deskripsi : Implementasi ADT Queue
*/

#include "queue.h"
#include <stdio.h>

/* *** Kreator *** */
void CreateQueue(Queue *q){
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */
  // KAMUS LOKAL
  // ALGORITMA
  IDX_HEAD(*q) = IDX_UNDEF;
  IDX_TAIL(*q) = IDX_UNDEF;
}
/* ********* Prototype ********* */
boolean isEmpty(Queue q){
/* Mengirim true jika q kosong: lihat definisi di atas */
  return(IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF);
}
boolean isFull(Queue q){
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */
  return(IDX_HEAD(q) == 0 && IDX_TAIL(q) == CAPACITY-1);
}
int length(Queue q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
  if(isEmpty(q)) return 0;
  else return(IDX_TAIL(q)-IDX_HEAD(q)+1);
}

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, ElType val){
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
  int idx;
  if (isEmpty(*q)){
    IDX_HEAD(*q) = 0;
    IDX_TAIL(*q) = 0;
    TAIL(*q) = val;
  }
  else if (IDX_TAIL(*q) == CAPACITY-1){
    for(idx = 0; idx < length(*q); idx++){
      (*q).buffer[idx] = (*q).buffer[IDX_HEAD(*q)+idx];
    }
    IDX_TAIL(*q) = CAPACITY-1-IDX_HEAD(*q);
    IDX_HEAD(*q) = 0;
    IDX_TAIL(*q)++;
    TAIL(*q) = val;
  }
  else{
    IDX_TAIL(*q)++;
    TAIL(*q) = val;
  }
}
void dequeue(Queue *q, ElType *val){
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., HEAD dan IDX_HEAD "mundur";
        q mungkin kosong */
  if (length(*q)==1){
    *val = HEAD(*q);
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
  }
  else{
    *val = HEAD(*q);
    IDX_HEAD(*q)++;
  }
}
/* *** Display Queue *** */
void displayQueue(Queue q){
/* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara kurung
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */
  int i;
  printf("[");
  for(i = 0; i < length(q); i++){
    if (i == length(q)-1) printf("%d", q.buffer[IDX_HEAD(q)+i] );
    else printf("%d,", q.buffer[IDX_HEAD(q)+i]);
  }
  printf("]");
}
