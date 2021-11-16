#include "stackTas.c"
#include "../ADTItem/item.c"
#include <stdio.h>

int main(){
    StackTas tas;
    Pesanan p;
    CreateTas(&tas);
    for (int i = 0; i < 5; i++){
      Time(p) = i;
      Exp(p) = i;
      PickupTime(p) = i;
      Pickup(p) = 'a';
      Dropoff(p) ='b';
      IType(p) ='c';
      pushTas(&tas,p);
    }
    dispTas(tas);
    return 0;
}
