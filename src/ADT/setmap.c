#include <stdio.h>
#include "../../include/ADT/boolean.h"
#include "../../include/ADT/setmap.h"
#include "../../include/features/work.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/ADT/mesinkarakter.h"

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void CreateEmptyMap(Map *M){
    M->Count = Nil;
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Map M kosong berkapasitas MaxEl */
/* Ciri Map kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsEmptyMap(Map M){
    return M.Count == Nil;
}
/* Mengirim true jika Map M kosong*/
/* Ciri Map kosong : count bernilai Nil */

boolean IsFullMap(Map M){
    return M.Count == MaxEl;
}
/* Mengirim true jika Map M penuh */
/* Ciri Map penuh : count bernilai MaxEl */

/* ********** Operator Dasar Map ********* */
valuetype Value(Map M, keytype k){
    for (int i = 0; i < M.Count; i++){
        if (my_strcmp(M.Elements[i].Key, k)){
            return M.Elements[i].Value;
        }
    }
    return Undefined;
}
/* Mengembalikan nilai value dengan key k dari M */
/* Jika tidak ada key k pada M, akan mengembalikan Undefined */

void Insert(Map *M, keytype k, valuetype v){
    if (!IsMemberMap(*M, k)){
        my_strcpy(M->Elements[M->Count].Key, k);
        M->Elements[M->Count].Value = v;
        M->Count += 1;
    }        
}
/* Menambahkan Elmt sebagai elemen Map M. */
/* I.S. M mungkin kosong, M tidak penuh
        M mungkin sudah beranggotakan v dengan key k */
/* F.S. v menjadi anggota dari M dengan key k. Jika k sudah ada, operasi tidak dilakukan */

void Delete(Map *M, keytype k){
    if (IsMemberMap(*M, k)){
        for (int i = 0; i < M->Count; i++){
            if (my_strcmp(M->Elements[i].Key, k)){
                for (int j = i; j < M->Count - 1; j++){
                    M->Elements[j] = M->Elements[j+1];
                }
                M->Count -= 1;
                break;  
            }
        }
    }    
}
/* Menghapus Elmt dari Map M. */
/* I.S. M tidak kosong
        element dengan key k mungkin anggota / bukan anggota dari M */
/* F.S. element dengan key k bukan anggota dari M */

boolean IsMemberMap(Map M, keytype k){
    for (int i = 0; i < M.Count; i++){
        if (my_strcmp(M.Elements[i].Key, k)){
            return TRUE;
        }
    }
    return FALSE;
}
/* Mengembalikan true jika k adalah member dari M */

void DisplayMap(Map M, ListItem L, int *subtotal){
    if (IsEmptyMap(M)) {
        printf("Map is empty.\n");
    } else {
        printf("Barang         Jumlah    Total\n");
        for (int i = 0; i < M.Count; i++) {
            int harga = 0;
            boolean found = FALSE;
            for (int j = 0; j < L.itemLength; j++) {
                if (my_strcmp(L.item[j].name, M.Elements[i].Key)) {
                    harga = L.item[j].price;
                    found = TRUE;
                    break;
                }
            }

            if (found) {
                int total = harga * M.Elements[i].Value;
                *subtotal += total;
                printf("%-15s %-8d %-d\n", M.Elements[i].Key, M.Elements[i].Value, total);
            }
            else {
                printf("%-15s %-8d (Harga tidak ditemukan)\n", M.Elements[i].Key, M.Elements[i].Value);
            }
        }
    }
}

/* ********* Util ********* gajadi dipake tp keep dulu siapa tau nanti kepake */
char* my_strcpy(char* destination, const char* source) {
    char* ptr = destination;
    while (*source != '\0') {
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return destination;
}
