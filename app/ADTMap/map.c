#include "map.h"
#include "../ADTColor/pcolor.h"
#include<stdio.h>

void CreateMap(int i, int j, map *m){
    baris(*m) = i;
    kolom(*m) = j;
}

void makeBorder(map *m, int bar, int kol){
    int i, j;
    bar = bar + 2;
    kol = kol + 2;
    CreateMap(bar, kol, m);
    for(i = 0; i <= bar-1; i++){
        for(j = 0 ; j <= kol-1; j++){
            if(i == 0){
                ELMTMap(*m,i,j) = '*';
            }else if(i == bar-1){
                ELMTMap(*m,i,j) = '*';
            }else if(j == 0){
                ELMTMap(*m,i,j) = '*';
            }else if(j == kol-1){
                ELMTMap(*m,i,j) = '*';
            }else{
                ELMTMap(*m,i,j) = ' ';
            }
        }
    }
}

void makeMap(map *m, int bar, int kol, ListDin daftar_lokasi){
    int k;
    int a,b;
    char c;
    makeBorder(m, bar, kol);
    for(k = 0; k <= getLastIdx(daftar_lokasi); k++){
        a = daftar_lokasi.buffer[k].coord.X;
        b = daftar_lokasi.buffer[k].coord.Y;
        c = daftar_lokasi.buffer[k].locname;
        ELMTMap(*m,a,b) = c;
    }
}

void printMap(map m, ListDin daftar_lokasi, Matrix adj, Loc mobita){
    int i,j,k,l,n;
    int locx,locy;
    char lokasiNow;
    ListDin posisiCapai;
    CreateListDin(&posisiCapai,10);
    lokasiNow = mobita.locname;
    k = convertToInt(lokasiNow, daftar_lokasi);
    for(l = 0; l <= getLastIdxCol(adj); l++){
        if(MELM(adj,k,l) == 1){
            char a = convertToChar(l, daftar_lokasi);
            for(k = 0 ; k <= getLastIdx(daftar_lokasi); k++){
                if(daftar_lokasi.buffer[k].locname == a){
                    locx = daftar_lokasi.buffer[k].coord.X;
                    locy = daftar_lokasi.buffer[k].coord.Y;
                    insertLast(&posisiCapai, MakeLoc(a,locx,locy));
                }
            }
        }
    }
    for(i = 0 ; i <= baris(m)-1; i++){
        for(j = 0; j <= kolom(m)-1; j++){
            for(n = 0; n <= getLastIdx(posisiCapai); n++){
                if(j != kolom(m)-1){
                    if (mobita.locname == ELMTMap(m,i,j)){
                        print_yellow(ELMTMap(m,i,j));
                    }else if (ELMTMap(m,i,j) == posisiCapai.buffer[n].locname){
                        print_green(ELMTMap(m,i,j));
                    }else{
                        printf("%c ",ELMTMap(m,i,j));
                    }
                }else {
                    printf("%c",ELMTMap(m,i,j));
                }
            }
        }
        if (i != baris(m)-1){
            printf("\n");
        }
    }
}

char convertToChar(int val, ListDin daftar_lokasi){
    int i;
    char c;
    boolean found;
    found = false;
    i = 0;
    while ((i <= getLastIdx(daftar_lokasi)) && !(found)){
        if (i == val){
            c = daftar_lokasi.buffer[i].locname;
            found = true;
        }
        i++;
    }
    return c;
}

int convertToInt(char val, ListDin daftar_lokasi){
    int hasil;
    int i = 0;
    boolean found = false;
    while( i <= getLastIdx(daftar_lokasi) && !(found)){
        if (daftar_lokasi.buffer[i].locname == val){
            hasil = i;
            found = true;
        }
        i++;
    }
    return hasil;
}

void move(Matrix matAjc, ListDin daftar_lokasi,Loc mobita){
    char lokasiNow;
    int i,j,k,l,m;
    int pilih;
    int locx,locy;
    ListDin posisiCapai;
    CreateListDin(&posisiCapai,1);
    lokasiNow = mobita.locname;
    i = convertToInt(lokasiNow, daftar_lokasi);
    l = 1;
    printf("Posisi yang dapat dicapai :\n");
    for(j = 0; j <= getLastIdxCol(matAjc); j++){
        if(MELM(matAjc,i,j) == 1){
            char a = convertToChar(j, daftar_lokasi);
            for(k = 0 ; k <= getLastIdx(daftar_lokasi); k++){
                if(daftar_lokasi.buffer[k].locname == a){
                    locx = daftar_lokasi.buffer[k].coord.X;
                    locy = daftar_lokasi.buffer[k].coord.Y;
                    insertLast(&posisiCapai, MakeLoc(a,locx,locy));
                }
            }
            printf("%d. %c(%d,%d)\n", l, a, locx,locy);
            l++;
        }
    }
    printf("Posisi yang dipilih yang dipilih: \n");
    printf("\n");
    printf("ENTER COMMAND :");
    scanf("%d\n", &pilih);
    // while ( pilih < 1 && pilih > k){
    //     printf("Masukkan tidak valid. Ulangi\n");
    //     scanf("%d", &pilih);
    // }
    mobita.coord.X = posisiCapai.buffer[pilih-1].coord.X;
    mobita.coord.Y = posisiCapai.buffer[pilih-1].coord.Y;
    mobita.locname = posisiCapai.buffer[pilih-1].locname;
    printf("Mobita sekarang ada di titik %c (%d,%d)\n", mobita.locname, mobita.coord.X, mobita.coord.Y);
}