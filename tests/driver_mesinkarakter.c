#include <stdio.h>
#include "../../include/ADT/mesinkarakter.h"  


int main() {
    boolean success = TRUE;
    printf("\nMasukkan input:\n");
    START();  
    while (!EOP) {
        printf("%c", currentChar);  
        ADV();  
    }
    return 0;
}