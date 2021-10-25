#include "charmachine.c"
#include "wordmachine.c"
int main () {
  char fname [100];
  printf("input nama file: ");
  startWord();
  printf("nama file: ");
  get_word(fname);
  print_word();
  fstartWord(fname);
  print_word();
  fadvWord();
  print_word();
  fclose(ftape);
  advWord();
  print_word();
  return 0;
}
