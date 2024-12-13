#include <stdio.h>
#include "../../include/ADT/stack.h"

void CreateEmpty(Stack *S) {
    Top(*S) = Nil;
}

boolean IsEmpty(Stack S) {
    return (Top(S) == Nil);
}

boolean IsFull(Stack S) {
    return (Top(S) == MaxEl-1);
}

void Push(Stack * S, infotype X) {
    if (IsEmpty(*S)) {
        Top(*S) = 0;
        InfoTop(*S) = X;
    }
    else {
        Top(*S) ++;
        InfoTop(*S) = X;
    }
}

void Pop(Stack * S, infotype* X) {
    *X = InfoTop(*S);
    Top(*S) --;
}