/* File: charmachine.h */
/* Definisi Character Engine */

#ifndef CHAR_ENGINE_H
#define CHAR_ENGINE_H

#include "../boolean.h"

/* Char Engine State */
extern char currentChar;
extern boolean eot;

void start();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */
void fstart(char namafile[]);
/* Mesin siap dioperasikan. Pita File disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : namafile terdefinisi (terdapat pada folder)
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void adv();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
*/

void fadv();
/* Pita File dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
*/

void closetape();
#endif
