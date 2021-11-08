/* File : list_linked.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi Address dengan pointer */
/* Pesanan adalah integer */

#ifndef LIST_H
#define LIST_H

#include "../boolean.h"
#include "node.h"
#include "../ADTQueue/prioqueue.h"
#include "../ADTStack/stackTas.h"

typedef Address LinkedList;

#define IDX_UNDEF_LL (-1)
#define FIRST(l) (l)

/* Definisi LinkedList : */
/* LinkedList kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir LinkedList: jika addressnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateLinkedList(LinkedList *l);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** TEST LIST KOSONG ******************/
boolean isEmptyLinkedList(LinkedList l);
/* Mengirim true jika list kosong */

/****************** GETTER SETTER ******************/
Pesanan getElmtLinkedList(LinkedList l, int idx);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */

void setElmtLinkedList(LinkedList *l, int idx, Pesanan val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOfLinkedList(LinkedList l, Pesanan val);
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertLinkedListFirst(LinkedList *l, Pesanan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLinkedListLast(LinkedList *l, Pesanan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void insertLinkedListAt(LinkedList *l, Pesanan val, int idx);
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteLinkedListFirst(LinkedList *l, Pesanan *val);
/* I.S. LinkedList l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
void deleteLinkedListLast(LinkedList *l, Pesanan *val);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */

void deleteLinkedListAt(LinkedList *l, int idx, Pesanan *val);
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayLinkedList(LinkedList l);
// void printInfo(LinkedList l);
/* I.S. LinkedList mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int lengthLinkedList(LinkedList l);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/****************** PROSES TERHADAP LIST ******************/
LinkedList concat(LinkedList l1, LinkedList l2);
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */

/****************** OPERASI MOBITA ******************/
void updateToDoList(PrioQueue *daftarPesanan, LinkedList *toDoList, int waktu);
/* I.S. daftarPesanan, toDoList, dan waktu terdefinisi sembarang */
/* F.S. Item yang ada di daftarPesanan yang Item.time kurang dari sama dengan
        waktu ditambahkan ke dalam toDoList */

void updateInProgressList(LinkedList *in_progress_list, int waktu);
/* I.S. in_progress_list terdefinisi dan mungkin kosong*/
/* F.S. Pesanan yang sudah expired dihapus dari in_progress_list*/

boolean isPickUpAble(LinkedList *to_do_list, Loc mobita);
/* I.S. to_do_list dan mobita terdefinisi*/
/* F.S. return true jika pada lokasi mobita ada barang yang dapat di pick up*/

void removePesananDariToDo(LinkedList *to_do_list, Loc mobita, Pesanan *val);
/* I.S. to_do_list dan mobita terdefinisi, val sembarang. dipastikan ada pesanan yang sesuai dengan lokasi mobita*/
/* F.S. mengapus pesanan dari to_do_list yang sesuai dengan lokasi mobita */

void useKainPembungkusWaktu(LinkedList *in_progress_list, StackTas *tas, int waktu);
/* I.S. in_progress_list dan tas terdefinisi dan mungkin kosong*/
/* F.S. Pesanan yang dapat expired dikembalikan ke waktu expired awal*/

void useMesinWaktu(LinkedList *in_progress_list, StackTas *tas, int *waktu);
/* I.S. in_progress_listdan tas  terdefinisi dan mungkin kosong*/
/* F.S. Mengurangi waktu sebanyak 50 satuan (minimal 0) dan Pesanan yang dapat expired dikembalikan ke waktu expired awal*/

void displayToDoList(LinkedList to_do_list);
/* I.S. to_do_list terdefinisi dan mungkin kosong*/
/* F.S. menampilkan to_do_list*/

#endif
