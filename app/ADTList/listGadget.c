#include <stdio.h>
#include "listGadget.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListGadget(ListGadget *l)
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
{
    for (int i = 0; i < LISTGADGET_CAPACITY; i++)
    {
        LGELMT(*l, i) = VAL_UNDEF;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* ********** Test Indeks yang valid ********** */
boolean isIdxGadgetEff(ListGadget l, int i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
{
    return (LGELMT(l, i) != VAL_UNDEF);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isGadgetEmpty(ListGadget l)
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
{
    int i = 0;

    while (i < LISTGADGET_CAPACITY)
    {
        if (isIdxGadgetEff(l, i))
        {
            return false;
        }
        i++;
    }

    return true;
}
/* *** Test List penuh *** */
boolean isGadgetFull(ListGadget l)
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
{
    int i = 0;

    while (i < LISTGADGET_CAPACITY)
    {
        if (!isIdxGadgetEff(l, i))
        {
            return false;
        }
        i++;
    }

    return true;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void displayListGadget(ListGadget l)
/* Proses : Menuliskan isi List dengan traversal */
/* I.S. l boleh kosong */
/* F.S. l ditampilkan ke layar */
{
    for (int i = 0; i < LISTGADGET_CAPACITY; i++)
    {
        printf("%d. ", (i + 1));
        if (LGELMT(l, i) == 1)
        {
            printf("Kain Pembungkus Waktu\n");
        }
        else if (LGELMT(l, i) == 2)
        {
            printf("Senter Pembesar\n");
        }
        else if (LGELMT(l, i) == 3)
        {
            printf("Pintu Kemana Saja\n");
        }
        else if (LGELMT(l, i) == 4)
        {
            printf("Mesin Waktu\n");
        }
        else
        {
            printf("-\n");
        }
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfGadg(ListGadget l, ElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan LGELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
{
    int i = 0;

    while (i < LISTGADGET_CAPACITY)
    {
        if (LGELMT(l, i) == val)
        {
            return i;
        }
        i++;
    }

    return IDX_UNDEF;
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN ********** */
/* *** Menambahkan elemen *** */
void insertGadget(ListGadget *l, ElType val)
/* Proses: Menambahkan val sebagai elemen List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen l yang baru */
{
    int i = 0;
    int idxInsert;
    boolean found = false;

    if (!isGadgetFull(*l))
    {
        while ((i < LISTGADGET_CAPACITY) && !found)
        {
            if (!isIdxGadgetEff(*l, i))
            {
                idxInsert = i;
                found = true;
            }
            i++;
        }

        LGELMT(*l, idxInsert) = val;
    }
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteGadget(ListGadget *l, int idxDelete, ElType *val)
/* Proses : Menghapus elemen List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{
    int i = 0;

    *val = LGELMT(*l, idxDelete);
    LGELMT(*l, idxDelete) = VAL_UNDEF;
}
