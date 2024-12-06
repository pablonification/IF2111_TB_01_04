#include <stdio.h>
#include "../../include/features/bonus2.h"

void DNAtoRNA(Word DNA, Word *RNA) {
    int idx = 0;
    while (idx < DNA.Length) {
        if (DNA.TabWord[idx] == 'T') {
            RNA->TabWord[idx] = 'A';
        } else if (DNA.TabWord[idx] == 'A') {
            RNA->TabWord[idx] = 'U';
        } else if (DNA.TabWord[idx] == 'G') {
            RNA->TabWord[idx] = 'C';
        } else if (DNA.TabWord[idx] == 'C') {
            RNA->TabWord[idx] = 'G';
        }
        idx++;
    }
    RNA->Length = DNA.Length;
    RNA->TabWord[RNA->Length] = '\0';
    printf("RNA: %s\n", RNA->TabWord);
    printf("Index: %d\n", idx);
}

char translateCodon(char *codon) {
    if (codon[0] == 'U') {
        if (codon[1] == 'U') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'F';
            else if (codon[2] == 'A' || codon[2] == 'G') return 'L';
        } else if (codon[1] == 'C') {
            return 'S';
        } else if (codon[1] == 'A') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'Y';
            else if (codon[2] == 'A' || codon[2] == 'G') return '*'; // Stop codon
        } else if (codon[1] == 'G') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'C';
            else if (codon[2] == 'A') return '*'; // Stop codon
            else if (codon[2] == 'G') return 'W';
        }
    } else if (codon[0] == 'C') {
        if (codon[1] == 'U') return 'L';
        if (codon[1] == 'C') return 'P';
        if (codon[1] == 'A') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'H';
            else if (codon[2] == 'A' || codon[2] == 'G') return 'Q';
        } else if (codon[1] == 'G') return 'R';
    } else if (codon[0] == 'A') {
        if (codon[1] == 'U') {
            if (codon[2] == 'U' || codon[2] == 'C' || codon[2] == 'A') return 'I';
            else if (codon[2] == 'G') return 'M';
        } else if (codon[1] == 'C') return 'T';
        else if (codon[1] == 'A') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'N';
            else if (codon[2] == 'A' || codon[2] == 'G') return 'K';
        } else if (codon[1] == 'G') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'S';
            else if (codon[2] == 'A' || codon[2] == 'G') return 'R';
        }
    } else if (codon[0] == 'G') {
        if (codon[1] == 'U') return 'V';
        if (codon[1] == 'C') return 'A';
        if (codon[1] == 'A') {
            if (codon[2] == 'U' || codon[2] == 'C') return 'D';
            else if (codon[2] == 'A' || codon[2] == 'G') return 'E';
        } else if (codon[1] == 'G') return 'G';
    }
    return '?'; // invalid codon
}

void processDNA(){
    Word DNA;
    Word RNA, weapon;
    char protein[1000];
    int validProtein = 0;
    int idx = 0, proteinIdx = 0;
    
    while(!validProtein){
        printf("Senjata yang ingin dimasukkan: ");
        STARTLINE();
        weapon = currentWord;
        printf("DNA: ");
        scanWord(&DNA);

        // DNA KE RNA
        DNAtoRNA(DNA, &RNA);

        // RNA KE PROTEIN
        
        while (idx < RNA.Length) {
            char codon[4] = {RNA.TabWord[idx], RNA.TabWord[idx + 1], RNA.TabWord[idx + 2], '\0'};
            protein[proteinIdx++] = translateCodon(codon);
            idx += 3;
        }
        protein[proteinIdx] = '\0';
        printf("Protein >>>> %s\n", protein);

        // check ada ? gk
        validProtein = 1;
        for(int i = 0; i < proteinIdx; i++){
            if(protein[i] == '?'){
                validProtein = 0;
                printf("Protein mengandung codon yang invalid. Tolong masukkan DNA yang valid!\n");
                break;
            }
        }
    }



    Word secretCode;
    printf("Masukkan kode rahasia: ");
    scanWord(&secretCode);

    int idxSC = secretCode.Length;
    printf("%d <<<<<<<< index secret code\n", idxSC);

    // Check if secretCode is in protein
    int found = 0;
    for (int i = 0; i <= proteinIdx - idxSC; i++) {
        int j = 0;
        while (j < secretCode.Length && protein[i + j] == secretCode.TabWord[j]) {
            j++;
        }
        if (j == secretCode.Length) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Senjata biologis mengandung kode, barang akan ditambahkan ke dalam queue!\n");
    } else {
        printf("Kode rahasia tidak ditemukan, maka senjata biologis sudah disabotase, barang ditolak!\n");
    }
}

/*int main() {
    Word DNA;
    Word RNA;
    char protein[1000];
    int validProtein = 0;
    int idx = 0, proteinIdx = 0;
    
    while(!validProtein){
        printf("DNA: ");
        scanWord(&DNA);

        // DNA KE RNA
        DNAtoRNA(DNA, &RNA);

        // RNA KE PROTEIN
        
        while (idx < RNA.Length) {
            char codon[4] = {RNA.TabWord[idx], RNA.TabWord[idx + 1], RNA.TabWord[idx + 2], '\0'};
            protein[proteinIdx++] = translateCodon(codon);
            idx += 3;
        }
        protein[proteinIdx] = '\0';
        printf("Protein >>>> %s\n", protein);

        // check ada ? gk
        validProtein = 1;
        for(int i = 0; i < proteinIdx; i++){
            if(protein[i] == '?'){
                validProtein = 0;
                printf("Protein mengandung codon yang invalid. Tolong masukkan DNA yang valid!\n");
                break;
            }
        }
    }



    Word secretCode;
    printf("Masukkan kode rahasia: ");
    scanWord(&secretCode);

    int idxSC = secretCode.Length;
    printf("%d <<<<<<<< index secret code\n", idxSC);

    // Check if secretCode is in protein
    int found = 0;
    for (int i = 0; i <= proteinIdx - idxSC; i++) {
        int j = 0;
        while (j < secretCode.Length && protein[i + j] == secretCode.TabWord[j]) {
            j++;
        }
        if (j == secretCode.Length) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Senjata biologis mengandung kode, barang akan ditambahkan ke dalam queue!\n");
    } else {
        printf("Kode rahasia tidak ditemukan, maka senjata biologis sudah disabotase, barang ditolak!\n");
    }

    return 0;
}*/