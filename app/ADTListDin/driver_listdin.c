#include "listdin.c"
#include "../ADTPoint/point.c"
#include "../ADTLokasi/lokasi.c"
int main() {
  ListDin l;
  CreateListDin(&l, 1);
  readList(&l);
  displayList(l);
  growList(&l, 1);
  insertLast(&l, MakeLoc('G', 99, 88));
  displayList(l);
  return 0;
}
