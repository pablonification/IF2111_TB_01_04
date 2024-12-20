#include <stdio.h>
#include "../../include/features/wishlist.h"
#include "../../include/features/store.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/ADT/mesinkarakter.h"
#include "../../include/ADT/listlinier.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Fitur wishlistShow
// Menampilkan isi wishlist pengguna
void wishlistShow(WishlistUser *wishlist) {
    if (!IsEmptyLL(wishlist->wishlist_item)) {
        printf(CYAN"Berikut adalah isi wishlist-mu:\n"WHITE);
        addressLL P = wishlist->wishlist_item.First;
        int idx = 1;
        while (P != Nil) {
            printf(CYAN"%d %s\n"WHITE, idx++, P->info);
            P = P->next;
        }
    } else {
        printf(YELLOW"Wishlist kamu kosong!\n"WHITE);
    }
}

// Fitur wishlistAdd
// Menambahkan barang ke wishlist jika barang ada di store dan belum ada di wishlist
void wishlistAdd(ListItem *L, WishlistUser *wishlist) {
    Word item_name;
    printf("Masukkan nama barang: ");
    STARTLINE();

    char item_namestr[MaxEl];
    item_name = currentWord;    
    wordToString(item_name, item_namestr); 

    // Cek apakah barang ada di store
    boolean isFoundInList = SearchItem(*L, item_namestr);
    if (isFoundInList) {
        // Cek apakah barang sudah ada di wishlist
        if (isMemberLL(wishlist->wishlist_item, item_namestr)) {
            printf(RED"%s sudah ada di wishlist\n"WHITE, item_namestr);
            wishlistAdd(L, wishlist); // Minta input ulang
        } else {
            InsertLastLL(&wishlist->wishlist_item, item_namestr);
            wishlist->number++;
            printf(GREEN"Berhasil menambahkan %s ke wishlist!\n"WHITE, item_namestr);
        }
    } else {
        printf(RED"Tidak ada barang dengan nama %s!\n"WHITE, item_namestr);
        wishlistAdd(L, wishlist); // Minta input ulang
    }
    // wishlistShow(wishlist);
}

// Fitur wishlistClear
// Menghapus semua barang di wishlist
void wishlistClear(WishlistUser *wishlist) {
    if (IsEmptyLL(wishlist->wishlist_item)) {
        printf(YELLOW"Wishlist sudah kosong.\n"WHITE);
    } else {
        ClearLL(&wishlist->wishlist_item);
        printf(GREEN"Wishlist telah dikosongkan.\n"WHITE);
    }
}

// Fitur wishlistRemove
// Menghapus barang dari wishlist berdasarkan nama atau nomor urut
boolean isNumber(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

void wishlistRemove(WishlistUser *wishlist) {
    Word input;
    printf("Masukkan nama/nomor barang yang akan dihapus: ");
    STARTLINE();

    char inputstr[MaxEl];
    input = currentWord;    
    wordToString(input, inputstr);

    // Cek apakah input berupa nomor atau nama barang
    if (isNumber(inputstr)) {
        int idx = convertWordToInt(input);
        if (idx > 0 && idx <= wishlist->number) {
            DeleteAtLL(&wishlist->wishlist_item, idx - 1);
            printf(GREEN"Barang pada posisi %d berhasil dihapus dari wishlist!\n"WHITE, idx);
        } else {
            printf(RED"Penghapusan barang wishlist gagal dilakukan, posisi %d tidak ada di wishlist!\n"WHITE, idx);
            wishlistRemove(wishlist); // Minta input ulang
        }
    } else {
        if (isMemberLL(wishlist->wishlist_item, inputstr)) {
            DeleteByValueLL(&wishlist->wishlist_item, inputstr);
            printf(GREEN"%s berhasil dihapus dari wishlist!\n"WHITE, inputstr);
        } else {
            printf(RED"Penghapusan barang wishlist gagal dilakukan, %s tidak ada di wishlist!\n"WHITE, inputstr);
            wishlistRemove(wishlist); // Minta input ulang
        }
    }
    wishlistShow(wishlist);
}

// Fitur wishlistSwap
// Menukar posisi dua barang dalam wishlist
void wishlistSwap(WishlistUser *wishlist, int i, int j) {
    if (i > 0 && i <= wishlist->number && j > 0 && j <= wishlist->number) {
        char item1[MaxEl], item2[MaxEl];
        char *tmp1 = GetLL(wishlist->wishlist_item, i);
        char *tmp2 = GetLL(wishlist->wishlist_item, j);
        
        // Salin nama barang
        int k;
        for (k = 0; tmp1[k] != '\0'; k++) item1[k] = tmp1[k];
        item1[k] = '\0';
        for (k = 0; tmp2[k] != '\0'; k++) item2[k] = tmp2[k];
        item2[k] = '\0';
        
        swapListLinier(&wishlist->wishlist_item, i - 1, j - 1);
        
        printf(GREEN"Urutan %s berubah dari %d menjadi %d. Sebaliknya, urutan %s berubah dari %d menjadi %d\n"WHITE, 
               item1, i, j, item2, j, i);
    } else {
        if (wishlist->number <= 1) {
            printf(YELLOW"Hanya terdapat satu barang (%s) pada wishlist sehingga posisinya tidak dapat ditukar\n"WHITE, 
                   GetLL(wishlist->wishlist_item, 1));
        } else {
            printf(RED"Posisi tidak valid!\n"WHITE);
        }
    }
    wishlistShow(wishlist);
}

// Fungsi tambahan untuk string manipulasi
int customStringCMP(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void customStringCPY(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void insertLastItem(ListItem *itemlist, Item item) {
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf(RED"Item sudah penuh. Tidak bisa menambahkan item %s\n"WHITE, item.name);
    }
}

// Driver main untuk testing
int main() {
    ListItem itemList = {
        .item = {
            {"AK47", 20},
            {"Lalabu", 20},
            {"Ayam Goreng Crisbar", 10},
            {"Kunjaw UAS Alstrukdat", 50}
        },
        .itemLength = 4
    };
    WishlistUser wishlist;
    CreateEmptyLL(&wishlist.wishlist_item);
    wishlist.number = 0;

    wishlistAdd(&itemList, &wishlist);
    return 0;
}
