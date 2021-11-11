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
  }
  /*
  fprintf(f, "%d\n", lengthLinkedList(in_progress_list));
  p = in_progress_list;
  while (p != NULL){
    order = INFO(p);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
  }
  fprintf(f, "%s\n", lengthTas(tas));
  while (!isTasEmpty(tas)){
    popTas(&tas, &order);
    fprintf(f, "%d %c %c %c %d %d\n", Time(order), Pickup(order), Dropoff(order), IType(order), Exp(order), PickupTime(order));
  }
  for (int i = 0 ; i < 5 ; i++){
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
