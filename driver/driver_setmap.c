/* Compile command dengan directory terdalam : /IF2111_TB_04_01
Compiler: gcc -o dsm driver/driver_setmap.c src/ADT/setmap.c  */

#include <stdio.h>
#include <stdlib.h>
#include "../include/ADT/setmap.h"
#include <string.h>

int main(){
    ListItem L = {
        .item = {
        {"AK47", 20},
        {"Lalabu", 20}
        },
        .itemLength = 2
    };

    Map M;
    CreateEmptyMap(&M);

    int subtotal = 0;

    keytype ak47 = "AK47";
    keytype lalabu = "Lalabu";

    Insert(&M, ak47, 2);
    Insert(&M, lalabu, 5);
    
    DisplayMap(M, L, &subtotal);

    int choice;
    keytype name;
    valuetype value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Value\n");
        printf("4. IsMember\n");
        printf("5. DisplayMap\n");
        printf("0. Exit\n");
        printf("Pilih fungsi: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                // Insert
                printf("Nama barang yang dimasukkan: ");
                fgets(name, MAX_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Jumlah barang: ");
                scanf("%d", &value);
                getchar();

                Insert(&M, name, value);
                printf("Barang ditambahkan.\n");
                break;

            case 2:
                // Delete
                printf("Nama barang yang dihapus: ");
                fgets(name, MAX_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                Delete(&M, name);
                printf("Item dihapus.\n");
                break;

            case 3:
                // Value
                printf("Nanya stok barang apa: ");
                fgets(name, MAX_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                value = Value(M, name);
                if (value != Undefined) {
                    printf("Stok %s: %d\n", name, value);
                } else {
                    printf("Barang tidak ditemukan.\n");
                }
                break;

            case 4:
                // IsMember
                printf("Barang yang ingin dicek: ");
                fgets(name, MAX_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                if (IsMemberMap(M, name)) {
                    printf("Barang %s ada dalam map.\n", name);
                } else {
                    printf("Barang %s tidak ada dalam map.\n");
                }
                break;

            case 5:
                // Display Map  
                subtotal = 0;

                printf("\n");
                DisplayMap(M, L, &subtotal);
                printf("Total: %d\n", subtotal);
                break;

            case 0:
                // Exit
                break;

            default:
                printf("Input invalid. Masukkan 0-5\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

// beberapa issue mungkin terjadi di driver ini karena fungsi fungsinya diadapt untuk bekerja di cart.c
// gcc -o driversetmap driver_setmap.c ../src/ADT/setmap.c ../src/features/work.c ../src/ADT/mesinkata.c ../src/ADT/mesinkarakter.c