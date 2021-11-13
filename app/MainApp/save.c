#include <stdio.h>
#include "../ADTWordMachine/charmachine.h"
#include "../ADTWordMachine/wordmachine.h"
#include "../ADTPoint/point.h"
#include "../ADTListDin/listdin.h"
#include "../ADTLokasi/lokasi.h"
#include "../ADTMatrix/matrix.h"
#include "../ADTQueue/prioqueue.h"
#include "../ADTStack/stackTas.h"
#include "../ADTList/listGadget.h"
#include "../ADTLinkedList/list_linked.h"
#include "../ADTMap/map.h"
#include "../ADTItem/item.h"
#include "../ADTLinkedList/node.h"

void save_konfig(Loc mobita, int uang, int waktu, float waktu_speed, float satuan_waktu,
  int speed_up, int jumlah_antaran, int return_barang, PrioQueue daftar_pesanan, LinkedList to_do_list,
  LinkedList in_progress_list, StackTas tas, ListGadget inventory_gadget, Matrix adj_matrix,
  ListDin daftar_lokasi, map peta, Word namafile);

void load_konfig(Loc *mobita, int *uang, int *waktu, float *waktu_speed, float *satuan_waktu,
  int *speed_up, int *jumlah_antaran, int *return_barang, PrioQueue *daftar_pesanan, LinkedList *to_do_list,
  LinkedList *in_progress_list, StackTas *tas, ListGadget *inventory_gadget, Matrix *adj_matrix,
  ListDin *daftar_lokasi, map *peta, Word namafile);

void save_konfig(Loc mobita, int uang, int waktu, float waktu_speed, float satuan_waktu,
  int speed_up, int jumlah_antaran, int return_barang, PrioQueue daftar_pesanan, LinkedList to_do_list,
  LinkedList in_progress_list, StackTas tas, ListGadget inventory_gadget, Matrix adj_matrix,
  ListDin daftar_lokasi, map peta, Word namafile){
  Pesanan order;
  Address p;
  Loc lokasi;
  FILE * f;
  f = fopen(namafile.contents, "w");
  fprintf(f, "%d %d\n", Absis(Coor(mobita)), Ordinat(Coor(mobita)));
  fprintf(f, "%d\n", uang);
  fprintf(f, "%d\n", waktu);
  fprintf(f, "%f\n", waktu_speed);
  fprintf(f, "%f\n", satuan_waktu);
  fprintf(f, "%d\n", speed_up);
  fprintf(f, "%d\n", jumlah_antaran);
  fprintf(f, "%d\n", return_barang);
  fprintf(f, "%d\n", length(daftar_pesanan));
  while (!isEmpty(daftar_pesanan)){
    dequeue(&daftar_pesanan, &order);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
  }
  fprintf(f, "%d\n", lengthLinkedList(to_do_list));
  p = to_do_list;
  while (p != NULL){
    order = INFO(p);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
    p = NEXT(p);
  }
  fprintf(f, "%d\n", lengthLinkedList(in_progress_list));
  p = in_progress_list;
  while (p != NULL){
    order = INFO(p);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
    p = NEXT(p);
  }
  fprintf(f, "%d\n", lengthTas(tas));
  while (!isTasEmpty(tas)){
    popTas(&tas, &order);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
  }

  for (int i = 0 ; i < LISTGADGET_CAPACITY ; i++){
    if (i != 4) fprintf(f, "%d ",LGELMT(inventory_gadget,i));
    else fprintf(f, "%d\n", LGELMT(inventory_gadget,i));
  }
  fprintf(f, "%d\n", NEFF(daftar_lokasi));
  for(int i = 0; i < NEFF(daftar_lokasi); i++){
    for(int j = 0 ; j < NEFF(daftar_lokasi); j++){
      fprintf(f, "%d ", MELM(adj_matrix,i,j));
    }
    fprintf(f, "\n");
  }
  for (int i = 0 ; i < NEFF(daftar_lokasi); i++){
    lokasi = ELMT(daftar_lokasi,i);
    fprintf(f, "%c %d %d\n", Name(lokasi),Absis(Coor(lokasi)), Ordinat(Coor(lokasi)) );
  }
  fprintf(f, "%d %d\n", bariseff(peta)-2, kolomeff(peta)-2); // baris dan kolom map*/
  fclose(f);
}

void load_konfig(Loc *mobita, int *uang, int *waktu, float *waktu_speed, float *satuan_waktu,
  int *speed_up, int *jumlah_antaran, int *return_barang, PrioQueue *daftar_pesanan, LinkedList *to_do_list,
  LinkedList *in_progress_list, StackTas *tas, ListGadget *inventory_gadget, Matrix *adj_matrix,
  ListDin *daftar_lokasi, map *peta, Word namafile){
  Pesanan order;
  Loc lokasi;
  int x, y, i;
  int len;
  fstartWord(namafile.contents);
  x = getAngka();
  fadvWord();
  y = getAngka();
  Absis(Coor(*mobita)) = x;
  Ordinat(Coor(*mobita)) = y;
  fadvWord();
  *uang = getAngka();
  fadvWord();
  *waktu = getAngka();
  fadvWord();
  *waktu_speed = getFloat();
  fadvWord();
  *satuan_waktu = getFloat();
  fadvWord();
  *speed_up = getAngka();
  fadvWord();
  *jumlah_antaran = getAngka();
  fadvWord();
  *return_barang = getAngka();
  fadvWord();
  len = getAngka();
  CreatePrioQueue(daftar_pesanan);
  for (i = 0 ; i < len ; i++){
    fadvWord();
    Time(order) = getAngka();
    fadvWord();
    Pickup(order) = currentWord.contents[0];
    fadvWord();
    Dropoff(order) = currentWord.contents[0];
    fadvWord();
    IType(order) = currentWord.contents[0];
    fadvWord();
    Exp(order) = getAngka();
    fadvWord();
    PickupTime(order) = getAngka();
    penqueue(daftar_pesanan, order);
  }
  fadvWord();
  len = getAngka();
  CreateLinkedList(to_do_list);
  for (i = 0; i < len; i++){
    fadvWord();
    Time(order) = getAngka();
    fadvWord();
    Pickup(order) = currentWord.contents[0];
    fadvWord();
    Dropoff(order) = currentWord.contents[0];
    fadvWord();
    IType(order) = currentWord.contents[0];
    fadvWord();
    Exp(order) = getAngka();
    fadvWord();
    PickupTime(order) = getAngka();
    insertLinkedListLast(to_do_list, order);
  }
  fadvWord();
  len = getAngka();
  CreateLinkedList(in_progress_list);
  for (i = 0; i < len; i++){
    fadvWord();
    Time(order) = getAngka();
    fadvWord();
    Pickup(order) = currentWord.contents[0];
    fadvWord();
    Dropoff(order) = currentWord.contents[0];
    fadvWord();
    IType(order) = currentWord.contents[0];
    fadvWord();
    Exp(order) = getAngka();
    fadvWord();
    PickupTime(order) = getAngka();
    insertLinkedListLast(in_progress_list, order);
  }
  fadvWord();
  len = getAngka();
  CreateTas(tas);
  for (i = 0; i < len; i++){
    fadvWord();
    Time(order) = getAngka();
    fadvWord();
    Pickup(order) = currentWord.contents[0];
    fadvWord();
    Dropoff(order) = currentWord.contents[0];
    fadvWord();
    IType(order) = currentWord.contents[0];
    fadvWord();
    Exp(order) = getAngka();
    fadvWord();
    PickupTime(order) = getAngka();
    pushTas(tas, order);
  }
  reverseTas(tas);
  CreateListGadget(inventory_gadget);
  for (int i = 0 ; i < LISTGADGET_CAPACITY ; i++){
    fadvWord();
    LGELMT(*inventory_gadget,i) = getAngka();
  }
  fadvWord();
  len = getAngka();
  CreateMatrix(len,len,adj_matrix);
  for(int i = 0; i < len; i++){
    for(int j = 0 ; j < len; j++){
      fadvWord();
      MELM(*adj_matrix,i,j) = getAngka();
    }
  }
  CreateListDin(daftar_lokasi,len);
  for (int i = 0 ; i < len; i++){
    fadvWord();
    Name(lokasi) = currentWord.contents[0];
    fadvWord();
    Absis(Coor(lokasi)) = getAngka();
    fadvWord();
    Ordinat(Coor(lokasi)) = getAngka();
    ELMT(*daftar_lokasi,i) = lokasi;
  }
  fadvWord();
  x = getAngka();
  fadvWord();
  y = getAngka();
  makeMap(peta, x, y, *daftar_lokasi);
}
