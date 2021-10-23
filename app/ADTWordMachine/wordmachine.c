/*
Nama : Ng Kyle
NIM               : 13520040
Nama              : Ng Kyle
Tanggal           : 26 September 2021
Topik praktikum   : Mesin Kata
*/
#include "wordmachine.h"
boolean endWord;
Word currentWord;
void ignoreBlank(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */
   while ((currentChar == BLANK || currentChar == '\n') && currentChar != MARK){
     adv();
   }
}

void startWord(){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
  start();
  ignoreBlank();
  if (currentChar == MARK) endWord = true;
  else {
    endWord = false;
    copyWord();
  }
}

void fstartWord(char namafile[]){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
  fstart(namafile);
  ignoreBlank();
  if (currentChar == MARK) endWord = true;
  else {
    endWord = false;
    copyWord();
  }
}

void advWord(){
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */
   ignoreBlank();
   if (currentChar == MARK) endWord = true;
   else {
     copyWord();
   }
}
void copyWord(){
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
  int i = 0;
  while (currentChar != MARK && currentChar != BLANK && i < CAPACITY && currentChar != '\n'){
    currentWord.contents[i] = currentChar;
    adv();
    i++;
  }
  currentWord.length = i;
}
