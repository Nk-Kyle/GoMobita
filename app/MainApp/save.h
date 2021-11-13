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
#include "boolean.h"

void save_konfig(Loc mobita, int uang, int waktu, float waktu_speed, float satuan_waktu,
                 int speed_up, int jumlah_antaran, int return_barang, PrioQueue daftar_pesanan, LinkedList to_do_list,
                 LinkedList in_progress_list, StackTas tas, ListGadget inventory_gadget, Matrix adj_matrix,
                 ListDin daftar_lokasi, map peta, Word namafile, boolean senter_pengecil);

void load_konfig(Loc *mobita, int *uang, int *waktu, float *waktu_speed, float *satuan_waktu,
                 int *speed_up, int *jumlah_antaran, int *return_barang, PrioQueue *daftar_pesanan, LinkedList *to_do_list,
                 LinkedList *in_progress_list, StackTas *tas, ListGadget *inventory_gadget, Matrix *adj_matrix,
                 ListDin *daftar_lokasi, map *peta, Word namafile, boolean *senter_pengecil);