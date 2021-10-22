/*
NIM : 13520040
Nama  : Ng Kyle
Tanggal : 7 Oktober 2021
Topik praktikum :ADT Queue
Deskripsi : Implementasi ADT PriorityQueue
*/

#include "prioqueue.h"
#include <stdio.h>

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq){
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */
  IDX_HEAD(*pq) = IDX_UNDEF;
  IDX_TAIL(*pq) = IDX_UNDEF;

}

boolean isEmpty(PrioQueue pq){
/* Mengirim true jika pq kosong: lihat definisi di atas */
  return (IDX_HEAD(pq) == IDX_UNDEF && IDX_TAIL(pq) == IDX_UNDEF);
}
boolean isFull(PrioQueue pq){
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */
  return (IDX_HEAD(pq) == 0 && IDX_TAIL(pq) == CAPACITY-1);
}
int length(PrioQueue pq){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
  if(isEmpty(pq)) return 0;
  else return (IDX_TAIL(pq)-IDX_HEAD(pq)+1);
}
/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *pq, ElType val){
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
  int idx, i;
  if (isEmpty(*pq)){
    IDX_HEAD(*pq) = 0;
    IDX_TAIL(*pq) = 0;
    TAIL(*pq) = val;
  }
  else{
    if(IDX_TAIL(*pq) == CAPACITY-1){
      for(idx = 0; idx < length(*pq); idx++){
        (*pq).buffer[idx] = (*pq).buffer[IDX_HEAD(*pq)+idx];
      }
      IDX_TAIL(*pq) = CAPACITY-1-IDX_HEAD(*pq);
      IDX_HEAD(*pq) = 0;
    }
    idx = 0;
    while((*pq).buffer[idx].score > val.score  && idx < length(*pq)){
      idx++;
    } //val.score <= buffer || idx == length(*pq)-1 (idx akhir)
    if (val.score == (*pq).buffer[idx].score) {
      while((*pq).buffer[idx].tArrival < val.tArrival && val.score == (*pq).buffer[idx].score  && idx < length(*pq)){
        idx++;
      } //val.tArrival >= buffer || idx akhir
      if(val.tArrival == (*pq).buffer[idx].tArrival && idx < length(*pq)){
        while((*pq).buffer[idx].tArrival == val.tArrival && val.score == (*pq).buffer[idx].score){
          idx++;
        } // buffer != val.tArrival
      }
    }
    for(i = IDX_TAIL(*pq) ; i >= idx ; i--){
      (*pq).buffer[i+1] = (*pq).buffer[i];
    }
    (*pq).buffer[idx] = val;
    IDX_TAIL(*pq)++;
  }
}
void dequeue(PrioQueue * pq, ElType *val){
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd
I.S., HEAD dan IDX_HEAD "mundur";
        pq mungkin kosong */
  if (length(*pq)==1){
    *val = HEAD(*pq);
    IDX_HEAD(*pq) = IDX_UNDEF;
    IDX_TAIL(*pq) = IDX_UNDEF;
  }
  else{
    *val = HEAD(*pq);
    IDX_HEAD(*pq)++;
  }
}

void displayPQueue(PrioQueue q){
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
    if (i == length(q)-1) printf("[%d,%d,%d]", q.buffer[IDX_HEAD(q)+i].id, q.buffer[IDX_HEAD(q)+i].tArrival ,q.buffer[IDX_HEAD(q)+i].score);
    else printf("[%d,%d,%d];", q.buffer[IDX_HEAD(q)+i].id, q.buffer[IDX_HEAD(q)+i].tArrival ,q.buffer[IDX_HEAD(q)+i].score);
  }
  printf("]\n");
}
