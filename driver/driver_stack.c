#include <stdio.h>
#include "../include/ADT/stack.h"

int main () {
    Stack s1;
    Stack s2;
    int x;
    int j = 0;

    CreateEmpty(&s1);
    CreateEmpty(&s2);

    if (IsEmpty(s1)) {
        printf("Stack kosong\n");
    }

    for (int i = 0; i < 5; i ++) {
        Push(&s1, (i+1));
    }
    Pop(&s1, &x);
    Push(&s2, x);
    
    while (!IsFull(s2)) {
        j ++;
        Push(&s2, j);
    }

    if (IsFull(s2)) {
        printf("Stack 2 penuh\n");
        printf("%d\n",InfoTop(s2));
    }
    else {
        printf("Masih belum penuh\n");
        printf("%d\n", InfoTop(s2));
    }

    return 0;
}