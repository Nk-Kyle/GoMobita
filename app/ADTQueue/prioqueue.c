#include "prioqueue.h"
#include <stdio.h>

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq)
{
  /* I.S. sembarang */
  /* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
  /* - Index head bernilai IDX_UNDEF */
  /* - Index tail bernilai IDX_UNDEF */
  /* Proses : Melakukan alokasi, membuat sebuah pq kosong */
  IDX_HEAD(*pq) = IDX_UNDEF;
  IDX_TAIL(*pq) = IDX_UNDEF;
}

boolean isEmpty(PrioQueue pq)
{
  /* Mengirim true jika pq kosong: lihat definisi di atas */
  return (IDX_HEAD(pq) == IDX_UNDEF && IDX_TAIL(pq) == IDX_UNDEF);
}
boolean isFull(PrioQueue pq)
{
  /* Mengirim true jika tabel penampung elemen pq sudah penuh */
  /* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */
  return (IDX_HEAD(pq) == 0 && IDX_TAIL(pq) == CAPACITY - 1);
}
int length(PrioQueue pq)
{
  /* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika pq kosong. */
  if (isEmpty(pq))
    return 0;
  else
    return (IDX_TAIL(pq) - IDX_HEAD(pq) + 1);
}
/*** Primitif Add/Delete ***/
void enqueue(PrioQueue *q, ElType val)
{
  /* Proses: Menambahkan val pada q dengan aturan FIFO */
  /* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
  /* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
          Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
          menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
  int idx;
  if (isEmpty(*q))
  {
    IDX_HEAD(*q) = 0;
    IDX_TAIL(*q) = 0;
    TAIL(*q) = val;
  }
  else if (IDX_TAIL(*q) == CAPACITY - 1)
  {
    for (idx = 0; idx < length(*q); idx++)
    {
      (*q).buffer[idx] = (*q).buffer[IDX_HEAD(*q) + idx];
    }
    IDX_TAIL(*q) = CAPACITY - 1 - IDX_HEAD(*q);
    IDX_HEAD(*q) = 0;
    IDX_TAIL(*q)
    ++;
    TAIL(*q) = val;
  }
  else
  {
    IDX_TAIL(*q)
    ++;
    TAIL(*q) = val;
  }
}

void penqueue(PrioQueue *pq, ElType val)
{
  /* Proses: menambah val secara terurut membesar berdasarkan time*/
  /* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
  /* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
      Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen pq
      menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
  PrioQueue temppq;
  ElType tempEl;
  if (isEmpty(*pq))
  {
    enqueue(pq, val);
  }
  else
  {
    CreatePrioQueue(&temppq);
    while (!isEmpty(*pq))
    {
      dequeue(pq, &tempEl);
      if (tempEl.time > val.time)
      {
        enqueue(&temppq, val);
        enqueue(&temppq, tempEl);
        while (!isEmpty(*pq))
        {
          dequeue(pq, &tempEl);
          enqueue(&temppq, tempEl);
        }
      }
      else
      {
        enqueue(&temppq, tempEl);
      }
    }
    while (!isEmpty(temppq))
    {
      dequeue(&temppq, &tempEl);
      enqueue(pq, tempEl);
    }
  }
};

void dequeue(PrioQueue *pq, ElType *val)
{
  /* Proses: Menghapus val pada q dengan aturan FIFO */
  /* I.S. pq tidak mungkin kosong */
  /* F.S. val = nilai elemen HEAD pd
  I.S., HEAD dan IDX_HEAD "mundur";
          pq mungkin kosong */
  if (length(*pq) == 1)
  {
    *val = HEAD(*pq);
    IDX_HEAD(*pq) = IDX_UNDEF;
    IDX_TAIL(*pq) = IDX_UNDEF;
  }
  else
  {
    *val = HEAD(*pq);
    IDX_HEAD(*pq)
    ++;
  }
}

void displayPQueue(PrioQueue pq)
{
  int i, l;
  l = length(pq);
  for (i = 0; i < l; i++)
  {
    printf("%d %c %c %c %d\n", pq.buffer[i].time, pq.buffer[i].pickup, pq.buffer[i].dropoff, pq.buffer[i].type, pq.buffer[i].exp);
  }
};