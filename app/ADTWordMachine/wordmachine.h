/* File: wordmachine.h */
/* Definisi Word Engine */

#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include "charmachine.h"
#include <stdlib.h>
#define WORD_CAP 50
#define BLANK ' '

typedef struct {
   char contents[WORD_CAP]; /* container penyimpan kata, indeks yang dipakai [0..CAPACITY-1] */
   int length;
} Word;

/* Word Engine State */
extern boolean endWord;
extern Word currentWord;

void ignoreBlank();
/* Mengabaikan satu atau beberapa BLANK pada input terminal
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void fignoreBlank();
/* Mengabaikan satu atau beberapa BLANK pada file
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void startWord();
/* I.S. : currentChar sembarang (input terminal)
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void fstartWord(char namafile[]);
/* I.S. : currentChar sembarang (file)
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void advWord();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi pada input terminal
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */

void fadvWord();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi pada input terminal pada file
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure copyWord */

void copyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata pada terminal
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
void fcopyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord pada file
   I.S. : currentChar adalah karakter pertama dari kata pada terminal
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */

void print_word();
/* menampilkan isi currentWord.contents pada layar
   I.S. : currentWord terisi oleh Word terakhir yang diakuisisi
   F.S. : currentWord tertampil pada layar */

Word getWord();
/* menghasilkan Word dari currentWord untuk disalin pada Word baru */

Word makeWord(char str []);
/* Menghasilkan word hasil dari pengubahan string str */

boolean isWordSame(Word str1, Word str2);
/* Menghasilkan nilai True jika Word str1 sama dengan Word str2 */

int getAngka();
/* Mendapatkan angka (integer) dari Currentword */

float getFloat();
/* Mendapatkan angka desimal (float) dari currentWord */

Word concat(char con [], Word inW);
/* Menghasilkan Word dengan Isi Word inW diconcat dengan  string con di depannya*/
#endif
