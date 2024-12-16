#include <stdio.h>
#include "../../include/features/cart.h"
#include "../../include/ADT/boolean.h"
#include "../../include/features/work.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/setmap.h"

/* asumsikan cart dibuat di main, jadi create empty mapnya tiap jalanin program*/

int cart(Map M, ListItem L){
    char input[50];
    char *firstWord, *secondWord, *thirdWord, *fourthWord;
    int subtotal = 0;

    if (IsEmptyMap(M)){
        printf("Keranjang anda masih kosong.\n");
    }
    else{
        printf("Isi Keranjang: \n");
        DisplayMap(M, L, &subtotal);
    }

    while(1){
        STARTLINE();
        collectInput(input);
        wordToString(currentWord, input);
            
        firstWord = my_strtok(input, " "); // baca kata pertama
        secondWord = my_strtok(NULL, " "); // baca kata kedua
        thirdWord = my_strtok(NULL, " "); // baca kata ketiga
        fourthWord = my_strtok(NULL, " "); // baca kata keempat

        keytype barang = "";
        valuetype jumlah = 0;
        if (thirdWord != NULL && fourthWord != NULL) {
            my_strcpy(barang, thirdWord);
            jumlah = atoi(fourthWord);
        }

        if (my_strcmp(firstWord, "HELP")){
            printf("Command list: \n");
            printf("1. CART ADD <barang> <jumlah>\n");
            printf("2. CART REMOVE <barang> <jumlah>\n");
            printf("3. CART SHOW\n");
            printf("4. CART PAY\n");
            printf("5. EXIT\n");
        }
        else if (my_strcmp(firstWord, "EXIT")){
            break;
        }
        else if (my_strcmp(firstWord, "CART")){
            if (my_strcmp(secondWord, "ADD")){
                cartAdd(&M, &L, barang, jumlah);
            }
            else if (my_strcmp(secondWord, "REMOVE")){
                cartRemove(&M, barang, jumlah);
            }
            else if (my_strcmp(secondWord, "SHOW")){
                cartShow(&M, &L, &subtotal);
                printf("Total biaya yang harus dikeluarkan: %d\n", subtotal);
            }
        //     // else if (my_strcmp(secondWord, "PAY")){
        //     //     cartPay(M, L);
        //     // } beluumm implementt
        }
        else{
            printf("Command tidak valid. Ketik HELP untuk melihat list command\n");
        }
    }
    return 0;
}

void cartAdd(Map *M, ListItem *L, keytype k, valuetype v){

    if (v <= 0){
        printf("Jumlah barang tidak valid.\n");
        return;
    }

    if (IsFullMap(*M)){
        printf("Keranjang penuh.\n");
        return;
    }

    int i = 0;
    boolean found = FALSE;

    while (i < L->itemLength && !found) {
        if(my_strcmp(L->item[i].name, k)){
            found = TRUE;
            break;
        }
        i++;
    }

    if (found){
        if (!IsMemberMap(*M, k)){
            Insert(M, k, v);
            printf("%s sebanyak %d berhasil ditambahkan ke keranjang.\n", k, v);
        }
        else{
            M->Elements[i-1].Value += v;
            printf("%s sebanyak %d berhasil ditambahkan ke keranjang.\n", k, v);
        }
    }
    else{
        printf("Barang tidak ditemukan.\n");
    }
}

void cartRemove(Map *M, keytype k, valuetype v){
    int i = 0;
    boolean found = FALSE;

    if (IsEmptyMap(*M)){
        printf("Tidak bise remove, keranjang kosong.\n");
        return;
    }

    if (v <= 0){
        printf("Jumlah barang tidak valid.\n");
        return;
    }

    if (!IsMemberMap(*M, k)){
        printf("Barang tidak ada di keranjang.\n");
        return;
    }

    valuetype currentJumlah = Value(*M, k);

    if (currentJumlah < v){
        printf("Gagal mengurangi. Hanya terdapat %d %s di keranjang.\n", currentJumlah, k);
    }
    else if (currentJumlah == v){
        Delete(M, k);
        printf("%s sebanyak %d berhasil dihapus dari keranjang.\n", k, v);
    }
    else{
        for (int i = 0; i < M->Count; i++) {
            if (my_strcmp(M->Elements[i].Key, k)) {
                M->Elements[i].Value -= v;
                printf("%s sebanyak %d berhasil dihapus dari keranjang.\n", k, v);
                break;
            }
        }
    }
}   


void cartShow(Map *M, ListItem *L, int *subtotal){
    if (IsEmptyMap(*M)){
        printf("Keranjang anda masih kosong.\n");
    }
    else{
        *subtotal = 0;
        printf("Isi Keranjangmu: \n");
        DisplayMap(*M, *L, subtotal);
    }
}

// void cartPay(Map *M, Stack *H, int *balance);
// GARAP HISTORY DULU

char* my_strtok(char* str, const char* delim) {
    static char* last;
    if (str) {
        last = str;
    }
    if (!last) {
        return NULL;
    }
    char* start = last;
    while (*last) {
        const char* d = delim;
        while (*d) {
            if (*last == *d) {
                break;
            }
            d++;
        }
        if (*d) {
            break;
        }
        last++;
    }
    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }
    return start;
}