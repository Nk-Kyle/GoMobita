#include "stackTas.h"
#include <stdio.h>

/* *** Konstruktor/Kreator *** */
void CreateTas(StackTas *s){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* - Kapasitas awal bernilai 3 */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */
  IDX_TOP(*s) = IDX_UNDEF;
  CURRENT_TAS_CAP(*s) = 3;
}

/* ************ Prototype ************ */
boolean isTasEmpty(StackTas s){
/* Mengirim true jika s kosong: lihat definisi di atas */
  return(IDX_TOP(s) == IDX_UNDEF);
}
boolean isTasFull(StackTas s){
/* Mengirim true jika tabel penampung nilai s stack penuh */
  return(IDX_TOP(s) == CURRENT_TAS_CAP(s) - 1);
}

/* ************ Menambahkan sebuah elemen ke StackTas ************ */
void pushTas(StackTas *s, Pesanan item){
/* Menambahkan item sebagai elemen StackTas s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. item menjadi TOP yang baru, IDX_TOP bertambah 1 */
  if (isTasEmpty(*s)) {
    IDX_TOP(*s) = 0;
  }
  else {
    IDX_TOP(*s)++;
  }
  TOP(*s) = item;
}

/* ************ Menghapus sebuah elemen StackTas ************ */
void popTas(StackTas *s, Pesanan *item){
/* Menghapus item dari StackTas s */
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

/* ************ Menambah kapasitas sementara Stack tas ************ */
void increaseTas(StackTas *s)
/* Meningkatkan kapasitas tas sebesar satu kali */
/* I.S. currentTasCap tas mungkin maksimal */
/* F.S. currentTasCap menjadi bertambah satu tetapi tidak melebihi batas maksimum */
{
  if (CURRENT_TAS_CAP(*s) < 100)
  {
    CURRENT_TAS_CAP(*s)++;
  }
}

/* ************ Update Stack tas ************ */
void updateTas(StackTas *s, int waktu)
/* Melakukan upate pada tas */
/* I.S. s mungkin memiliki item perishable yang sudah expired */
/* F.S. item perishable yang sudah expired akan hilang */
{
  StackTas sTemp;
  Pesanan item;

  CreateTas(&sTemp);
  while (!isTasEmpty(*s))
  {
    if (isPerishable(TOP(*s)))
    {
      if ((waktu - PickupTime(TOP(*s))) == Exp(TOP(*s)))
      {
        popTas(s, &item);
      }
      else
      {
        popTas(s, &item);
        pushTas(&sTemp, item);
      }
    }
    else
    {
      popTas(s, &item);
      pushTas(&sTemp, item);
    }
  }
  while (!isTasEmpty(sTemp))
  {
    popTas(&sTemp, &item);
    pushTas(s, item);
  }
}

/* ************ Gadget ************ */
void senterPembesar(StackTas *s)
/* Meningkatkan kapasitas tas sebesar dua kali lipat */
/* I.S. currentTasCap tas mungkin maksimal */
/* F.S. currentTasCap menjadi dua kali lipat tetapi tidak melebihi batas maksimum */
{
  CURRENT_TAS_CAP(*s) = CURRENT_TAS_CAP(*s) * 2;
  if (CURRENT_TAS_CAP(*s) > 100)
  {
    CURRENT_TAS_CAP(*s) = 100;
  }
}

int lengthTas(StackTas s){
  int cnt = 0;
  if (!isTasEmpty(s)) cnt += IDX_TOP(s) + 1;
  return cnt;
}

void reverseTas(StackTas *s){
  StackTas temp;
  Pesanan item;
  CreateTas(&temp);
  while(!isTasEmpty(*s)){
    popTas(s, &item);
    pushTas(&temp, item);
  }
  while(!isTasEmpty(temp)){
    popTas(&temp, &item);
    pushTas(s, item);
  }
}

void dispTas(StackTas s){
  Pesanan item;
  while(!isTasEmpty(s)){
    popTas(&s,&item);
    printf("Time :%d\nExp :%d\nPickupTime :%d\nPickup Place :%c\nDropoff Place: %c\nItem Type :%c\n\n",
    Time(item), Exp(item), PickupTime(item), Pickup(item), Dropoff(item), IType(item));
  }
}
