/* File : item.h
   Definisi ADT Item berupa struct char, LOC, dan int */

#ifndef ITEM_H
#define ITEM_H

#include "../boolean.h"
#include "../ADTLokasi/lokasi.h"

#define IDX_UNDEF -1

typedef struct {
    int tMasuk;
    Loc locPick;
    Loc locDrop;
    char type;
    int tHangus;    /* item non-perishable akan memiliki tHangus == -1 */
} Item;

/* ********* AKSES (Selektor) ********* */
/* Jika I adalah Item, maka akses elemen : */
#define  TMasuk(I) (I).tMasuk
#define LocPick(I) (I).locPick
#define LocDrop(I) (I).locDrop
#define    Type(I) (I).type
#define THangus(I) (I).tHangus

#endif
