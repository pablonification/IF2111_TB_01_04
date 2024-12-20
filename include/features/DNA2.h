#include "../ADT/boolean.h"
#include "../ADT/mesinkarakter.h"
#include "../ADT/mesinkata.h"
#include "misc.h"

static int mismatch = 0;
static int gap = -1;
static int match = 1;


boolean isDNAvalid(Word sequence);
/* Mengembalikan true jika sequence merupakan DNA valid, yaitu hanya terdiri dari karakter A, T, C, dan G */

int needlemanWunsch(Word ref, Word query, char *alignedRef, char *alignedQuery, int *alignedLength);
/* Algoritma dynamic programming untuk menghitung skor dari kococokan sequence*/

void traceback(Word ref, Word query, int **matrix, int m, int n, char *alignedRef, char *alignedQuery, int *alignedLength);
/* Fungsi melakukan handling gap pada pencetakan alignedRef dan alignedQuery (sudah disejajarkan) */

int GlobalAlignment();
/* Fungsi utama untuk deteksi kebocoran DNA */


