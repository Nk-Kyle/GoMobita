/* File : item.h
   Definisi ADT Item berupa struct char, LOC, dan int */

#ifndef ITEM_H
#define ITEM_H

#include "../boolean.h"

#define IDX_UNDEF -1

typedef struct
{
	int time;	  /* waktu pesanan masuk */
	int exp;	  /* waktu pesanan hangus
						  -1 untuk pesanan yang tidak akan hangus */
	char pickup;  /* tempat pengambilan barang */
	char dropoff; /* tujuan pengiriman barang */
	char itype;	  /* tipe barang */
} QElType;

/* ********* AKSES (Selektor) ********* */
/* Jika I adalah QElType, maka akses elemen : */
#define    Time(I) (I).time
#define     Exp(I) (I).exp
#define  Pickup(I) (I).pickup
#define Dropoff(I) (I).dropoff
#define    Type(I) (I).itype

/* ************ Prototype ************ */
boolean isNormal(QElType I);
/* Mengirim true jika item bertipe normal */
boolean isHeavy(QElType I);
/* Mengirim true jika item bertipe heavy */
boolean isPerishable(QElType I);
/* Mengirim true jika item bertipe perishable */

#endif
