#include <stdio.h>
#include "../../include/ADT/mesinkata.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/boolean.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void scanWord(Word *inputWord) {
/* Membaca input dari pengguna menggunakan mesin kata.
   I.S. : sembarang
   F.S. : inputWord berisi kata yang dibaca dari pengguna */
    STARTWORD();           // Memulai pembacaan kata
    *inputWord = currentWord; // Salin kata yang dibaca ke parameter output
}

int convertWordToInt(Word inputWord) {
/* Mengonversi Word ke integer.
   I.S. : inputWord berupa angka dalam bentuk Word
   F.S. : Nilai integer dikembalikan */
    return WordToInt(inputWord);
}

boolean isWordEqual(Word W1, Word W2) {
/* Membandingkan dua Word, apakah sama.
   I.S. : W1 dan W2 sembarang
   F.S. : Mengembalikan TRUE jika W1 sama dengan W2 */
    return isKataEqual(W1, W2);
}

void displayWordWithNewline(Word W) {
/* Menampilkan Word ke layar diikuti newline.
   I.S. : Word sembarang
   F.S. : Isi Word ditampilkan ke layar dengan newline */
    displayWord(W, TRUE);
}

int stringLength(char *str) {
/* Mengembalikan panjang dari string
    I.S : String sembarang
    F.S : Panjang string dikembalikan */
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void stringCopy(char *dest, char *src) {
/* Mengembalikan panjang dari string
    I.S : String tersalin dan hasil
          String sembarang
    F.S : Panjang string dikembalikan */
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void stringConcat(char *dest, const char *src) {
/* Mengembalikan panjang dari string
    I.S : 2 string sembarang
    F.S : Panjang string dikembalikan */
    int destLen = stringLength(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
}

boolean stringEqual(char *str1, char *str2) {
/* Mengembalikan panjang dari string
    I.S : 2 string sembarang
    F.S : Boolean str1 == str2*/
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return FALSE;
        i++;
    }
    return str1[i] == str2[i];
}

void wordToString(Word word, char *str) {
/* Mengembalikan panjang dari string
    I.S : Word dan string sembarang
    F.S : Panjang string dikembalikan */
    int i;
    for (i = 0; i < word.Length; i++) {
        str[i] = word.TabWord[i];
    }
    str[i] = '\0';
}

boolean compareWords(const char *str, Word word, int length) {
    if (word.Length != length) {
        return FALSE;
    }
    for (int i = 0; i < length; i++) {
        if (str[i] != word.TabWord[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

boolean IsEqual(char *str2, Word str1)
{
    int i = 0;
    boolean checker = (str1.Length == stringLength(str2));
    while (str1.TabWord[i] != '\0' && str2[i] != '\0' && checker)
    {
        if (str1.TabWord[i] != str2[i])
            checker = FALSE;
        i++;
    }
    return checker;
}