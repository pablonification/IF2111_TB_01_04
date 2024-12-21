#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/history.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void history(Stack *S) {
    if (IsEmptyStack(*S)) {
        printf(RED"Kamu belum membeli barang apapun!\n"RESET);
        return;
    }
    printf(GREEN"Riwayat pembelian barang:\n"RESET);
    for (int i = S->TOP; i >= 0; i--) {
        printf(YELLOW"%d. %s %d\n"RESET, 
               (S->TOP-i)+1, 
               S->T[i].name, 
               S->T[i].harga);
    }
}

void historyInt(Stack *S, int *i){
    if (IsEmptyStack(*S)) {
        printf(RED"Kamu belum membeli barang apapun!\n"RESET);
        return;
    }
    printf(GREEN"Riwayat pembelian barang:\n"RESET);
    int j = S->TOP;
    int count = 0;
    while (j >= 0 && count < *i) {
        printf(YELLOW"%d. %s %d\n"RESET, 
               count + 1, 
               S->T[j].name, 
               S->T[j].harga);
        j--;
        count++;
    }
}