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

void get_word(char *str){
  int i;
  for (i = 0; i < currentWord.length; i++){
    str[i] = currentWord.contents[i];
  }
}

boolean isWordSame(char *str1, char *str2){
  boolean isSame = false;
  int i = 0;
  if (strlen(str1) == strlen(str2)){
    isSame = true;
    while(isSame && i < strlen(str1)){
      printf("%c %c\n", str1[i], str2[i]);
      if (str1[i] != str2[i]) isSame = false;
      else i++;
    }
  }
  return isSame;
}
