/* File : item.h
   Definisi ADT Item berupa struct char, LOC, dan int */

#ifndef ITEM_H
#define ITEM_H

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

#endif
