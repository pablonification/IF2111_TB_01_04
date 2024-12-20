#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../ADT/boolean.h"
#include "../ADT/mesinkata.h"

#define MAX_LOKASI 100
#define infinity 999999

// Struktur untuk menyimpan solusi rute
typedef struct {
    int *jalur;          
    int panjangJalur;    
    double totalJarak;   
} SolusiRute;

// Konstruktor matriks jarak
double** AlokasiMatrixJarak(int n);

// Destruktor matriks jarak
void DealokasiMatrixJarak(double** matriks, int n);

// Fungsi rekursif untuk mencari rute terbaik
void DFS(double** jarak, int lokasi, int n, int* dikunjungi);

// Fungsi untuk mengecek apakah graf terhubung
int isConnected(double** jarak, int n);

// Fungsi untuk menghitung kombinasi
int combination(int n, int r);

// Fungsi rekursif untuk mencari rute terbaik
SolusiRute* optimasiRute(double** jarak, int n);

// Fungsi rekursif untuk mencari rute terbaik
void bestRoute(double** jarak, int n, int depth, int* jalurSekarang, int* visited, double jarakSaatIni, SolusiRute* solusiTerbaik);

// Fungsi utama untuk optimasi rute
int OptimasiRute();