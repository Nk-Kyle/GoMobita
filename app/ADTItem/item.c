#include "item.h"
#include <stdio.h>

/* ************ Prototype ************ */
boolean isNormal(Pesanan I)
/* Mengirim true jika item bertipe normal */
{
    return (IType(I) == 'N');
}
boolean isHeavy(Pesanan I)
/* Mengirim true jika item bertipe heavy */
{
    return (IType(I) == 'H');
}
boolean isPerishable(Pesanan I)
/* Mengirim true jika item bertipe perishable */
{
    return (IType(I) == 'P');
}

boolean isPesananSama(Pesanan i1, Pesanan i2)
{
    return (Time(i1) == Time(i2) && Exp(i1) == Exp(i2) && Pickup(i1) == Pickup(i2) && Dropoff(i1) == Dropoff(i2) && IType(i1) == IType(i2));
};
