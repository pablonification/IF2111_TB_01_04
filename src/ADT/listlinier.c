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

void swapListLinier(ListLinier *L, int i, int j) {
    // Validate indices
    if (i == j) return;
    
    // Get nodes at positions i and j
    addressLL prev_i = Nil;
    addressLL curr_i = L->First;
    int pos_i = 0;
    while (pos_i < i && curr_i != Nil) {
        prev_i = curr_i;
        curr_i = curr_i->next;
        pos_i++;
    }
    
    addressLL prev_j = Nil;
    addressLL curr_j = L->First;
    int pos_j = 0;
    while (pos_j < j && curr_j != Nil) {
        prev_j = curr_j;
        curr_j = curr_j->next;
        pos_j++;
    }
    
    // Swap nodes
    if (curr_i != Nil && curr_j != Nil) {
        // Handle if nodes are adjacent
        if (curr_i->next == curr_j) {
            curr_i->next = curr_j->next;
            curr_j->next = curr_i;
            if (prev_i != Nil) prev_i->next = curr_j;
            else L->First = curr_j;
        } else if (curr_j->next == curr_i) {
            curr_j->next = curr_i->next;
            curr_i->next = curr_j;
            if (prev_j != Nil) prev_j->next = curr_i;
            else L->First = curr_i;
        } else {
            // Non-adjacent nodes
            addressLL temp_next = curr_i->next;
            curr_i->next = curr_j->next;
            curr_j->next = temp_next;
            
            if (prev_i != Nil) prev_i->next = curr_j;
            else L->First = curr_j;
            
            if (prev_j != Nil) prev_j->next = curr_i;
            else L->First = curr_i;
        }
    }
}

char* GetLL(ListLinier L, int idx) {
    if (idx < 1) return NULL;
    
    addressLL p = L.First;
    int ctr = 1;
    
    while (p != Nil && ctr < idx) {
        p = p->next;
        ctr++;
    }
    
    return (p != Nil) ? p->info : NULL;
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