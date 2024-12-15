#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/history.h"


/* Sementara sembari menunggu versi final struct global dan user*/


// boolean IsEmptyItem(ListItem *L) {
//     return L->itemLength == 0;
// }

// void customStringCPY(char *dest, const char *src){
//     int i = 0;
//     while(src[i] != '\0'){
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
// }

void history(int n, /*User *user,*/ ListItem *barang) {
    if (n == 0) {
        return;
    } else {
        if (IsEmptyItem(barang)) {
            printf("Riwayat pembelian kosong\n");
        } 
        else {
            if (n > barang->itemLength) {
                n = barang->itemLength;
            }
            printf("Riwayat pembelian barang:\n");
            for (int i = 0; i < n; i++) {
                printf("%d. %s %d\n", i + 1, barang->item[i].name, barang->item[i].price);
            }
        }
    }
}

// int main() {
//     ListItem *barang;
//     int num;
//     Word number;

//     barang = (ListItem *)malloc(sizeof(ListItem));

//     for (int i = 0; i < MaxEl; i++) {
//         barang->item[i].price = 0;
//         barang->item[i].name[0] = '\0';
//     }

//     customStringCPY(barang->item[0].name, "AK47");
//     customStringCPY(barang->item[1].name, "AK47");
//     customStringCPY(barang->item[2].name, "Lalabu");
//     customStringCPY(barang->item[3].name, "AK47");
//     customStringCPY(barang->item[4].name, "Meong");
//     customStringCPY(barang->item[5].name, "Ayam Goreng Crisbar");

//     barang->item[0].price = 40;
//     barang->item[1].price = 100;
//     barang->item[2].price = 35;
//     barang->item[3].price = 10;
//     barang->item[4].price = 500;
//     barang->item[5].price = 20;
//     barang->itemLength = 6;

//     for (int i = 0; i < barang->itemLength; i++) {
//         printf("%d. %s (Harga: %d)\n",
//                i + 1,
//                barang->item[i].name,
//                barang->item[i].price);
//     }

//     STARTLINE();
//     number = currentWord;
//     num = WordToInt(number);
//     printf("%d\n", num);

//     history(num, barang);
//     free(barang);
//     return 0;
// }