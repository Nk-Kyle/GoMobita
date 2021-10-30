#ifndef _MAP_H_
#define _MAP_H_
#include "../boolean.h"
#include "../ADTListDin/listdin.h"
#include "../ADTLokasi/lokasi.h"
#include "../ADTPoint/point.h"
#include "../ADTMatrix/matrix.h"
#include "../ADTLinkedList/list_linked.h"
#include "../ADTStack/stackTas.h"
typedef struct{
    char elemen[22][32];
    int bariseff;
    int kolomeff;
}map;

#define bariseff(m) (m).bariseff
#define kolomeff(m) (m).kolomeff
#define ELMTMap(m, i, j) (m).elemen[(i)][(j)]

/* CreateMap */
void CreateMap(int i, int j, map *m);
/*membuat map dengan ukuran baris i, dan ukuran kolom j*/

void makeBorder(map *m, int i, int j);
/* membuat map dengan border * diujung ujungnya */

void makeMap(map *m, int i, int j, ListDin daftar_lokasi);
/*membuat map dengan isi yang sesuai dengan daftar lokasi*/

void printMap(map m, ListDin daftar_lokasi, Matrix mat_adj, Loc mobita, LinkedList ToDo, StackTas Tas );
/*prosedur untuk menampilkan map*/

char convertToChar(int val, ListDin daftar_lokasi);
/*mengubah integer menjadi karakter*/

int convertToInt(char val, ListDin daftar_lokasi);
/*mengubah char menjadi integer*/

void move(Matrix matAjc, ListDin daftar_lokasi,Loc mobita);


#endif
