#include <stdio.h>
#include "../../include/ADT/stack.h"

void CreateEmpty(Stack *S) {
    S->TOP = Nil;
}

boolean IsEmpty(Stack S) {
    return (S.TOP == Nil);
}

boolean IsFull(Stack S) {
    return (S.TOP == MaxEl-1);
}

void Push(Stack *S, infotype X) {
    if (!IsFull(*S)) {
        if (IsEmpty(*S)) {
            S->TOP = 0;
        } else {
            S->TOP++;
        }
        stringCopy(S->T[S->TOP].name, X.name);
        S->T[S->TOP].harga = X.harga;
    }
}

void Pop(Stack *S, infotype *X) {
    if (!IsEmpty(*S)) {
        stringCopy(X->name, S->T[S->TOP].name);
        X->harga = S->T[S->TOP].harga;
        if (S->TOP == 0) {
            S->TOP = Nil;
        } else {
            S->TOP--;
        }
    }
}