#include "charmachine.c"
#include "wordmachine.c"

int main() {
  fstartWord("words.txt");
  fadvWord();
  fadvWord();
  printf("%f\n", getFloat());
}
