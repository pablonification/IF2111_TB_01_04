/* File : stack.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "boolean.h"
#include "../features/misc.h"

#define Nil -1
#define MaxEl 100
#define MAX_LEN 50

// Original stack definitions
typedef int address;

// Definisi StackItem untuk riwayat pembelian
typedef struct {
    char name[MAX_LEN];  // Nama item yang dibeli
    int harga;           // Harga item
} infotype;

// Definisi Stack untuk menyimpan riwayat pembelian
typedef struct { 
    infotype T[MaxEl];  // Array of StackItem
    address TOP;        // Indeks top of stack
} Stack;

// Definisi akses original
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]


/* *** Prototype untuk Stack Riwayat Pembelian *** */
void CreateEmpty(Stack *S);
/* I.S. Sembarang */
/* F.S. Membuat sebuah stack history S yang kosong berkapasitas MaxEl */
/* Ciri stack kosong: TOP bernilai Nil */

boolean IsEmpty(Stack S);
/* Mengirim true jika Stack History kosong: TOP bernilai Nil */

boolean IsFull(Stack S);
/* Mengirim true jika stack History penuh */
/* Ciri stack penuh: TOP bernilai MaxEl */

void Push(Stack *S, infotype X);
/* Menambahkan item X sebagai elemen Stack History S */
/* I.S. S mungkin kosong, S tidak penuh */
/* F.S. X menjadi element TOP yang baru, TOP bertambah 1 */
/* Copy nama item dan harga ke dalam stack */

void Pop(Stack *S, infotype *X);
/* Menghapus item X dari Stack History S */
/* I.S. S tidak kosong */
/* F.S. X adalah nilai elemen TOP yang lama (nama dan harga item) */
/* TOP berkurang 1, elemen TOP yang lama dikembalikan ke X */

#endif