#include <stdio.h>
#include "../../include/features/cart.h"
#include "../../include/ADT/boolean.h"
#include "../../include/features/work.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/setmap.h"

/* asumsikan cart dibuat di main, jadi create empty mapnya tiap jalanin program*/

int main(){
    Map M;
    CreateEmptyMap(&M);
    ListItem L = {
        .item = {
        {"AK47", 20},
        {"Lalabu", 30}
        },
        .itemLength = 2
    };

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
        //     // }
        }
        else{
            printf("Command tidak valid. Ketik HELP untuk melihat list command\n");
        }
    }
    return 0;
}

//gcc -o drivercart drivercart.c ../ADT/setmap.c ../ADT/mesinkata.c ../ADT/mesinkarakter.c work.c misc.c cart.c