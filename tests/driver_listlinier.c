/* Compile command dengan directory terdalam : /IF2111_TB_04_01
gcc -o tes src/ADT/listlinier.c src/features/misc.c src/ADT/mesinkata.c src/ADT/mesinkarakter.c */  

#include <stdio.h>
#include "../include/ADT/listlinier.h"

int main() {
    ListLinier L;
    
    printf("=== Test 1: Inisialisasi List ===\n");
    CreateEmptyLL(&L);
    printf("List kosong: %s\n", IsEmptyLL(L) ? "true" : "false");
    printf("\n");

    printf("=== Test 2: Insert Operations ===\n");
    InsertLastLL(&L, "Barang1");
    InsertLastLL(&L, "Barang2");
    InsertLastLL(&L, "Barang3");
    printf("List setelah insert:\n");
    displayListLinier(L);
    printf("Jumlah elemen: %d\n", NbElmt(L));
    printf("\n");

    printf("=== Test 3: Search Operation ===\n");
    printf("Barang2 ada dalam list: %s\n", isMemberLL(L, "Barang2") ? "true" : "false");
    printf("Barang4 ada dalam list: %s\n", isMemberLL(L, "Barang4") ? "true" : "false");
    printf("\n");

    printf("=== Test 4: Swap Operation ===\n");
    printf("List sebelum swap:\n");
    displayListLinier(L);
    swapListLinier(&L, 1, 3);
    printf("List setelah swap elemen 1 dan 3:\n");
    displayListLinier(L);
    printf("\n");

    printf("=== Test 5: Delete Operations ===\n");
    DeleteByValueLL(&L, "Barang2");
    printf("List setelah delete Barang2:\n");
    displayListLinier(L);
    printf("\n");

    printf("=== Test 6: Get Operation ===\n");
    char* item = GetLL(L, 1);
    if (item != NULL) {
        printf("Item pada indeks 1: %s\n", item);
    }
    printf("\n");

    printf("=== Test 7: Clear Operation ===\n");
    ClearLL(&L);
    printf("List setelah clear:\n");
    displayListLinier(L);
    printf("\n");

    printf("=== Test 8: Complex Operations ===\n");
    InsertLastLL(&L, "AK47");
    InsertLastLL(&L, "Lalabu");
    InsertLastLL(&L, "Meong");
    printf("Wishlist awal:\n");
    displayListLinier(L);
    
    swapListLinier(&L, 1, 2);
    printf("\nSetelah swap item 1 dan 2:\n");
    displayListLinier(L);
    
    DeleteAtLL(&L, 1);
    printf("\nSetelah delete item pada indeks 1:\n");
    displayListLinier(L);
    
    DeleteByValueLL(&L, "Meong");
    printf("\nSetelah delete item 'Meong':\n");
    displayListLinier(L);

    printf("=== Test 9 : Invalid Swap ===\n");
    swapListLinier(&L, 1, 5);
    displayListLinier(L);

    printf("=== Test 10 : Swap Single Element ===\n");
    CreateEmptyLL(&L);
    InsertLastLL(&L, "Single");
    swapListLinier(&L, 1, 1);
    displayListLinier(L);

    printf("=== Test 11 : Delete Empty List ===\n");
    CreateEmptyLL(&L);
    DeleteAtLL(&L, 0);
    DeleteByValueLL(&L, "Not Exist");
    displayListLinier(L);

    printf("=== Test 12 : Get Invalid Index ===\n");
    char* invalidItem = GetLL(L, 999);
    printf("Invalid index: %s\n", invalidItem == NULL ? "NULL" : invalidItem);

    return 0;
}