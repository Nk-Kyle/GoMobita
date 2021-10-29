#ifndef _MAP_H_
#define _MAP_H_
#include "../boolean.h"
#include "../ADTListDin/listdin.h"
#include "../ADTLokasi/lokasi.h"
#include "../ADTPoint/point.h"
#include "../ADTMatrix/matrix.h"

#define Nil NULL
#define barisMaks 20
#define kolomMaks 30

typedef struct{
    char elemen[barisMaks][kolomMaks];
    int bariseff;
    int kolomeff;
}map;

#define baris(m) (m).bariseff
#define kolom(m) (m).kolomeff
#define ELMTMap(m, i, j) (m).elemen[(i)][(j)]

/* CreateMap */
void CreateMap(int i, int j, map *m);
/*membuat map dengan ukuran baris i, dan ukuran kolom j*/

void makeBorder(map *m, int i, int j);
/* membuat map dengan border * diujung ujungnya */

void makeMap(map *m, int i, int j, ListDin daftar_lokasi);
/*membuat map dengan isi yang sesuai dengan daftar lokasi*/

void printMap(map m, ListDin daftar_lokasi, Matrix adj,Loc mobita);
/*prosedur untuk menampilkan map*/

char convertToChar(int val, ListDin daftar_lokasi);
/*mengubah integer menjadi karakter*/

int convertToInt(char val, ListDin daftar_lokasi);
/*mengubah char menjadi integer*/

void move(Matrix matAjc, ListDin daftar_lokasi,Loc mobita);


#endif
