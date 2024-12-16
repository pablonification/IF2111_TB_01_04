/* Compile command dengan directory terdalam : /IF2111_TB_04_01
Compiler: gcc -o dmkr driver/driver_mesinkarakter.c src/ADT/mesinkarakter.c*/

#include <stdio.h>
#include "../include/ADT/mesinkarakter.h"  


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