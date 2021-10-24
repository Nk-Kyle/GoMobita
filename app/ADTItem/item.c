#include "item.h"
#include <stdio.h>

/* ************ Prototype ************ */
boolean isNormal(QElType I)
/* Mengirim true jika item bertipe normal */
{
    return (Type(I) == 'N');
}
boolean isHeavy(QElType I)
/* Mengirim true jika item bertipe heavy */
{
    return (Type(I) == 'H');
}
boolean isPerishable(QElType I)
/* Mengirim true jika item bertipe perishable */
{
    return (Type(I) == 'P');
}
