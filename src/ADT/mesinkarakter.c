#include <stdio.h>
#include <stdlib.h>
#include "../../include/ADT/mesinkarakter.h"
#include "../../include/ADT/boolean.h"

char currentChar;
boolean EOP;
static FILE *pita = NULL;
static int retval;

void RESETPITA() {
/* Mengembalikan state awal pita (kosong tanpa inputan) supaya pita dapat 
   digunakan kembali tanpa overflow dari pita input sebelumnya.
   I.S. : sembarang
   F.S. : pita kosong (NULL) */
    // KAMUS LOKAL

    // ALGORITMA
    if (pita != NULL) rewind(pita);
}

void STARTFILE(char* file_name, boolean *success) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Pita yang akan diambil adalah pita yang berada di dalam file
   pada path ../data/file_name.
   Pita baca diambil dari fopen(path).
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (FALSE)
          Jika currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL
    static char path[150] = "../data/";
    int i=0, len = 8;

    RESETPITA();

    // ALGORITMA
    while (*file_name != '\0') {
        path[i+len] = *file_name;
        file_name++;
        i++;
    } path[i+len] = '\0';

    //printf("k = %s", path);
    pita = fopen(path,"r");
    if (pita != NULL) {
        *success = TRUE;
        ADV();
    } else {
        *success = FALSE;
    }
}

void START() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   Pita baca diambil dari stdin. Sebelum pembacaan, pita akan 
   dikembalikan ke state awal.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (FALSE)
          Jika currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL

    // ALGORITMA
    RESETPITA();

    pita = stdin;
    ADV();
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
          Jika  currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL

    // ALGORITMA
    retval = fscanf(pita, "%c", &currentChar);
    EOP = (currentChar == MARK);
}

FILE* openFile(const char* filepath, const char* mode) {
/* Membuka file dengan mode tertentu
       Mode yang didukung: "r" untuk read, "w" untuk write
       Mengembalikan NULL jika gagal membuka file */
    return fopen(filepath, mode);
}

int readFile(FILE *f, const char *format, int *num) {
/* Membaca satu angka dari file
       Format yang didukung: "%d"
       Mengembalikan jumlah item yang berhasil dibaca */
    return fscanf(f, format, num);
}

int readItem(FILE *f, const char *format, int *num, char *str) {
/* Membaca item (angka dan string) dari file
       Format yang didukung: "%d %[^\n]"
       Mengembalikan jumlah item yang berhasil dibaca */
    return fscanf(f, format, num, str);
}

int readItem2(FILE *f, const char *format, char *str){
    return fscanf(f, format, str);
}

int readUser(FILE *f, const char *format, int *num, char *str1, char *str2) {
/* Membaca data user (angka dan 2 string) dari file
       Format yang didukung: "%d %s %s"
       Mengembalikan jumlah item yang berhasil dibaca */
    return fscanf(f, format, num, str1, str2);
}

void writeItem(FILE *f, const char *format, int num1, char *str1) {
/* Menulis integer dan string ke file
       Format yang didukung: "%d %s\n" */
    fprintf(f, format, num1, str1);
}

void writeLen(FILE *f, const char *format, int num1) {
/* Menulis single integer ke file
       Format yang didukung: "%d\n" */
    fprintf(f, format, num1);
}

void writeUser(FILE *f, const char *format, int num1, char *str1, char *str2) {
/* Menulis integer dan dua string ke file
       Format yang didukung: "%d %s %s\n" */
    fprintf(f, format, num1, str1, str2);
}

void closeFile(FILE *f) {
/* Menutup file yang sudah dibuka */
    if (f != NULL) {
        fclose(f);
    }
}