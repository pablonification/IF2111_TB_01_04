#include <stdio.h>
#include <stdlib.h>
#include "../include/ADT/setmap.h"
#include <string.h>

int main(){
    Map M;
    CreateEmptyMap(&M);

    keytype ayam = "Ayam";
    keytype sapi = "Sapi";
    keytype kambing = "Kambing";

    Insert(&M, ayam, 10);
    Insert(&M, sapi, 5);
    Insert(&M, kambing, 3);
    
    DisplayMap(M);

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
                    printf("Barang %s tidak ada dalam map.\n", name);
                }
                break;

            case 5:
                // Display Map
                printf("\n");
                DisplayMap(M);
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

// gcc -o driversetmap driver_setmap.c ../src/ADT/setmap.c ../src/features/work.c ../src/ADT/mesinkata.c ../src/ADT/mesinkarakter.c