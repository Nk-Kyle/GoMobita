#include "list_linked.h"
#include "node.h"
#include "../ADTItem/item.h"
#include <stdio.h>

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateLinkedList(LinkedList *l)
{
  /* I.S. sembarang             */
  /* F.S. Terbentuk list kosong */
  *l = NULL;
}
/****************** TEST LIST KOSONG ******************/
boolean isEmptyLinkedList(LinkedList l)
{
  /* Mengirim true jika list kosong */
  return (l == NULL);
}
/****************** GETTER SETTER ******************/
Pesanan getElmtLinkedList(LinkedList l, int idx)
{
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengembalikan nilai elemen l pada indeks idx */
  int cnt = 0;
  Address p;
  p = l;
  while (cnt < idx)
  {
    p = NEXT(p);
    cnt++;
  }
  return INFO(p);
}

void setElmtLinkedList(LinkedList *l, int idx, Pesanan val)
{
  /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
  int cnt = 0;
  Address p;
  p = *l;
  while (cnt < idx)
  {
    p = NEXT(p);
    cnt++;
  }
  INFO(p) = val;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertLinkedListFirst(LinkedList *l, Pesanan val)
{
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
  /* Jika alokasi gagal: I.S.= F.S. */
  Address p;
  p = newNode(val);
  if (p != NULL)
  {
    NEXT(p) = *l;
    *l = p;
  }
}

void insertLinkedListLast(LinkedList *l, Pesanan val)
{
  /* I.S. l mungkin kosong */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menambahkan elemen list di akhir: elemen terakhir yang baru */
  /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  Address pin, ptrav;
  pin = newNode(val);
  if (isEmptyLinkedList(*l))
    insertLinkedListFirst(l, val);
  else
  { // list tidak kosong
    if (pin != NULL)
    {
      ptrav = *l;
      while (NEXT(ptrav) != NULL)
      {
        ptrav = NEXT(ptrav);
      }
      NEXT(ptrav) = pin;
    }
  }
}

void insertLinkedListAt(LinkedList *l, Pesanan val, int idx)
{
  /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. Melakukan alokasi sebuah elemen dan */
  /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
  /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  Address pin, ptrav;
  int cnt = 0;
  if (idx == 0)
    insertLinkedListFirst(l, val);
  else
  {
    pin = newNode(val);
    if (pin != NULL)
    {
      ptrav = *l;
      while (cnt < idx - 1)
      {
        ptrav = NEXT(ptrav);
        cnt++;
      }
      NEXT(pin) = NEXT(ptrav);
      NEXT(ptrav) = pin;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteLinkedListFirst(LinkedList *l, Pesanan *val)
{
  /* I.S. LinkedList l tidak kosong  */
  /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen pertama di-dealokasi */
  Address p;
  p = *l;
  *val = INFO(p);
  *l = NEXT(p);
  free(p);
}

void deleteLinkedListLast(LinkedList *l, Pesanan *val)
{
  /* I.S. list tidak kosong */
  /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
  /*      dan alamat elemen terakhir di-dealokasi */
  Address pout, ptrav;
  ptrav = NULL;
  pout = *l;
  while (NEXT(pout) != NULL)
  {
    ptrav = pout;
    pout = NEXT(pout);
  }
  *val = INFO(pout);
  if (ptrav == NULL)
    *l = NULL;
  else
    NEXT(ptrav) = NULL;
  free(pout);
}

void deleteLinkedListAt(LinkedList *l, int idx, Pesanan *val)
{
  /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
  /* F.S. val diset dengan elemen l pada indeks ke-idx. */
  /*      Elemen l pada indeks ke-idx dihapus dari l */
  int cnt;
  Address pout, ptrav;
  if (idx == 0)
    deleteLinkedListFirst(l, val);
  else
  {
    cnt = 0;
    ptrav = *l;
    while (cnt < idx - 1)
    {
      ptrav = NEXT(ptrav);
      cnt++;
    }
    pout = NEXT(ptrav);
    *val = INFO(pout);
    NEXT(ptrav) = NEXT(pout);
    free(pout);
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayLinkedList(LinkedList l)
{
  // void printInfo(LinkedList l);
  /* I.S. LinkedList mungkin kosong */
  /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
  /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
  /* Jika list kosong : menulis [] */
  /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
  Address p;
  p = l;
  if (isEmptyLinkedList(l))
    printf("[]");
  else
  {
    printf("[");
    while (NEXT(p) != NULL)
    {
      printf("%d,", INFO(p));
      p = NEXT(p);
    }
    // last element;
    printf("%d]", INFO(p));
  }
}

int lengthLinkedList(LinkedList l)
{
  /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int cnt = 0;
  Address p;
  p = l;
  if (!isEmptyLinkedList(l))
  {
    while (NEXT(p) != NULL)
    {
      cnt++;
      p = NEXT(p);
    }
    cnt++;
  }
  return cnt;
}

/****************** OPERASI MOBITA ******************/
void updateToDoList(PrioQueue *daftarPesanan, LinkedList *toDoList, int waktu)
{
  if (!isEmpty(*daftarPesanan))
  {
    while (HEAD(*daftarPesanan).time <= waktu)
    {
      Pesanan temp;
      dequeue(daftarPesanan, &temp);
      insertLinkedListLast(toDoList, temp);
    }
  }
}

void updateInProgressList(LinkedList *in_progress_list, int waktu)
{
  Address p;
  Pesanan val;
  int i;
  p = FIRST(*in_progress_list);
  i = 0;
  while (p != NULL)
  {
    if (INFO(p).itype == 'P')
    {
      if (waktu - INFO(p).pickuptime == INFO(p).exp)
      {
        deleteLinkedListAt(in_progress_list, i, &val);
      }
    }
    p = NEXT(p);
    i++;
  }
};

boolean isPickUpAble(LinkedList *to_do_list, Loc mobita)
{
  Address p;
  p = FIRST(*to_do_list);
  while (p != NULL)
  {
    if (INFO(p).pickup == mobita.locname)
    {
      return true;
    }
    p = NEXT(p);
  }
  return false;
};

void removePesananDariToDo(LinkedList *to_do_list, Loc mobita, Pesanan *val)
{
  Address p;
  p = FIRST(*to_do_list);
  boolean found = false;
  while (!found)
  {
    if (INFO(p).pickup == mobita.locname)
    {
      *val = INFO(p);
      found = true;
    }
    else
    {
      p = NEXT(p);
    }
  }
};

void useKainPembungkusWaktu(LinkedList *in_progress_list, StackTas *tas, int waktu)
{
  if (TOP(*tas).itype == 'P')
  {
    TOP(*tas).pickuptime = waktu;
    FIRST(*in_progress_list)->info.pickuptime = waktu;
  }
  else
  {
    printf("Tidak ada barang perishable yang dikembalikan waktu expirednya\n");
  }
};

void useMesinWaktu(LinkedList *in_progress_list, StackTas *tas, int *waktu)
{
  Address p;
  StackTas tempTas;
  Pesanan val;
  *waktu -= 50;
  if (*waktu < 0)
  {
    *waktu = 0;
  }
  // ngerefresh barang di to_do_list
  p = FIRST(*in_progress_list);
  while (p != NULL)
  {
    if (INFO(p).itype == 'P')
    {
      INFO(p).pickuptime = *waktu;
    }
    p = NEXT(p);
  }

  // ngerefresh barang di tas
  CreateTas(&tempTas);
  tempTas.currentTasCap = 100;
  while (!isTasEmpty(*tas))
  {
    popTas(tas, &val);
    if (val.itype == 'P')
    {
      val.pickuptime = *waktu;
    }
    pushTas(&tempTas, val);
  }
  while (!isTasEmpty(tempTas))
  {
    popTas(&tempTas, &val);
    pushTas(tas, val);
  }
};

void displayToDoList(LinkedList to_do_list)
{
  Address p;
  int i;
  if (isEmptyLinkedList(to_do_list))
  {
    printf("To Do List Kosong\n");
  }
  else
  {
    p = FIRST(to_do_list);
    i = 1;
    printf("Pesanan pada To Do List:\n");
    while (p != NULL)
    {
      printf("%d. %c --> %c (", i, p->info.pickup, p->info.dropoff);
      switch (p->info.itype)
      {
      case 'N':
        printf("Normal Item)\n");
        break;
      case 'H':
        printf("Heavy Item)\n");
      case 'P':
        printf("Perishable Item)\n");
      default:
        break;
      }
      i++;
      p = NEXT(p);
    }
  }
};

void displayInProgressList(LinkedList in_progress_list, int waktu)
{
  Address p;
  int i;
  if (isEmptyLinkedList(in_progress_list))
  {
    printf("To Do List Kosong\n");
  }
  else
  {
    p = FIRST(in_progress_list);
    i = 1;
    printf("Pesanan pada To Do List:\n");
    while (p != NULL)
    {
      printf("%d. ", i);
      switch (p->info.itype)
      {
      case 'N':
        printf("Normal Item ");
        break;
      case 'H':
        printf("Heavy Item) ");
        break;
      case 'P':
        printf("Perishable Item ");
      default:
        break;
      }
      printf("(Tujuan : %c)", p->info.dropoff);
      if (p->info.itype == 'C')
      {
        printf(", (Expired in: %d)", (p->info.exp + p->info.pickuptime - waktu));
      }
      printf("\n");
      i++;
      p = NEXT(p);
    }
  }
};
