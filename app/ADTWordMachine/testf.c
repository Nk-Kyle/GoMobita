#include "charmachine.c"
#include "wordmachine.c"

int main() {
  fstartWord("words.txt");
  while(true){
    print_word();
    fadvWord();
  }
  printf("EOF\n");
}
