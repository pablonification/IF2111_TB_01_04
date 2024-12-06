/* File: mesinkarakter.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "boolean.h"

#define MARK '\n'
/* State Mesin */
extern char currentChar;
extern boolean EOP;

void RESETPITA();
/* Mengembalikan state awal pita (kosong tanpa inputan) supaya pita dapat 
   digunakan kembali tanpa overflow dari pita input sebelumnya.
   I.S. : sembarang
   F.S. : pita kosong (NULL) */

void STARTFILE(char* file_name, boolean *success);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Pita yang akan diambil adalah pita yang berada di dalam file
   pada path ../data/file_name.
   Pita baca diambil dari fopen(path).
   I.S. : sembarang
   F.S. : currenChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void START();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   Pita baca diambil dari stdin. Sebelum pembacaan, pita akan 
   dikembalikan ke state awal.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (false)
          Jika currentChar = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
          Jika  currentChar = MARK maka EOP akan menyala (true) */


FILE* openFile(const char* filepath, const char* mode);
int readFile(FILE *f, const char *format, int *num);
int readItem(FILE *f, const char *format, int *num, char *str);
int readUser(FILE *f, const char *format, int *num, char *str1, char *str2);
void writeItem(FILE *f, const char *format, int num1, char *str1);
void writeLen(FILE *f, const char *format, int num1);
void writeUser(FILE *f, const char *format, int num1, char *str1, char *str2);
void closeFile(FILE *f);

#endif
