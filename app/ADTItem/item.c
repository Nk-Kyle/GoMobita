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
