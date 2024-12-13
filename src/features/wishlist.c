#include <stdio.h>
#include "../../include/features/wishlist.h"
#include "../../include/features/store.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/ADT/mesinkarakter.h"
#include "../../include/ADT/listlinier.h"
// #include "../../include/features/main.h"

// run : gcc -o wishlist wishlist.c ../ADT/listlinier.c ../ADT/mesinkata.c ../ADT/mesinkarakter.c misc.c store.c

/*
ini belum nanganin kasus input tidak valid atau enter langsung &&&&&&&&&&&&&&&&&&&&&&&&&
*/

// Fitur wishlistShow

/*
WISHLIST SHOW adalah command yang digunakan untuk menunjukkan barang-barang yang sudah dimasukkan ke dalam wishlist. 
Tampilan:
Berikut adalah isi wishlist-mu:
1 Ayam Geprek Bakar Crispy Besthal
2 Ayam Mangut Besthal
3 Karaage Don
4 Torikatsu Don
(nomor merupakan posisi barang dalam wishlist)
*/
void wishlistShow(WishlistUser *wishlist) {
    if(!IsEmptyLL(wishlist->wishlist_item)) {
        printf("Berikut adalah isi wishlist-mu:\n");
        addressLL P = wishlist->wishlist_item.First;
        int idx = 1;
        while (P != Nil) {
            printf("%d %s\n", idx++, P->info);
            P = P->next;
        }
    } else {
        printf("Wishlist kamu kosong!\n");
    }
}

// Fitur wishlistAdd

/*
WISHLIST ADD merupakan command yang digunakan untuk menambahkan suatau barang ke wishlist. Menggunakan fungsio InsertLastLL dari ADT ListLinier.

Tampilan:
Masukkan nama barang: Ayam Geprek Bakar Crispy Besthal

Berhasil menambahkan Ayam Geprek Bakar Crispy Besthal ke wishlist!

Alur:
- Menerima input nama barang dari pengguna  
- Cek barang apakah sudah ada di store
    - Jika barang ditemukan dalam store, maka barang berhasil ditambahkan ke wishlist dengan menggunakan fungsi InsertLastLL    
    - Jika barang ditemukan dalam store dan sudah ada di wishlist, maka barang tidak dapat ditambahkan ke wishlist
    - Jika barang tidak ditemukan dalam store, maka barang tidak dapat ditambahkan ke wishlist
*/
void wishlistAdd(ListItem *L, WishlistUser *wishlist) {
    // Terima input nama barang dari pengguna
    Word item_name;
    printf("Masukkan nama barang: ");
    STARTLINE(); // kaya scanf

    char item_namestr[MaxEl];
    item_name = currentWord;    
    wordToString(item_name, item_namestr); 

    // Cek apakah barang sudah ada di store
    // // debug kasus AK47 udah ada di wishlist &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // InsertLastLL(&wishlist->wishlist_item, "AK47");
    boolean isFoundInList = SearchItem(*L, item_namestr);
    if (isFoundInList) {
        // Cek apakah barang sudah ada di wishlist
        if (isMemberLL(wishlist->wishlist_item, item_namestr)) {
            printf("%s sudah ada di wishlist\n", item_namestr);
            wishlistAdd(L, wishlist); // kalo udah ada di wishlist, minta input lagi
        } else {
            InsertLastLL(&wishlist->wishlist_item, item_namestr);
            wishlist->number++; // increment jumlah barang di wishlist
            printf("Berhasil menambahkan %s ke wishlist!\n", item_namestr);
        }
    } else { // Barang tidak ditemukan di store
        printf("Tidak ada barang dengan nama %s!\n", item_namestr);
        wishlistAdd(L, wishlist); // kalo udah ada di wishlist, minta input lagi
    }
    // debug masuk atau ngga, MASUK tinggal integrasi sama config tapi ntaran ajalah &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    wishlistShow(wishlist);

}

// Fitur wishlistClear
/*
WISHLIST CLEAR adalah command yang digunakan untuk menghapus semua barang yang terdapat di dalam WISHLIST. 

Tampilan:
Wishlist telah dikosongkan.
*/
void wishlistClear(WishlistUser *wishlist){
    // apakah wishlist kosong?
    if (IsEmptyLL(wishlist->wishlist_item)) {
        printf("Wishlist sudah kosong.\n");
    } else {
        ClearLL(&wishlist->wishlist_item);
        printf("Wishlist telah dikosongkan.\n");
    }
}

// Fitur wishlistRemove
/*
WISHLIST REMOVE adalah command yang digunakan untuk menghapus barang dari wishlist berdasarkan nama barang yang dimasukkan pengguna. Sedangkan jika wishlistRemove diikuti oleh nomor urut barang, maka barang yang dihapus adalah barang pada posisi tersebut. wishlistRemove <i> (berdasarkan posisi)

Tampilan:
// Contoh menghapus barang “Lalabu” dari WISHLIST
>> WISHLIST REMOVE
Masukkan nama barang yang akan dihapus : Lalabu
Lalabu berhasil dihapus dari WISHLIST! 

// Command mati; Kembali ke main menu
// Contoh penghapusan wishlist yang gagal (Barang tidak ada di WISHLIST)

>> WISHLIST REMOVE
Masukkan nama barang yang akan dihapus : LoremIpsum
Penghapusan barang WISHLIST gagal dilakukan, LoremIpsum tidak ada di WISHLIST!

// Command mati; Kembali ke main menu


*/

/*
Step:
- Menentukan apakah pemanggilan fungsi wishlistRemove diikuti oleh nama barang atau nomor urut barang
- Jika diikuti oleh nama barang, maka gunakan fungsi DeleteByValueLL
- Jika diikuti oleh nomor urut barang, maka gunakan fungsi DeleteAtLL
*/

boolean isNumber(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] < '0' || str[i] > '9'){
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

void wishlistRemove(WishlistUser *wishlist){
    // Terima input nama barang dari pengguna
    Word input;
    printf("Masukkan nama/nomor barang yang akan dihapus: ");
    STARTLINE(); // kaya scanf

    char inputstr[MaxEl];
    input = currentWord;    
    wordToString(input, inputstr);

    // Cek apakah input berupa nomor atau nama barang
    if (isNumber(inputstr)) {
        int idx = convertWordToInt(input);
        if (idx > 0 && idx <= wishlist->number) {
            DeleteAtLL(&wishlist->wishlist_item, idx-1);
            printf("Barang pada posisi %d berhasil dihapus dari wishlist!\n", idx);
        } else {
            printf("Penghapusan barang wishlist gagal dilakukan, posisi %d tidak ada di wishlist!\n", idx);
            wishlistRemove(wishlist); // kalo index salah, minta input lagi
        }
    } else {
        // Cek apakah barang sudah ada di wishlist
        if (isMemberLL(wishlist->wishlist_item, inputstr)) {
            DeleteByValueLL(&wishlist->wishlist_item, inputstr);
            printf("%s berhasil dihapus dari wishlist!\n", inputstr);
        } else {
            printf("Penghapusan barang wishlist gagal dilakukan, %s tidak ada di wishlist!\n", inputstr);
            wishlistRemove(wishlist); // kalo barangnya ga ada, minta input lagi
        }
    }
    wishlistShow(wishlist);
}



// Fitur wishlistSwap <i> <j> (berdasarkan posisi)
/*
WISHLIST SWAP merupakan command yang digunakan untuk menukar barang posisi ke-i dengan barang posisi ke-j pada wishlist. Posisi i dan j merupakan urutan barang pada wishlist, urutan dimulai dari 1. 

Tampillan:
>> WISHLIST SWAP 1 2
Berhasil menukar posisi Ayam Geprek Bakar Crispy Besthal dengan Ayam Mangut Besthal pada wishlist!
// Urutan Ayam Geprek Bakar Crispy Besthal berubah dari 1 menjadi 2. Sebaliknya, urutan Ayam Mangut Besthal berubah dari 2 menjadi 1
>> WISHLIST SWAP 1 2
Gagal menukar posisi Ayam Geprek Bakar Crispy Besthal!
// Hanya terdapat satu barang (Ayam Geprek Bakar Crispy Besthal) pada wishlist sehingga posisinya tidak dapat ditukar
*/
void wishlistSwap(WishlistUser *wishlist, int i, int j) {
    if (i > 0 && i <= wishlist->number && j > 0 && j <= wishlist->number) {
        // Store items before swapping
        char item1[MaxEl], item2[MaxEl];
        char *tmp1 = GetLL(wishlist->wishlist_item, i);
        char *tmp2 = GetLL(wishlist->wishlist_item, j);
        
        // Manual array copy
        int k;
        for(k = 0; tmp1[k] != '\0'; k++) item1[k] = tmp1[k];
        item1[k] = '\0';
        for(k = 0; tmp2[k] != '\0'; k++) item2[k] = tmp2[k];
        item2[k] = '\0';
        
        swapListLinier(&wishlist->wishlist_item, i-1, j-1);
        
        printf("Urutan %s berubah dari %d menjadi %d. Sebaliknya, urutan %s berubah dari %d menjadi %d\n", 
               item1, i, j, item2, j, i);
    } else {
        if (wishlist->number <= 1) {
            printf("Hanya terdapat satu barang (%s) pada wishlist sehingga posisinya tidak dapat ditukar\n", 
                   GetLL(wishlist->wishlist_item, 1));
        } else {
            printf("Posisi tidak valid!\n");
        }
    }
    wishlistShow(wishlist);
}




// biar jalan NTAR HAPUS &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int customStringCMP(const char *str1, const char *str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void customStringCPY(char *dest, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void insertLastItem(ListItem *itemlist, Item item){
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
    }
}

// driver main untuk testing sementara
int main(){
    // testing wishlistAdd
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
    // wishlistAdd(&itemList, &wishlist);
    // wishlistAdd(&itemList, &wishlist);
    // wishlistAdd(&itemList, &wishlist);

    // wishlistShow(&wishlist);
    // // wishlistClear(&wishlist);
    // wishlistRemove(&wishlist);
    // wishlistShow(&wishlist);
    // wishlistRemove(&wishlist);
    // wishlistShow(&wishlist);
    wishlistSwap(&wishlist, 1, 2);
    
    return 0;
}