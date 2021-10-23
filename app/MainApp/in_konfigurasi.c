#include <stdio.h>
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
int getAngka(Word currentWord);
int getAngka(Word currentWord){
  int angka = 0;
  int i;
  for (i = 0; i < currentWord.length; i++){
    angka = angka*10 + currentWord.contents[i];
  }
  return ret;
}
int main () {
  int size_n, size_m;
  int x,y;
  int i;
  int n_lokasi;
  fstartWord("konfigurasi.txt");
  size_n = getAngka(currentWord);
  advWord();
  size_m = getAngka(currentWord);
  advWord();
  x = getAngka(currentWord);
  advWord();
  y = getAngka(currentWord);
  advWord();
  n_lokasi = getAngka(currentWord);
}
