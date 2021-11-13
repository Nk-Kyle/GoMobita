#include "charmachine.c"
#include "wordmachine.c"
int main () {
  Word namafile;
  Word katamove;
  int sum;
  float afloat;
  printf("Test Input Terminal 1\n");
  printf("Kata 1: ");
  startWord();
  print_word();
  printf("Kata 2: ");
  advWord();
  print_word();
  printf("Test Input File\nMasukkan nama file (ex: words.txt) : ");
  advWord();
  namafile = getWord();
  fstartWord(namafile.contents);
  sum = 0;
  sum += getAngka();
  fadvWord();
  sum += getAngka();
  fadvWord();
  afloat = getFloat();
  fclose(ftape);
  //Sudah keluar dari File
  printf("Jumlah angka: %d\n", sum);
  printf("nilai float: %f\n", afloat);
  printf("Test Input Terminal 2\nInput kata MOVE\n");
  advWord();
  katamove = makeWord("MOVE");
  printf("%d\n",isWordSame(katamove, currentWord));
  printf("SELESAI");
  fclose(tape);
  return 0;
}
