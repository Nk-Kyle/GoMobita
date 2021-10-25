#include <stdio.h>
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
#include "../ADTListDin/listdin.c"
#include "../ADTLokasi/lokasi.c"
#include "../ADTMatrix/matrix.c"
#include "../ADTQueue/prioqueue.c"
void konfig (Matrix *Adj_mat, ListDin *Daftar_lokasi, PrioQueue *orders);
void konfig (Matrix *Adj_mat, ListDin *Daftar_lokasi, PrioQueue *orders) {
  int size_n, size_m;
  int x,y;
  int i,j;
  int n_lokasi, n_orders;
  int time, exp;
  char pickup, dropoff, itype;
  char name;
  QElType QEl;
  fstartWord("konfigurasi.txt");
  //startWord();
  size_n = getAngka(currentWord);
  fadvWord();
  size_m = getAngka(currentWord);
  fadvWord();
  x = getAngka(currentWord);
  fadvWord();
  y = getAngka(currentWord);
  CreateListDin(daftar_lokasi,1);
  insertLast(daftar_lokasi, MakeLoc('8', x, y));
  fadvWord();
  n_lokasi = getAngka(currentWord);
  growList(daftar_lokasi, n_lokasi);
  for (i = 0; i < n_lokasi; i++){
    fadvWord(); //Asumsi nama lokasi selalu char
    name = currentWord.contents[0];
    fadvWord();
    x = getAngka(currentWord);
    fadvWord();
    y = getAngka(currentWord);
    insertLast(daftar_lokasi, MakeLoc(name,x,y));
  }
  CreateMatrix(n_lokasi+1, n_lokasi+1, Adj_mat);
  for (i = 0; i < n_lokasi+1; i++){
    for (j = 0; j < n_lokasi+1; j++){
      fadvWord();
      x = getAngka(currentWord);
      MELM(*Adj_mat,i,j) = x;
    }
  }
  CreatePrioQueue(orders);
  fadvWord();
  n_orders = getAngka(currentWord);
  for (i = 0; i < n_orders; i++){
    fadvWord();
    QEl.time = getAngka(currentWord);
    fadvWord();
    QEl.pickup = currentWord.contents[0];
    fadvWord();
    QEl.dropoff = currentWord.contents[0];
    fadvWord();
    QEl.itype = currentWord.contents[0];
    if (QEl.itype == 'P'){
      fadvWord();
      QEl.exp = getAngka(currentWord);
    }
    else QEl.exp = -1;
    penqueue(orders, QEl);
  }
}
