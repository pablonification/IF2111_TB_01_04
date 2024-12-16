/* Compile command dengan directory terdalam : /IF2111_TB_04_01
Compiler: gcc -o dl driver/driver_list.c src/ADT/list.c  */

#include <stdio.h>
#include "../include/ADT/list.h"

int main () {
    List l1 = MakeList();

    if (IsEmpty(l1)) {
        printf("List kosong.\n");
    }
    else {
        printf("List tidak kosong.\n");
    }

    InsertFirst(&l1, 100);
    InsertLast(&l1, 300);
    InsertAt(&
    l1, 200, 1);

    printf("%d\n", Length(l1));

    List l2 = MakeList();

    InsertFirst(&l2, 1);
    InsertLast(&l2, 3);
    InsertAt(&l2, 2, 1);

    List l3 = Concat(l1,l2);

    for (int i = 0; i < Length(l3); i++) {
        printf("%d ", l3.A[i]);
    }
    printf("\n");

    DeleteLast(&l3);

    printf("%d\n", Length(l3));

    if (Search(l3, 300)) {
        printf("Angka ditemukan.\n");
    }
}

// gcc -o list list.c