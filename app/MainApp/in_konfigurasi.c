#include "in_konfigurasi.h"
void konfig(Matrix *Adj_mat, ListDin *daftar_lokasi, PrioQueue *orders, boolean *berhasil, Word namafile, map *map)
{
  int size_n, size_m;
  int x, y;
  int i, j;
  int n_lokasi, n_orders;
  int time, exp;
  char pickup, dropoff, itype;
  char name;
  Pesanan QEl;
  namafile = concat("data/", namafile);
  fstartWord(namafile.contents);
  if (ftape == NULL) {
    *berhasil = false;
  }
  else {
    size_n = getAngka();
    fadvWord();
    size_m = getAngka();
    fadvWord();
    x = getAngka();
    fadvWord();
    y = getAngka();
    CreateListDin(daftar_lokasi, 1);
    insertLast(daftar_lokasi, MakeLoc('8', x, y));
    fadvWord();
    n_lokasi = getAngka();
    growList(daftar_lokasi, n_lokasi);
    for (i = 0; i < n_lokasi; i++)
    {
      fadvWord(); // Asumsi nama lokasi selalu char
      name = currentWord.contents[0];
      fadvWord();
      x = getAngka();
      fadvWord();
      y = getAngka();
      insertLast(daftar_lokasi, MakeLoc(name, x, y));
    }
    CreateMatrix(n_lokasi + 1, n_lokasi + 1, Adj_mat);
    for (i = 0; i < n_lokasi + 1; i++)
    {
      for (j = 0; j < n_lokasi + 1; j++)
      {
        fadvWord();
        x = getAngka();
        MELM(*Adj_mat, i, j) = x;
      }
    }
    makeMap(map, size_n, size_m, *daftar_lokasi);
    CreatePrioQueue(orders);
    fadvWord();
    n_orders = getAngka();
    for (i = 0; i < n_orders; i++)
    {
      fadvWord();
      QEl.time = getAngka();
      fadvWord();
      QEl.pickup = currentWord.contents[0];
      fadvWord();
      QEl.dropoff = currentWord.contents[0];
      fadvWord();
      QEl.itype = currentWord.contents[0];
      if (QEl.itype == 'P')
      {
        fadvWord();
        QEl.exp = getAngka();
        QEl.pickuptime = -1;
      }
      else
      {
        QEl.exp = -1;
        QEl.pickuptime = -1;
      }
      penqueue(orders, QEl);
    }
    *berhasil = true;
    fclose(ftape);
  }
}
