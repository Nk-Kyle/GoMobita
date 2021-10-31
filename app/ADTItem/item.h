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
	int pickuptime;  /*waktu barang di pickup
						  -1 untuk pesanan yang belum dipickup*/
	char pickup;  /* tempat pengambilan barang */
	char dropoff; /* tujuan pengiriman barang */
	char itype;	  /* tipe barang */
} Pesanan;

/* ********* AKSES (Selektor) ********* */
/* Jika I adalah Pesanan, maka akses elemen : */
#define    Time(I) (I).time
#define     Exp(I) (I).exp
#define	PickupTime(I) (I).pickuptime
#define  Pickup(I) (I).pickup
#define Dropoff(I) (I).dropoff
#define    IType(I) (I).itype

/* ************ Prototype ************ */
boolean isNormal(Pesanan I);
/* Mengirim true jika item bertipe normal */
boolean isHeavy(Pesanan I);
/* Mengirim true jika item bertipe heavy */
boolean isPerishable(Pesanan I);
/* Mengirim true jika item bertipe perishable */

boolean isPesananSama(Pesanan i1, Pesanan i2);
/* Mengirim true jika pesanan 1 = pesanan 2*/

#endif
