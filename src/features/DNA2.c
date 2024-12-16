#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/DNA2.h"

boolean isDNAvalid(Word sequence){
    for (int i = 0;i < sequence.Length;i++){
        if(sequence.TabWord[i] != 'A' && sequence.TabWord[i] != 'T' && sequence.TabWord[i] != 'C' && sequence.TabWord[i] != 'G'){
            return FALSE;
        }
    }
    return TRUE;
}
int needlemanWunsch(Word ref, Word query){
    int m = ref.Length + 1;
    int n = query.Length + 1;
    int **matrix = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) matrix[i][0] = i * gap;
    for (int j = 0; j < n; j++) matrix[0][j] = j * gap;

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            int matchscore = matrix[i-1][j-1] + 
                       (ref.TabWord[i-1] == query.TabWord[j-1] ? match : mismatch);
            int deletescore = matrix[i-1][j] + gap;
            int insertscore = matrix[i][j-1] + gap;
            
            matrix[i][j] = max(matchscore, deletescore, insertscore);
        }
    }

    int score = matrix[m-1][n-1];

    for (int i = 0; i < m; i++) free(matrix[i]);
    free(matrix);

    return score;
}


int deteksiKebocoranDNA(){
    Word reference, query;

    printf("Masukkan sequence referensi: ");
    STARTLINE();
    reference = currentWord;
    
    printf("Masukkan sequence query: ");
    STARTLINE();
    query = currentWord;

    if (!isDNAvalid(reference) || !isDNAvalid(query)) {
        printf("sekuens DNA invalid! (harus ACGT)\n");
        return 1;
    }

    int score = needlemanWunsch(reference, query);
    printf("=> GLOBALALIGNMENT\n");
    printf("Masukkan sequence referensi: ");
    for (int i = 0; i < reference.Length; i++) printf("%c", reference.TabWord[i]);
    printf(" // Panjang: %d karakter\n", reference.Length);
    
    printf("Masukkan sequence query: ");
    for (int i = 0; i < query.Length; i++) printf("%c", query.TabWord[i]);
    printf(" // Panjang: %d karakter\n", query.Length);
    
    printf("\nSkor: %d\n", score);
    printf("Sequence yang telah disejajarkan:\n");
    for (int i = 0; i < reference.Length; i++) printf("%c", reference.TabWord[i]);
    printf("\n");
    for (int i = 0; i < query.Length; i++) printf("%c", query.TabWord[i]);
    printf("\n\n");

    double threshold = reference.Length * 0.8;
    printf("Hmm! %s kebocoran... (%s) // %.0f+80%% = %.2f %c %d (%s)\n", 
        (score > threshold) ? "Ada" : "Tidak ada",
        (score > threshold) ? "≥-5" : "≤-5",
        (double)reference.Length, threshold,
        (score > threshold) ? '>' : '<',
        score,
        (score > threshold) ? "(lebih tinggi)" : "(lebih rendah)");

    return 0;
}

int main(){
    return deteksiKebocoranDNA();
}