#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void CreateMatrix(int nRow, int nCol, Matrix *m){
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
  ROWS(*m) = nRow;
  COLS(*m) = nCol;
}

/* *** Selektor "DUNIA Matrix" *** */
boolean isMIdxValid(int i, int j){
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
  return(i>= 0 && i <ROW_CAP && j >= 0 && j < COL_CAP);
}
/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
Index getLastIdxRow(Matrix m){
/* Mengirimkan Index baris terbesar m */
  return (ROWS(m)-1);
}
Index getLastIdxCol(Matrix m){
/* Mengirimkan Index kolom terbesar m */
  return (COLS(m)-1);
}
boolean isMIdxEff(Matrix m, Index i, Index j){
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
  return(i>=0 && i<= getLastIdxRow(m) && j >=0 && j <= getLastIdxCol(m));
}
int getElmtDiagonal(Matrix m, Index i){
/* Mengirimkan elemen m(i,i) */
  return(MELM(m,i,i));
}
/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mRes){
/* Melakukan assignment MRes = MIn */
  int i,j;
  CreateMatrix(ROWS(mIn),COLS(mIn), mRes);
  for(i = 0 ; i < ROWS(mIn); i++){
    for(j = 0 ; j < COLS(mIn); j++){
      MELM(*mRes,i,j) = MELM(mIn, i, j);
    }
  }
}
/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol){
/* I.S. isMIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
  int i,j;
  CreateMatrix(nRow, nCol, m);
  for(i = 0; i < nRow; i++){
    for(j = 0; j < nCol; j++){
      scanf("%d", &MELM(*m,i,j));
    }
  }
}
void displayMatrix(Matrix m){
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
  int i,j;
  for(i = 0 ; i< ROWS(m); i++){
    for(j=0; j < COLS(m); j++){
      if(j != COLS(m)-1) printf("%d ",MELM(m,i,j));
      else printf("%d",MELM(m,i,j));
    }
    if (i != ROWS(m)-1) printf("\n");
  }
}
/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2){
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
  int i,j;
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m1), &m3);
  for(i = 0; i < ROWS(m1); i++){
    for(j=0; j < COLS(m1); j++){
      MELM(m3,i,j) = MELM(m1,i,j) + MELM(m2,i,j);
    }
  }
  return m3;
}
Matrix subtractMatrix(Matrix m1, Matrix m2){
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
  int i,j;
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m1), &m3);
  for(i = 0; i < ROWS(m1); i++){
    for(j=0; j < COLS(m1); j++){
      MELM(m3,i,j) = MELM(m1,i,j) - MELM(m2,i,j);
    }
  }
  return m3;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2){
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
  int i, j,k,sum;
  Matrix m3;
  CreateMatrix(ROWS(m1), COLS(m2), &m3);
  for(i = 0; i < ROWS(m3); i++){
    for(j = 0; j <COLS(m3); j++){
      sum = 0;
      for(k = 0; k < COLS(m1); k++){
        sum += MELM(m1,i,k) * MELM(m2,k,j);
      }
      MELM(m3,i,j) = sum;
    }
  }
  return m3;

}
Matrix multiplyConst(Matrix m, int x){
/* Mengirim hasil perkalian setiap elemen m dengan x */
  Matrix mres;
  int i,j;
  CreateMatrix(ROWS(m), COLS(m), &mres);
  for(i = 0; i < ROWS(m); i++){
    for(j=0; j < COLS(m); j++){
      MELM(mres,i,j) = MELM(m,i,j) * x;
    }
  }
  return mres;
}
void pMultiplyConst(Matrix *m, int k){
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
  int i,j;
  for(i = 0; i < ROWS(*m); i++){
    for(j = 0; j < COLS(*m); j++){
      MELM(*m,i,j) *= k;
    }
  }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isEqual(Matrix m1, Matrix m2){
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
  boolean eq = true;
  int i = 0;
  int j = 0;
  if (count(m1) != count(m2) || getLastIdxCol(m1) != getLastIdxCol(m2) ) eq = false;
  while(eq == true && i < ROWS(m1)){
    j = 0;
    while(eq == true && j < COLS(m1)){
      if(MELM(m1,i,j) != MELM(m2,i,j)) eq = false;
      else j++;
    }
    i++;
  }
  return eq;
}
boolean isNotEqual(Matrix m1, Matrix m2){
/* Mengirimkan true jika m1 tidak sama dengan m2 */
  return (!isEqual(m1,m2));
}
boolean isSizeEqual(Matrix m1, Matrix m2){
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
  return(ROWS(m1) == ROWS(m2) && COLS(m1) == COLS(m2));
}
/* ********** Operasi lain ********** */
int count(Matrix m){
/* Mengirimkan banyaknya elemen m */
  return (ROWS(m) * COLS(m));
}
/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m){
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
  return (ROWS(m) == COLS(m));
}
boolean isSymmetric(Matrix m){
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m)
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
   boolean sym;
   sym = isSquare(m);
   int i,j;
   i = 0;
   while (sym == true && i < ROWS(m)){
     j = 0;
     while(sym == true && j < COLS(m)){
       if(MELM(m,i,j) != MELM(m,j,i)) sym = false;
       else j++;
     }
     i++;
   }
   return sym;
}
boolean isIdentity(Matrix m){
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
   boolean iden;
   int i =0;
   int j;
   iden = isSquare(m);
   while (iden == true && i < ROWS(m)){
     j = 0;
     while(iden == true && j < COLS(m)){
       if(i==j && MELM(m,i,j) != 1) iden = false;
       else if (i!=j && MELM(m,i,j) != 0) iden = false;
       else j++;
     }
     i++;
   }
   return iden;
 }
boolean isSparse(Matrix m){
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
   int cnt = 0;
   float koma;
   int i,j;
   for(i = 0; i < ROWS(m); i++) {
     for(j=0; j < COLS(m); j++){
       if (MELM(m,i,j) != 0) cnt++;
     }
   }
   return((float)cnt/count(m) <= 0.05);
}
Matrix inverse1(Matrix m){
/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
  return multiplyConst(m,-1);
}
void pInverse1(Matrix *m){
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
  pMultiplyConst(m,-1);
}
float determinant(Matrix m){
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
  int i,j,k;
  if (count(m) == 1) return MELM(m,0,0);
  else{
    double sum = 0;
    Matrix mtemp;
    int col;
    CreateMatrix(ROWS(m)-1, COLS(m)-1,&mtemp);
    for(i = 0; i< COLS(m); i++){
      // Buat matriks n-1 x n-1 per col dalam row 1
      for(j=1; j < ROWS(m); j++) {
        col = 0;
        for(k=0; k < COLS(m); k++){
          if(k!=i) {
            MELM(mtemp,j-1,col) = MELM(m,j,k);
            col++;
          }
        }
      }
      sum += MELM(m,0,i) * determinant(mtemp) * pow(-1,i);
    }
    return sum;
  }
}
void transpose(Matrix *m){
/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
  Matrix temp;
  int i,j;
  CreateMatrix(COLS(*m), ROWS(*m), &temp);
  for (i = 0; i < ROWS(*m) ; i++){
    for(j=0 ; j < COLS(*m); j++){
      MELM(temp,j,i) = MELM(*m,i,j);
    }
  }
  copyMatrix(temp,m);
}

float rowMean (Matrix m, Index i){
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
  int j;
  float sum = 0;
  for (j = 0 ; j < COLS(m) ; j++){
    sum += MELM(m,i,j);
  }
  return(sum/COLS(m));
}
float colMean (Matrix m, Index j){
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
  int i;
  float sum = 0;
  for (i = 0; i < ROWS(m) ; i++){
    sum += MELM(m,i,j);
  }
  return(sum/ROWS(m));
}
void rowExtremes (Matrix m, Index i, int * max, int * min){
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
  int j;
  *max = MELM(m,i,0);
  *min = MELM(m,i,0);
  if(COLS(m) > 1){
    for(j = 1; j < COLS(m); j++){
      if(MELM(m,i,j) > *max) *max = MELM(m,i,j);
      if(MELM(m,i,j) < *min) *min =MELM(m,i,j);
    }
  }
}
void colExtremes (Matrix m, Index j, int * max, int * min){
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
  int i;
  *max = MELM(m,0,j);
  *min = MELM(m,0,j);
  if(ROWS(m) > 1){
    for (i = 1; i < ROWS(m); i++){
      if(MELM(m,i,j) > *max) *max = MELM(m,i,j);
      if(MELM(m,i,j) < *min) *min = MELM(m,i,j);
    }
  }
}
int countValOnRow (Matrix m, Index i, int val){
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
  int j;
  int cnt = 0;
  for(j = 0; j < COLS(m); j++){
    if(MELM(m,i,j) == val) cnt++;
  }
  return cnt;
}
int countValOnCol (Matrix m, Index j, int val){
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
  int i;
  int cnt = 0;
  for(i = 0; i < ROWS(m); i++){
    if(MELM(m,i,j) == val) cnt++;
  }
  return cnt;
}
