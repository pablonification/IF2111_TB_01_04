/* Compile command dengan directory terdalam : /IF2111_TB_04_01
Compiler: gcc -o dmkt driver/driver_mesinkata.c src/ADT/mesinkata.c src/ADT/mesinkarakter.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/ADT/mesinkata.h"

int main() {
    Word item1;
    Word item2;

    printf("Masukkan kata pertama:\n");
    STARTLINE();
    item1 = currentWord;

    printf("Masukkan kata kedua:\n");
    STARTLINE();
    item2 = currentWord;

    if (isKataEqual(item1, item2)) {
        printf("Kata sama.\n");
    } else {
        printf("Kata berbeda.\n");
    }

    if (isKataInt(item1)) {
        printf("Angka.\n");
    } else {
        printf("Bukan angka.\n");
    }

    Word item3;

    printf("Masukkan kata:\n");
    STARTLINE();
    item3 = currentWord;
    int convertedInt = WordToInt(item3);
    printf("Hasil konversi: %d\n", convertedInt);

    // const char *fileName = "testdriverkar.txt";

    char **wordsList;
    int wordCount = 0;

    // printf("\nMembaca kata dari file '%s':\n", fileName);
    LoadWordsFromFile("testdriverkar.txt", &wordsList, &wordCount);
    printf("done\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%c\n", wordsList[i]);
        free(wordsList[i]);  // Bebaskan memori untuk setiap kata
    }
    free(wordsList);  // Bebaskan daftar kata
    
    return 0;
}