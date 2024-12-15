#include "../../include/features/optimasirute.h"

double** AlokasiMatrixJarak(int n) {
    double** matriks = (double**) malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        matriks[i] = (double*) malloc(n * sizeof(double));
        for(int j = 0; j < n; j++) {
            matriks[i][j] = INFINITY;
        }
        matriks[i][i] = 0;  
    }
    return matriks;
}

void DealokasiMatrixJarak(double** matriks, int n) {
    for(int i = 0; i < n; i++) {
        free(matriks[i]);
    }
    free(matriks);
}

void DFS(double** jarak, int lokasi, int n, int* dikunjungi) {
    dikunjungi[lokasi] = TRUE;
    for(int i = 0; i < n; i++) {
        if(!dikunjungi[i] && jarak[lokasi][i] != INFINITY) {
            DFS(jarak, i, n, dikunjungi);
        }
    }
}

int isConnected(double** jarak, int n) {
    int* dikunjungi = (int*) calloc(n, sizeof(int));
    DFS(jarak, 0, n, dikunjungi);
    
    for(int i = 0; i < n; i++) {
        if(!dikunjungi[i]) {
            free(dikunjungi);
            return FALSE;
        }
    }
    free(dikunjungi);
    return TRUE;
}

void bestRoute(double** jarak, int n, int depth, int* jalurSekarang, int* visited, double jarakSaatIni, SolusiRute* solusiTerbaik) {
    if(depth == n) {
        if(jarak[jalurSekarang[n-1]][jalurSekarang[0]] != INFINITY) {
            double totalJarak = jarakSaatIni + jarak[jalurSekarang[n-1]][jalurSekarang[0]];
            if(totalJarak < solusiTerbaik->totalJarak) {
                for(int i = 0; i < n; i++) {
                    solusiTerbaik->jalur[i] = jalurSekarang[i];
                }
                solusiTerbaik->totalJarak = totalJarak;
            }
        }
        return;
    }

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            double jarakBaru = jarakSaatIni;
            if(depth > 0) {
                double cost = jarak[jalurSekarang[depth - 1]][i];
                if(cost == INFINITY) {
                    continue;
                }
                jarakBaru += cost;

                if(jarakBaru >= solusiTerbaik->totalJarak) {
                    continue;
                }
            }
            
            visited[i] = TRUE;
            jalurSekarang[depth] = i;
            
            bestRoute(jarak, n, depth + 1, jalurSekarang, visited, jarakBaru, solusiTerbaik);
            visited[i] = FALSE;
        }
    }
}

SolusiRute* optimasiRute(double** jarak, int n) {
    SolusiRute* solusi = (SolusiRute*) malloc(sizeof(SolusiRute));
    solusi->jalur = (int*) malloc(n * sizeof(int));
    solusi->panjangJalur = n;
    solusi->totalJarak = INFINITY;
    
    int* jalurSekarang = (int*) malloc(n * sizeof(int));
    int* visited = (int*) calloc(n, sizeof(int));
    
    bestRoute(jarak, n, 0, jalurSekarang, visited, 0.0, solusi);
    
    free(jalurSekarang);
    free(visited);
    
    return solusi;
}

int cekDeadEnd(double** jarak, int n) {
    for(int i = 0; i < n; i++) {
        int edge_count = 0;
        for(int j = 0; j < n; j++) {
            if(jarak[i][j] != INFINITY) edge_count++;
        }
        if(edge_count < 2) return TRUE;
    }
    return FALSE;
}

int main() {
    int jumlahLokasi, jumlahRute;
    Word lokasi, route;

    printf(">> OPTIMASIRUTE\n");
    
    printf("Masukkan jumlah lokasi pengiriman (node): ");
    STARTWORD(); 
    lokasi = currentWord;

    if (!isKataInt(lokasi)) {
        printf("Input harus berupa angka!\n");
        return 1;
    }

    jumlahLokasi = WordToInt(lokasi);
    if(jumlahLokasi < 2 || jumlahLokasi > MAX_LOKASI) {
        printf("Jumlah lokasi tidak valid!\n");
        return 1;
    }
    
    printf("Masukkan jumlah rute (edge): ");
    STARTWORD();  
    route = currentWord;

    if (!isKataInt(route)) {
        printf("Input harus berupa angka!\n");
        return 1;
    }

    jumlahRute = WordToInt(route);
    
    if(jumlahRute < jumlahLokasi - 1) {
        printf("Jumlah rute terlalu sedikit untuk membentuk graf terhubung!\n");
        return 1;
    }
    
    double** jarak = AlokasiMatrixJarak(jumlahLokasi);
    
    printf("Masukkan jarak antarlokasi (weight):\n");
    printf("format: <asal> <tujuan> <jarak>\n");
    printf("Contoh: 0 1 40 berarti jarak dari lokasi 0 ke 1 adalah 40\n");
    
    for (int i = 0; i < jumlahRute; i++) {
        int asal, tujuan;
        double bobot;

        STARTWORD();
        if (!isKataInt(currentWord)) {
            printf("Input harus berupa angka!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        asal = WordToInt(currentWord);

        ADVWORD();
        if (!isKataInt(currentWord)) {
            printf("Input harus berupa angka!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        tujuan = WordToInt(currentWord);

        ADVWORD();
        if (!isKataInt(currentWord)) {  
            printf("Input harus berupa angka!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        bobot = WordToDouble(currentWord);
        
        if(asal < 0 || asal >= jumlahLokasi || tujuan < 0 || tujuan >= jumlahLokasi) {
            printf("Lokasi tidak valid!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        if(bobot < 0) {
            printf("Bobot tidak boleh negatif!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }

        if (jarak[asal][tujuan] != INFINITY) {
            if (bobot < jarak[asal][tujuan]) {
                jarak[asal][tujuan] = bobot;
                jarak[tujuan][asal] = bobot;
            }
        } 
        else {
            jarak[asal][tujuan] = bobot;
            jarak[tujuan][asal] = bobot;
        }
    }


        if(!isConnected(jarak, jumlahLokasi)) {
            printf("Graf tidak terhubung!\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }

        printf("\nData diterima, silakan tunggu...\n");

        SolusiRute* solusi = optimasiRute(jarak, jumlahLokasi);
        
        if(solusi->totalJarak == INFINITY) {
            printf("\nTidak ditemukan rute valid!\n");
        } 
        
        else {
            printf("A-ha! Rute paling efektif adalah ");
            for (int i = 0; i < jumlahLokasi; i++) {
                printf("%d", solusi->jalur[i]);
                if(i < jumlahLokasi - 1) printf("-");
            }
            printf("-%d.\n", solusi->jalur[0]);
        }
        
        DealokasiMatrixJarak(jarak, jumlahLokasi);
        free(solusi->jalur);
        free(solusi);
        
        return 0;
}

int OptimasiRuteEkspedisi() {
    return main();
}


