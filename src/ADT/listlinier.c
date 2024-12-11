#include "../../include/ADT/listlinier.h"
#include <stdio.h>

boolean IsEmptyLL(ListLinier L) {
    return L.First == Nil;
}

void CreateEmptyLL(ListLinier *L) {
    L->First = Nil;
}

addressLL AlokasiLL(infotypeLL X) {
    addressLL P = (addressLL)malloc(sizeof(ElmtList));
    if (P != Nil) {
        stringCopy(P->info, X);
        P->next = Nil;
    }
    return P;
}

void DealokasiLL(addressLL *P) {
    free(*P);
    *P = Nil;
}

void InsertFirstLL(ListLinier *L, infotypeLL X) {
    addressLL P = AlokasiLL(X);
    if (P != Nil) {
        P->next = L->First;
        L->First = P;
    }
}

void InsertLastLL(ListLinier *L, infotypeLL X) {
    if (IsEmptyLL(*L)) {
        InsertFirstLL(L, X);
    } else {
        addressLL P = AlokasiLL(X);
        if (P != Nil) {
            addressLL last = L->First;
            while (last->next != Nil) {
                last = last->next;
            }
            last->next = P;
        }
    }
}

void InsertAtLL(ListLinier *L, infotypeLL X, int idx) {
    if (idx == 0) {
        InsertFirstLL(L, X);
    } else {
        addressLL P = AlokasiLL(X);
        if (P != Nil) {
            addressLL curr = L->First;
            int i = 0;
            while (i < idx - 1 && curr != Nil) {
                curr = curr->next;
                i++;
            }
            if (curr != Nil) {
                P->next = curr->next;
                curr->next = P;
            }
        }
    }
}

void DeleteFirstLL(ListLinier *L) {
    if (!IsEmptyLL(*L)) {
        addressLL P = L->First;
        L->First = P->next;
        DealokasiLL(&P);
    }
}

void DeleteLastLL(ListLinier *L) {
    if (!IsEmptyLL(*L)) {
        if (L->First->next == Nil) {
            DeleteFirstLL(L);
        } else {
            addressLL last = L->First;
            addressLL prev = Nil;
            while (last->next != Nil) {
                prev = last;
                last = last->next;
            }
            prev->next = Nil;
            DealokasiLL(&last);
        }
    }
}

void DeleteAtLL(ListLinier *L, int idx) {
    if (!IsEmptyLL(*L) && idx >= 0 && idx < NbElmt(*L)) {
        if (idx == 0) {
            DeleteFirstLL(L);
        } else {
            addressLL curr = L->First;
            int i = 0;
            while (i < idx - 1) {
                curr = curr->next;
                i++;
            }
            addressLL temp = curr->next;
            curr->next = temp->next;
            DealokasiLL(&temp);
        }
    }
}

void DeleteByValueLL(ListLinier *L, infotypeLL X) {
    if (!IsEmptyLL(*L)) {
        addressLL curr = L->First;
        addressLL prev = Nil;
        boolean found = FALSE;
        
        while (curr != Nil && !found) {
            if (stringEqual(curr->info, X)) {
                found = TRUE;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        
        if (found) {
            if (prev == Nil) {
                DeleteFirstLL(L);
            } else {
                prev->next = curr->next;
                DealokasiLL(&curr);
            }
        }
    }
}

void displayListLinier(ListLinier L) {
    if (IsEmptyLL(L)) {
        printf("List kosong\n");
    } else {
        addressLL P = L.First;
        int i = 1;
        while (P != Nil) {
            printf("%d. %s\n", i, P->info);
            P = P->next;
            i++;
        }
    }
}

int NbElmt(ListLinier L) {
    int count = 0;
    addressLL P = L.First;
    while (P != Nil) {
        count++;
        P = P->next;
    }
    return count;
}

void swapListLinier(ListLinier *L, int x, int y) {
    if (x != y && x >= 1 && y >= 1 && x <= NbElmt(*L) && y <= NbElmt(*L)) {
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
        }
        
        addressLL prevX = Nil, currX = L->First;
        for (int i = 1; i < x; i++) {
            prevX = currX;
            currX = currX->next;
        }
        
        addressLL prevY = Nil, currY = L->First;
        for (int i = 1; i < y; i++) {
            prevY = currY;
            currY = currY->next;
        }
        
        if (prevX != Nil) {
            prevX->next = currY;
        } else {
            L->First = currY;
        }
        
        if (prevY != Nil) {
            prevY->next = currX;
        } else {
            L->First = currX;
        }
        
        addressLL temp = currY->next;
        currY->next = currX->next;
        currX->next = temp;
    }
}

char* GetLL(ListLinier L, int idx) {
    if (!IsEmptyLL(L) && idx >= 0 && idx < NbElmt(L)) {
        addressLL P = L.First;
        int i = 0;
        while (i < idx) {
            P = P->next;
            i++;
        }
        return P->info;
    }
    return NULL;
}

void ClearLL(ListLinier *L) {
    while (!IsEmptyLL(*L)) {
        DeleteFirstLL(L);
    }
}

boolean isMemberLL(ListLinier L, infotypeLL X) {
    addressLL P = L.First;
    while (P != Nil) {
        if (stringEqual(P->info, X)) {
            return TRUE;
        }
        P = P->next;
    }
    return FALSE;
}