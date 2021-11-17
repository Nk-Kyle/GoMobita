#include "map.h"
#include "../ADTColor/pcolor.h"
#include <stdio.h>
#include "../ADTWordMachine/charmachine.h"
#include "../ADTWordMachine/wordmachine.h"
void CreateMap(int i, int j, map *m)
{
  bariseff(*m) = i;
  kolomeff(*m) = j;
}

void makeBorder(map *m, int bar, int kol)
{
  int i, j;
  bar = bar + 2;
  kol = kol + 2;
  CreateMap(bar, kol, m);
  for (i = 0; i <= bar - 1; i++)
  {
    for (j = 0; j <= kol - 1; j++)
    {
      if (i == 0)
      {
        ELMTMap(*m, i, j) = '*';
      }
      else if (i == bar - 1)
      {
        ELMTMap(*m, i, j) = '*';
      }
      else if (j == 0)
      {
        ELMTMap(*m, i, j) = '*';
      }
      else if (j == kol - 1)
      {
        ELMTMap(*m, i, j) = '*';
      }
      else
      {
        ELMTMap(*m, i, j) = ' ';
      }
    }
  }
}

void makeMap(map *m, int bar, int kol, ListDin daftar_lokasi)
{
  int k;
  int a, b;
  char c;
  makeBorder(m, bar, kol);
  for (k = 0; k < lengthList(daftar_lokasi); k++)
  {
    a = daftar_lokasi.buffer[k].coord.X;
    b = daftar_lokasi.buffer[k].coord.Y;
    c = daftar_lokasi.buffer[k].locname;
    ELMTMap(*m, a, b) = c;
  }
}

void printMap(map m, ListDin daftar_lokasi, Matrix mat_adj, Loc mobita, LinkedList ToDo, StackTas Tas)
{
  int i, j, k, l;
  boolean foundLoc;
  char mobita_c, curr_c;
  char warna[lengthList(daftar_lokasi)];
  Address p;
  mobita_c = Name(mobita); // char lokasi (nama lokasi mobita)
  foundLoc = false;
  i = 0;
  while (!foundLoc)
  {
    if (Name(ELMT(daftar_lokasi, i)) == mobita_c)
      foundLoc = true;
    else
      i++;
  }
  // Ketemu indeks lokasi mobita sekarang
  for (j = 0; j < lengthList(daftar_lokasi); j++)
  {
    if (MELM(mat_adj, i, j) == 1)
      warna[j] = 'G';
    else
      warna[j] = 'N';
  }
  p = ToDo;
  foundLoc = false;
  while (p != NULL)
  {
    curr_c = Pickup(INFO(p));
    j = 0;
    foundLoc = false;
    while (!foundLoc)
    {
      if (Name(ELMT(daftar_lokasi, j)) == curr_c)
        foundLoc = true;
      else
        j++;
    }
    warna[j] = 'R';
    p = NEXT(p);
  }
  if (!isTasEmpty(Tas))
  {
    curr_c = Dropoff(TOP(Tas));
    j = 0;
    foundLoc = false;
    while (!foundLoc)
    {
      if (Name(ELMT(daftar_lokasi, j)) == curr_c)
        foundLoc = true;
      else
        j++;
    }
    warna[j] = 'B';
  }
  j = 0;
  foundLoc = false;
  while (!foundLoc)
  {
    if (Name(ELMT(daftar_lokasi, j)) == mobita_c)
      foundLoc = true;
    else
      j++;
  }
  warna[j] = 'Y';
  for (i = 0; i < bariseff(m); i++)
  {
    for (j = 0; j < kolomeff(m); j++)
    {
      curr_c = ELMTMap(m, i, j);
      if (curr_c == '*' || curr_c == ' ')
        printf("%c", curr_c);
      else
      {
        k = 0;
        foundLoc = false;
        while (!foundLoc)
        {
          if (Name(ELMT(daftar_lokasi, k)) == curr_c)
            foundLoc = true;
          else
            k++;
        }
        switch (warna[k])
        {
        case 'Y':
          print_yellow(curr_c);
          break;
        case 'R':
          print_red(curr_c);
          break;
        case 'B':
          print_blue(curr_c);
          break;
        case 'G':
          print_green(curr_c);
          break;
        default:
          printf("%c", curr_c);
        }
      }
    }
    printf("\n");
  }
}

char convertToChar(int val, ListDin daftar_lokasi)
{
  int i;
  char c;
  boolean found;
  found = false;
  i = 0;
  while ((i <= getLastIdx(daftar_lokasi)) && !(found))
  {
    if (i == val)
    {
      c = daftar_lokasi.buffer[i].locname;
      found = true;
    }
    i++;
  }
  return c;
}

int convertToInt(char val, ListDin daftar_lokasi)
{
  int hasil;
  int i = 0;
  boolean found = false;
  while (i <= getLastIdx(daftar_lokasi) && !(found))
  {
    if (daftar_lokasi.buffer[i].locname == val)
    {
      hasil = i;
      found = true;
    }
    i++;
  }
  return hasil;
}

void move(Matrix matAjc, ListDin daftar_lokasi, Loc *mobita)
{
  char lokasiNow;
  int i, j, k, l, m;
  int pilih;
  int locx, locy;
  POINT p;
  ListDin posisiCapai;
  CreateListDin(&posisiCapai, 1);
  lokasiNow = Name(*mobita);
  i = convertToInt(lokasiNow, daftar_lokasi);
  l = 1;
  printf("Posisi yang dapat dicapai :\n");
  for (j = 0; j <= getLastIdxCol(matAjc); j++)
  {
    if (MELM(matAjc, i, j) == 1)
    {
      char a = convertToChar(j, daftar_lokasi);
      for (k = 0; k <= getLastIdx(daftar_lokasi); k++)
      {
        if (daftar_lokasi.buffer[k].locname == a)
        {
          locx = daftar_lokasi.buffer[k].coord.X;
          locy = daftar_lokasi.buffer[k].coord.Y;
          growList(&posisiCapai, 1);
          insertLast(&posisiCapai, MakeLoc(a, locx, locy));
        }
      }
      printf("%d. %c(%d,%d)\n", l, a, locx, locy);
      l++;
    }
  }

  printf("Posisi yang dipilih yang dipilih: ");
  advWord();
  pilih = getAngka();
  printf("nilai k: %d\nnilai pilihan: %d\n")
  while ( pilih < 1 || pilih > k){
    printf("Masukkan tidak valid. Ulangi\n");
    scanf("%d", &pilih);
 }

  Absis(p) = posisiCapai.buffer[pilih - 1].coord.X;
  Ordinat(p) = posisiCapai.buffer[pilih - 1].coord.Y;
  Coor(*mobita) = p;
  Name(*mobita) = posisiCapai.buffer[pilih - 1].locname;
  printf("Mobita sekarang ada di titik %c (%d,%d)\n", Name(*mobita), Absis(p), Ordinat(p));
}

void pintuKemanaSaja(ListDin daftar_lokasi, Loc *mobita)
{
  int locx, locy;
  int pilih;
  int l = 1;
  char pos;
  char posisiNow;
  POINT p;
  ListDin posisiCapai;
  CreateListDin(&posisiCapai, 1);
  posisiNow = Name(*mobita);
  printf("posisi yang bisa di capai: \n");
  for (int i = 0; i <= getLastIdx(daftar_lokasi); i++)
  {
    if (daftar_lokasi.buffer[i].locname != posisiNow)
    {
      pos = daftar_lokasi.buffer[i].locname;
      locx = daftar_lokasi.buffer[i].coord.X;
      locy = daftar_lokasi.buffer[i].coord.Y;
      insertLast(&posisiCapai, MakeLoc(pos, locx, locy));

      printf("%d. %c(%d,%d)\n", l, pos, locx, locy);
      l++;
    }
  }

  printf("Posisi yang dipilih yang dipilih: ");
  advWord();
  pilih = getAngka();

  Absis(p) = posisiCapai.buffer[pilih - 1].coord.X;
  Ordinat(p) = posisiCapai.buffer[pilih - 1].coord.Y;
  Coor(*mobita) = p;
  Name(*mobita) = posisiCapai.buffer[pilih - 1].locname;
  printf("Mobita sekarang ada di titik %c (%d,%d)\n", Name(*mobita), Absis(p), Ordinat(p));
}
