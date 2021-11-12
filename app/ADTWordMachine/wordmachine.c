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
   F.S. : currentChar ≠ BLANK */
   while (currentChar == BLANK || currentChar == '\n'){
     adv();
   }
}

void fignoreBlank(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK*/
   while (currentChar == BLANK || currentChar == '\n'){
     fadv();
   }
}

void startWord(){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
  start();
  ignoreBlank();
  endWord = false;
  copyWord();
}

void fstartWord(char namafile[]){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
  fstart(namafile);
  fignoreBlank();
  endWord = false;
  fcopyWord();
}

void advWord(){
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya
   Proses : Akuisisi kata menggunakan procedure copyWord */
   ignoreBlank();
   copyWord();
}
void copyWord(){
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
  int i = 0;
  while (currentChar != BLANK && i < WORD_CAP && currentChar != '\n'){
    currentWord.contents[i] = currentChar;
    adv();
    i++;
  }
  currentWord.length = i;
}

void fadvWord(){
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */
   fignoreBlank();
   fcopyWord();
}

void fcopyWord(){
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
  int i = 0;
  while (currentChar != BLANK && i < WORD_CAP && currentChar != '\n'){
    currentWord.contents[i] = currentChar;
    fadv();
    i++;
  }
  currentWord.length = i;
}

void print_word(){
  int i;
  for (i = 0; i < currentWord.length; i++){
    printf("%c", currentWord.contents[i]);
  }
  printf("\n");
}

Word getWord(){
  int i;
  Word outW;
  outW.length = currentWord.length;
  for(i = 0; i < outW.length; i++){
    outW.contents[i] = currentWord.contents[i];
  }
  outW.contents[i] ='\0';
  return outW;
}

Word makeWord(char str []){
  Word outW;
  int i = 0;
  outW.length = 0;
  while (str[i] != '\0') {
    outW.length++;
    outW.contents[i] = str[i];
    i++;
  }
  outW.contents[i+1] = '\0';
  return outW;
}

boolean isWordSame(Word str1, Word str2){
  boolean isSame = false;
  int i = 0;
  if (str1.length == str2.length){
    isSame = true;
    while(isSame && i < str1.length){
      if (str1.contents[i] != str2.contents[i]) isSame = false;
      else i++;
    }
  }
  return isSame;
}

int getAngka(){
  int angka = 0;
  int i;
  if (currentWord.contents[0] == '-') {
    for (i = 1; i < currentWord.length; i++){
      angka = angka*10 + (currentWord.contents[i]- '0');
    }
    angka = angka*(-1);
  }
  else {
    for (i = 0; i < currentWord.length; i++){
      angka = angka*10 + (currentWord.contents[i]- '0');
    }
  }
  return angka;
}

float getFloat(){
  float angka = 0;
  int i = 0;
  float j = 1;
  while (i < currentWord.length && currentWord.contents[i] != '.'){
    angka = angka * 10 + (currentWord.contents[i]- '0');
    i++;
  }
  i++;
  while(i < currentWord.length){
    j = j * 10;
    angka = angka + ((currentWord.contents[i]- '0')/j);
    i++;
  }
  return angka;
}
