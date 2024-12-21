#include "../../include/features/optimasirute.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

double** AlokasiMatrixJarak(int n) {
    double** matriks = (double**) malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        matriks[i] = (double*) malloc(n * sizeof(double));
        for(int j = 0; j < n; j++) {
            matriks[i][j] = infinity;
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
        if(!dikunjungi[i] && jarak[lokasi][i] != infinity) {
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

int combination(int n, int r) {
    if(r == 0 || r == n) {
        return 1;
    }
    return combination(n - 1, r - 1) + combination(n - 1, r);
}

void bestRoute(double** jarak, int n, int depth, int* jalurSekarang, int* visited, double jarakSaatIni, SolusiRute* solusiTerbaik) {
    if(depth == n) {
        if (jarakSaatIni < solusiTerbaik->totalJarak) {
            for(int i = 0; i < n; i++) {
                solusiTerbaik->jalur[i] = jalurSekarang[i];
            }
            solusiTerbaik->totalJarak = jarakSaatIni;
        }
        return;
    }
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            double jarakBaru = jarakSaatIni;

            if(depth > 0) {
                double cost = jarak[jalurSekarang[depth - 1]][i];
                if(cost == infinity) {
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
    solusi->totalJarak = infinity;
    
    int* jalurSekarang = (int*) malloc(n * sizeof(int));
    int* visited = (int*) calloc(n, sizeof(int));
    
    visited[0] = TRUE;
    jalurSekarang[0] = 0;

    bestRoute(jarak, n, 1, jalurSekarang, visited, 0.0, solusi);
    
    free(jalurSekarang);
    free(visited);
    
    return solusi;
}

int cekDeadEnd(double** jarak, int n) {
    for(int i = 0; i < n; i++) {
        int edge_count = 0;
        for(int j = 0; j < n; j++) {
            if(jarak[i][j] != infinity) edge_count++;
        }
        if(edge_count < 2 && i != n-1) return TRUE;  
    }
    return FALSE;
}

int OptimasiRute() {
    int jumlahLokasi, jumlahRute;
    Word lokasi, route;

    printf(">> " BLUE "OPTIMASIRUTE" WHITE "\n");
    
    printf("Masukkan jumlah lokasi pengiriman (node): ");
    STARTWORD(); 
    lokasi = currentWord;

    if (!isKataInt(lokasi)) {
        printf(RED "Input harus berupa angka!" WHITE "\n");
        return 1;
    }

    jumlahLokasi = WordToInt(lokasi);
    if(jumlahLokasi < 2 || jumlahLokasi > MAX_LOKASI) {
        printf(RED "Jumlah lokasi tidak valid!" WHITE "\n");
        return 1;
    }
    
    printf("Masukkan jumlah rute (edge): ");
    STARTWORD();  
    route = currentWord;

    if (!isKataInt(route)) {
        printf(RED "Input harus berupa angka!" WHITE "\n");
        return 1;
    }

    jumlahRute = WordToInt(route);

    int maxEdge = (jumlahLokasi * (jumlahLokasi - 1)) / 2;
    if (jumlahRute > maxEdge) {
        printf(RED "Jumlah rute terlalu banyak, maksimal %d!" WHITE "\n", maxEdge);
        return 1;
    }
    
    if(jumlahRute < jumlahLokasi - 1) {
        printf(RED "Jumlah rute terlalu sedikit untuk membentuk graf terhubung!" WHITE "\n");
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
            printf(RED "Input harus berupa angka!" WHITE "\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        asal = WordToInt(currentWord);

        ADVWORD();
        if (!isKataInt(currentWord)) {
            printf(RED "Input harus berupa angka!" WHITE "\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        tujuan = WordToInt(currentWord);

        ADVWORD();
        if (!isKataInt(currentWord) && !isWordNegative(currentWord)) {
            printf(RED "Input harus berupa angka!" WHITE "\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        bobot = WordToDouble(currentWord);
        
        if(asal < 0 || asal >= jumlahLokasi || tujuan < 0 || tujuan >= jumlahLokasi) {
            printf(RED "Lokasi tidak valid!" WHITE "\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }
        if(bobot < 0) {
            printf(RED "Bobot tidak boleh negatif!" WHITE "\n");
            DealokasiMatrixJarak(jarak, jumlahLokasi);
            return 1;
        }

        if (jarak[asal][tujuan] != infinity) {
            if (bobot < jarak[asal][tujuan]) {
                jarak[asal][tujuan] = bobot;
                jarak[tujuan][asal] = bobot;
            }
        } else {
            jarak[asal][tujuan] = bobot;
            jarak[tujuan][asal] = bobot;
        }
    }

    if(!isConnected(jarak, jumlahLokasi)) {
        printf(RED "Graf tidak terhubung!" WHITE "\n");
        DealokasiMatrixJarak(jarak, jumlahLokasi);
        return 1;
    }

    // if(cekDeadEnd(jarak, jumlahLokasi)) {
    //     printf(RED "Graf mengandung dead-end, rute valid tidak ditemukan!" WHITE "\n");
    //     DealokasiMatrixJarak(jarak, jumlahLokasi);
    //     return 1;
    // }

    printf("\n" YELLOW "Data diterima, silakan tunggu..." WHITE "\n");

    SolusiRute* solusi = optimasiRute(jarak, jumlahLokasi);

    if(solusi->totalJarak == infinity) {
        printf("\n" RED "Tidak ditemukan rute valid!" WHITE "\n");
    } else {
        printf(GREEN "A-ha! Rute paling efektif adalah ");
        for (int i = 0; i < jumlahLokasi; i++) {
            printf("%d", solusi->jalur[i]);
            if(i < jumlahLokasi - 1) printf("-");
        }
        printf(" dengan total jarak %.2f.\n" WHITE, solusi->totalJarak);
    }
        
    DealokasiMatrixJarak(jarak, jumlahLokasi);
    free(solusi->jalur);
    free(solusi);
        
    return 0;
}



// int TestOptimasiRute() {
//    printf("\n=== RUNNING OPTIMASI RUTE TEST CASES ===\n\n");
   
//    // Test Case 1: Basic Valid Route
//    printf("TC1: Basic Valid Route\n");
//    printf("Input:\n");
//    printf("3 2\n");
//    printf("0 1 10\n");
//    printf("1 2 20\n");
//    printf("Expected: Valid route 0-1-2 with total 30\n");
//    printf("Result: ");
//    OptimasiRute();
   
//    // Test Case 2: Graf Tidak Terhubung
//    printf("\nTC2: Graf Tidak Terhubung\n");
//    printf("Input:\n");
//    printf("4 3\n");
//    printf("0 1 10\n");
//    printf("1 2 15\n");
//    printf("2 0 20\n");
//    printf("Expected: Graf tidak terhubung!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 3: Bobot Nol Valid
//    printf("\nTC3: Bobot Nol Valid\n");
//    printf("Input:\n");
//    printf("3 3\n"); 
//    printf("0 1 0\n");
//    printf("1 2 0\n");
//    printf("2 0 0\n");
//    printf("Expected: Valid route with total 0\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 4: Maximum Edges
//    printf("\nTC4: Maximum Edges\n");
//    printf("Input:\n");
//    printf("4 6\n");
//    printf("0 1 10\n");
//    printf("1 2 20\n");
//    printf("2 3 30\n");
//    printf("3 0 40\n");
//    printf("0 2 50\n");
//    printf("1 3 60\n");
//    printf("Expected: Valid route with optimal path\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 5: Invalid Location
//    printf("\nTC5: Invalid Location\n");
//    printf("Input:\n");
//    printf("3 2\n");
//    printf("0 3 10\n");
//    printf("1 2 20\n");
//    printf("Expected: Lokasi tidak valid!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 6: Negative Weight
//    printf("\nTC6: Negative Weight\n");
//    printf("Input:\n");
//    printf("3 2\n");
//    printf("0 1 -10\n");
//    printf("1 2 20\n");
//    printf("Expected: Bobot tidak boleh negatif!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 7: Too Few Edges
//    printf("\nTC7: Too Few Edges\n");
//    printf("Input:\n");
//    printf("4 2\n");
//    printf("Expected: Jumlah rute terlalu sedikit!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 8: Invalid Node Count
//    printf("\nTC8: Invalid Node Count\n");
//    printf("Input:\n");
//    printf("1\n");
//    printf("Expected: Jumlah lokasi tidak valid!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 9: Non-Numeric Input
//    printf("\nTC9: Non-Numeric Input\n");
//    printf("Input:\n");
//    printf("abc\n");
//    printf("Expected: Input harus berupa angka!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 10: Too Many Edges
//    printf("\nTC10: Too Many Edges\n");
//    printf("Input:\n");
//    printf("3 4\n");
//    printf("Expected: Jumlah rute terlalu banyak!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 11: Dead End Path
//    printf("\nTC11: Dead End Path\n");
//    printf("Input:\n");
//    printf("4 3\n");
//    printf("0 1 10\n");
//    printf("1 2 15\n");
//    printf("2 3 20\n");
//    printf("Expected: Tidak ditemukan rute valid!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 12: Equal Weight Routes
//    printf("\nTC12: Equal Weight Routes\n");
//    printf("Input:\n");
//    printf("4 6\n");
//    printf("0 1 10\n");
//    printf("1 2 10\n");
//    printf("2 3 10\n");
//    printf("3 0 10\n");
//    printf("0 2 10\n");
//    printf("1 3 10\n");
//    printf("Expected: Valid route with total 30\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 13: Maximum Node Count
//    printf("\nTC13: Maximum Node Count\n");
//    printf("Input:\n");
//    printf("51\n");
//    printf("Expected: Jumlah lokasi tidak valid!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 14: Single Edge Graph
//    printf("\nTC14: Single Edge Graph\n");
//    printf("Input:\n");
//    printf("2 1\n");
//    printf("0 1 10\n");
//    printf("Expected: Valid route\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 15: Large Weights
//    printf("\nTC15: Large Weights\n");
//    printf("Input:\n");
//    printf("3 3\n");
//    printf("0 1 2139095040\n");
//    printf("1 2 2139095040\n");
//    printf("2 0 2139095040\n");
//    printf("Expected: Valid route with large total\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 16: Zero Distance Round Trip
//    printf("\nTC16: Zero Distance Round Trip\n");
//    printf("Input:\n");
//    printf("3 3\n");
//    printf("0 1 0\n");
//    printf("1 2 0\n");
//    printf("2 0 0\n");
//    printf("Expected: Valid route with total 0\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 17: Duplicate Routes with Different Weights
//    printf("\nTC17: Duplicate Routes\n");
//    printf("Input:\n");
//    printf("3 3\n");
//    printf("0 1 10\n");
//    printf("0 1 5\n");
//    printf("1 2 20\n");
//    printf("Expected: Uses minimum weight for duplicate routes\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 18: Self Loop
//    printf("\nTC18: Self Loop\n");
//    printf("Input:\n");
//    printf("3 3\n");
//    printf("0 0 10\n");
//    printf("1 1 10\n");
//    printf("2 2 10\n");
//    printf("Expected: Graf tidak terhubung!\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 19: Linear Path
//    printf("\nTC19: Linear Path\n");
//    printf("Input:\n");
//    printf("4 3\n");
//    printf("0 1 10\n");
//    printf("1 2 20\n");
//    printf("2 3 30\n");
//    printf("Expected: Valid route 0-1-2-3\n");
//    printf("Result: ");
//    OptimasiRute();

//    // Test Case 20: Mixed Edge Types
//    printf("\nTC20: Mixed Edge Types\n");
//    printf("Input:\n");
//    printf("4 5\n");
//    printf("0 1 10\n");
//    printf("1 2 0\n");
//    printf("2 3 30\n");
//    printf("3 0 40\n");
//    printf("1 3 20\n");
//    printf("Expected: Valid route with optimal path\n");
//    printf("Result: ");
//    OptimasiRute();

//    printf("\n=== TEST CASES COMPLETED ===\n");
//    return 0;
// }

// int main() {
//     return OptimasiRute();
// }