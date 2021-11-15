#include "map.c"
#include "../MainApp/in_konfigurasi.c"
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
#include "../ADTListDin/listdin.c"
#include "../ADTLokasi/lokasi.c"
#include "../ADTMatrix/matrix.c"
#include "../ADTQueue/prioqueue.c"
#include "../ADTColor/pcolor.c"
#include "../ADTLinkedList/list_linked.c"
#include "../ADTLinkedList/node.c"
#include "../ADTItem/item.c"
#include "../ADTStack/stackTas.c"

int main() {
  Matrix Adj_Mat;
  ListDin daftar_lokasi;
  PrioQueue Orders;
  boolean berhasil;
  Word namafile;
  Loc mobita;
  LinkedList ToDo;
  Pesanan val;
  map m;
  StackTas tas;
  CreateTas(&tas);
  namafile = makeWord("a.txt");
  konfig(&Adj_Mat,&daftar_lokasi,&Orders,namafile,&m);
  mobita = MakeLoc('8',1,1);
  dequeue(&Orders, &val);
  CreateLinkedList(&ToDo);
  insertLinkedListFirst(&ToDo, val);
  printMap(m,daftar_lokasi,Adj_Mat,mobita,ToDo,tas);
}
