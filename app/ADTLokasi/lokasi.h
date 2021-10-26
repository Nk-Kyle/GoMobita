/* File : lokasi.h
   Definisi ADT Lokasi berupa struct char dengan POINT
   lokname merupakan nama lokasi dan coord merupakan point */
#ifndef LOKASI_H
#define LOKASI_H

#include "../boolean.h"
#include "../ADTPOINT/point.h"

#define IDX_UNDEF -1

typedef struct {
  POINT coord;
  char locname;
} Loc;

/* SELEKTOR LOKASI */
#define Name(L) (L).locname // A, B, 8, ...
#define Coor(L) (L).coord // POINT (x,y)

/* Definisi Prototipe Primitif */
/* Konstruktor */
Loc MakeLoc (char name, int x, int y);
/* Konstruktor Loc L dengan Name(L) diisi name
   Coor(L) berupa point dengan Absis x dan Ordinat y */

void DispLoc (Loc l);
/* Menuliskan Loc dalam bentuk : lokname Absis(coord) Ordinat(coord) */

#endif
