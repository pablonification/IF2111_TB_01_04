#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/history.h"

void history(Stack *S) {
    if (IsEmptyStack(*S)) {
        printf("Kamu belum membeli barang apapun!\n");
        return;
    }
    printf("\nRiwayat pembelian barang:\n");
    for (int i = 0; i < S->TOP; i++) {
        printf("%d. %s %d\n", 
               i+1, 
               S->T[i].name, 
               S->T[i].harga);
    }
}