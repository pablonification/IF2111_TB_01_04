/* File: listlinier.h */
/* Definisi ListLinier*/

#ifndef LISTLINIER_H
#define LISTLINIER_H

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ADT/boolean.h"
#include "../../include/features/misc.h"

#define Nil NULL
#define MaxEl 100

typedef char* infotypeLL;
typedef struct tElmtlist *addressLL;
typedef struct tElmtlist { 
    char info[MaxEl];
    addressLL next;
} ElmtList;

typedef struct {
    addressLL First;
    char Name[MaxEl];
} ListLinier;

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLL(ListLinier L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLL(ListLinier *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addressLL AlokasiLL(infotypeLL X);
/* Mengembalikan addressLL hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressLL tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiLL(addressLL *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressLL P */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
void InsertFirstLL(ListLinier *L, infotypeLL X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void InsertLastLL(ListLinier *L, infotypeLL X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void InsertAtLL(ListLinier *L, infotypeLL X, int idx);
/* I.S. L tidak mungkin kosong, idx valid */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada posisi idx yang bernilai X */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
void DeleteFirstLL(ListLinier *L);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void DeleteLastLL(ListLinier *L);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

void DeleteAtLL(ListLinier *L, int idx);
/* I.S. list tidak kosong, idx valid */
/* F.S. Elemen list pada posisi idx dihapus */

void DeleteByValueLL(ListLinier *L, infotypeLL X);
/* I.S. list tidak kosong */
/* F.S. Menghapus elemen list yang memiliki nilai X */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayListLinier(ListLinier L);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, semua elemen list di-print */
/* Jika list kosong, hanya menuliskan "List kosong" */

int NbElmt(ListLinier L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

/****************** PROSES TERHADAP LIST ******************/
void swapListLinier(ListLinier *L, int x, int y);
/* I.S. L terdefinisi, x dan y valid */
/* F.S. Elemen ke-x dan ke-y ditukar nilainya */

char* GetLL(ListLinier L, int idx);
/* Prekondisi: list tidak kosong, idx valid */
/* Mengirimkan nilai elemen list yang ke-idx */

void ClearLL(ListLinier *L);
/* I.S. sembarang */
/* F.S. Terbentuk list kosong */

boolean isMemberLL(ListLinier L, infotypeLL X);
/* Mengirim true jika X adalah member dari L */

#endif