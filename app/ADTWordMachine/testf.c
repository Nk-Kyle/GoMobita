#include "charmachine.c"
#include "wordmachine.c"

int main() {
  Word a,b;
  b= makeWord("test");
  a = concat("123",b);
  printf("%s\n", b.contents);
  printf("%d\n", b.length);
  printf("%s\n", a.contents);
}
