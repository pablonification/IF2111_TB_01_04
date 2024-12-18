#include <stdio.h>
#include "../../include/ADT/stack.h"

void CreateEmpty(Stack *S) {
    S->TOP = Nill;
}

boolean IsEmptyStack(Stack S) {
    return (S.TOP == Nill);
}

boolean IsFullStack(Stack S) {
    return (S.TOP == MaxEl-1);
}

void Push(Stack *S, infotypeStack X) {
    if (!IsFullStack(*S)) {
        if (IsEmptyStack(*S)) {
            S->TOP = 0;
        } else {
            S->TOP++;
        }
        stringCopy(S->T[S->TOP].name, X.name);
        S->T[S->TOP].harga = X.harga;
    }
}

void Pop(Stack *S, infotypeStack *X) {
    if (!IsEmptyStack(*S)) {
        stringCopy(X->name, S->T[S->TOP].name);
        X->harga = S->T[S->TOP].harga;
        if (S->TOP == 0) {
            S->TOP = Nill;
        } else {
            S->TOP--;
        }
    }
}
