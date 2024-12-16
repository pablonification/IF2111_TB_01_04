/* Compile command dengan directory terdalam : /IF2111_TB_04_01
Compiler: gcc -o ds driver/driver_stack.c src/ADT/stack.c src/features/misc.c src/ADT/mesinkata.c src/ADT/mesinkarakter.c */

#include <stdio.h>
#include "../include/ADT/stack.h"

int main() {
    Stack s1;
    Stack s2;
    infotype item;
    int j = 0;

    CreateEmpty(&s1);
    CreateEmpty(&s2);

    if (IsEmpty(s1)) {
        printf("Stack kosong\n");
    }

    for (int i = 0; i < 5; i++) {
        stringCopy(item.name, "Barang");
        item.harga = (i+1) * 1000;
        Push(&s1, item);
    }

    Pop(&s1, &item);
    Push(&s2, item);
    while (!IsFull(s2)) {
        j++;
        stringCopy(item.name, "Item");
        item.harga = j * 500;
        Push(&s2, item);
    }

    if (IsFull(s2)) {
        printf("Stack 2 penuh\n");
        printf("Item teratas: %s dengan harga %d\n", s2.T[s2.TOP].name, s2.T[s2.TOP].harga);
    }
    else {
        printf("Masih belum penuh\n");
        printf("Item teratas: %s dengan harga %d\n", s2.T[s2.TOP].name, s2.T[s2.TOP].harga);
    }

    return 0;
}