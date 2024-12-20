/*
isEmpty harus buat lagi

terus fungsi aymar juga ada yg harus dibuat lagi insertLast
*/

#include <stdio.h>
#include "../../include/features/store.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/ADT/mesinkarakter.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void storeList (ListItem *L) {
    if (IsEmptyItem(L)) {
        printf(RED"TOKO KOSONG\n"WHITE);
    }
    else { 
        printf(CYAN"List barang yang ada di toko: \n"WHITE);
        for (int i  = 0; i < L->itemLength; i ++) {
            printf("");
            printf(CYAN"%d. %s - Harga: %d\n"WHITE, i + 1, L->item[i].name, L-> item[i].price);
        }
        printf("\n");
    }
}
  
void storeRequest(ListItem *L, QueueItem *Q) {
    Word req;
    char reqstr[MaxEl]; // Ensure sufficient size
    boolean found = FALSE;

    printf("Nama barang yang diminta: ");
    STARTLINE();
    req = currentWord;
    wordToString(req, reqstr); // Convert Word to string

    boolean isFoundInList = SearchItem(*L, reqstr);
    if (isFoundInList) {
        printf(RED"Barang dengan nama yang sama sudah ada di toko\n"WHITE);
    } else if (isEmptyItem(*Q)) {
        enqueueItem(Q, reqstr);
    } else {
        boolean foundInQueue = FALSE;
        int queueLength = lengthQueueItem(*Q);

        for (int i = 0; i < queueLength; i++) {
            char temp[MaxEl];
            dequeueItem(Q, temp); // Dequeue an item to temp
            if (customStringCMP(temp, reqstr) == 0) {
                foundInQueue = TRUE;
            }
            enqueueItem(Q, temp); // Re-enqueue the item
        }

        if (foundInQueue) {
            printf(RED"Barang dengan nama yang sama sudah ada di antrian\n"WHITE);
        } else {
            enqueueItem(Q, reqstr);
        }
    }
}

void storeRemove(ListItem *L) {
    Word item_name;
    printf("Nama barang yang akan dihapus: ");
    STARTLINE();
    item_name = currentWord;
    
    char item_namestr[50];
    wordToString(item_name, item_namestr);

    boolean found = 0;
    int i = 0;

    while (i < L->itemLength && !found) {
        if (customStringCMP(item_namestr, (*L).item[i].name) == 0) {
            found = 1;
        }
        i++;
    }

    if (found) {
        DeleteAtItem(L, i-1);
        printf(GREEN"%s telah berhasil dihapus.\n"WHITE, item_namestr);
    }
    else {
        printf(RED"Toko tidak menjual %s.\n"WHITE, item_namestr);
    }
}

void storeSupply(ListItem *L, QueueItem *Q) { 
    if (!isEmptyItem(*Q)) {
        char item_name[50];
        dequeueItem(Q, item_name);
        printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak): ", item_name);

        Word response;
        STARTLINE();
        char responsestr;
        response = currentWord;
        wordToString(response, &responsestr);
        boolean inputValid = FALSE;

        while (!inputValid) {
            if (customStringCMP(&responsestr, "Terima") == 0 || customStringCMP(&responsestr, "Tunda") == 0 || customStringCMP(&responsestr, "Tolak") == 0) {
                inputValid = TRUE;
            }
            else {
                printf(RED"Input tidak valid. Silakan coba lagi: "WHITE);
                scanWord(&response);
                wordToString(response, &responsestr);
            }
        }

        if (customStringCMP(&responsestr, "Terima") == 0) {
            Word price;
            printf("Harga barang: ");
            scanWord(&price);
            boolean validprice = FALSE;

            while (!validprice) {
                if (isWordInt(price)) {
                    validprice = TRUE;
                }
                else {
                    printf(RED"Harga tidak valid. Silakan coba lagi: "WHITE);
                    scanWord(&price);
                }
            }

            int priceint = convertWordToInt(price);
            Item new_item;
            customStringCPY(new_item.name, item_name);
            new_item.price = priceint;

            insertLastItem(L, new_item);
            printf(GREEN"%s dengan harga %d telah ditambahkan ke toko.\n"WHITE, item_name, priceint);
        }
        else if (customStringCMP(&responsestr, "Tunda") == 0) {
            printf(YELLOW"%s dikembalikan ke antrian.\n"WHITE, item_name);
            enqueueItem(Q, item_name);
        }
        else if (customStringCMP(&responsestr, "Tolak") == 0) {
            printf(RED"%s dihapus dari antrian.\n"WHITE, item_name);
        }
    }
    else {
        printf(RED"Antrian kosong.\n"WHITE);
    }
}

boolean IsEmptyItem(ListItem *L) {
    return L->itemLength == 0;
}

void DeleteAtItem(ListItem *L, IdxType i) {
	int j = LastIdxItem(*L);
	while (i < j) {
		(*L).item[i] = (*L).item[i+1];
        i++;
	}
    (*L).itemLength -= 1;
}

IdxType LastIdxItem(ListItem L) {
    int i = 0;
    while ((i < MaxEl) && (L.item[i].name[0] != '\0')) {
        i += 1;
    }
    return i - 1;
}

boolean SearchItem(ListItem L, char *X) {
	int i = 0;
    
	int j = L.itemLength;
	boolean found = FALSE;
	while ((i < L.itemLength) && !found) {
		if (customStringCMP(L.item[i].name, X) == 0) {
			found = TRUE;
		}
		i += 1;
	}
    return found;
}

void CreateQueueItem(QueueItem *q) {
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}

boolean isEmptyItem(QueueItem q){
    return (IDX_HEAD(q) == IDX_UNDEF) && (IDX_TAIL(q) == IDX_UNDEF);
}

int lengthQueueItem(QueueItem q) {
    if (isEmptyItem(q)) {
        return 0;
    } else {
        return (IDX_TAIL(q) - IDX_HEAD(q) + 100) % 100 + 1;
    }
}

void enqueueItem(QueueItem *q, char *item_name) {
    if (q->idxTail == (q->idxHead - 1 + CAPACITY) % CAPACITY) {
        printf(RED"Queue is full! Cannot add new item.\n"WHITE);
        return;
    }

    if (isEmptyItem(*q)) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
    } else {
        IDX_TAIL(*q) = (IDX_TAIL(*q) + 1) % CAPACITY;
    }
    int i = 0;
    while (item_name[i] != '\0' && i < 100 - 1) {
        q->item_name[q->idxTail][i] = item_name[i];
        i++;
    }
    q->item_name[q->idxTail][i] = '\0';
}

void dequeueItem(QueueItem *q, char *item_name) {   
    customStringCPY(item_name, (q)->item_name[(q)->idxHead]);
    if (lengthQueueItem(*q) == 1) {
        CreateQueueItem(q);
    } else {
        IDX_HEAD(*q) = (IDX_HEAD(*q) + 1) % CAPACITY;
    }
}

boolean isWordInt(Word w) {
    int i = 0;
    for (i = 0; i < w.Length; i++) {
        if (w.TabWord[i] < '0' || w.TabWord[i] > '9') {
            return FALSE;
        }
    }
    return TRUE;
}

// int main() {
//     ListItem itemList = {
//         .item = {
//         {"AK47", 20},
//         {"Lalabu", 20},
//         {"Ayam Goreng Crisbar", 10},
//         {"Kunjaw UAS Alstrukdat", 50}
//         },
//         .itemLength = 4
//     };

//     QueueItem requestQueue;
//     CreateQueueItem(&requestQueue);

//     storeList(&itemList);
//     storeRequest(&itemList, &requestQueue);
//     storeRequest(&itemList, &requestQueue);
//     storeRequest(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeRemove(&itemList);
//     storeList(&itemList);
//     return 0;
// }
