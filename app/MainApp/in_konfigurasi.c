#include <stdio.h>
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
#include "../ADTListDin/listdin.c"
#include "../ADTLokasi/lokasi.c"
#include "../ADTMatrix/matrix.c"
#include "../ADTQueue/prioqueue.c"
int getAngka(Word currentWord);
int getAngka(Word currentWord){
  int angka = 0;
  int i;
  for (i = 0; i < currentWord.length; i++){
    angka = angka*10 + (currentWord.contents[i]- '0');
  }
  return angka;
}

int main () {
  int size_n, size_m;
  int x,y;
  int i,j;
  int n_lokasi, n_orders;
  int time, exp;
  char pickup, dropoff, itype;
  char name;
  Matrix Adj_mat;
  ListDin daftar_lokasi; //ListDin berisi Lokasi, referensi ke ADTLokasi
  PrioQueue orders;
  QElType QEl;
  fstartWord("konfigurasi.txt");
  //startWord();
  size_n = getAngka(currentWord);
  advWord();
  size_m = getAngka(currentWord);
  advWord();
  x = getAngka(currentWord);
  advWord();
  y = getAngka(currentWord);
  CreateListDin(&daftar_lokasi,1);
  insertLast(&daftar_lokasi, MakeLoc('8', x, y));
  advWord();
  n_lokasi = getAngka(currentWord);
  growList(&daftar_lokasi, n_lokasi);
  for (i = 0; i < n_lokasi; i++){
    advWord(); //Asumsi nama lokasi selalu char
    name = currentWord.contents[0];
    advWord();
    x = getAngka(currentWord);
    advWord();
    y = getAngka(currentWord);
    insertLast(&daftar_lokasi, MakeLoc(name,x,y));
  }
  CreateMatrix(n_lokasi+1, n_lokasi+1, &Adj_mat);
  for (i = 0; i < n_lokasi+1; i++){
    for (j = 0; j < n_lokasi+1; j++){
      advWord();
      x = getAngka(currentWord);
      MELM(Adj_mat,i,j) = x;
    }
  }
  CreatePrioQueue(&orders);
  advWord();
  n_orders = getAngka(currentWord);
  for (i = 0; i < n_orders; i++){
    advWord();
    QEl.time = getAngka(currentWord);
    advWord();
    QEl.pickup = currentWord.contents[0];
    advWord();
    QEl.dropoff = currentWord.contents[0];
    advWord();
    QEl.itype = currentWord.contents[0];
    if (QEl.itype == 'P'){
      advWord();
      QEl.exp = getAngka(currentWord);
    }
    else QEl.exp = -1;
    penqueue(&orders, QEl);
  }
  displayPQueue(orders);
}
