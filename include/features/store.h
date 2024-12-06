#ifndef storelist_H
#define storelist_H
#include <stdio.h>
#include <time.h>
#include <math.h>
//#include "../ADT/list.h"
//#include "../ADT/queue.h"
//#include "../ADT/mesinkata.h"
//#include "../ADT/mesinkarakter.h"
#include "main.h"

void storeList (ListItem *L);
// I.S List bisa saja kosong
// F.S Jika list kosong, mencetak "TOKO KOSONG"
// Jika list tidak kosong, mencetak seluruh barang yang ada di toko

void storeRemove(ListItem *L);

void storeRequest (ListItem *L, QueueItem *Q);

void storeSupply(ListItem *L, QueueItem *Q);

boolean IsEmptyItem(ListItem *L);

void DeleteAtItem(ListItem *L, IdxType i);

IdxType LastIdxItem(ListItem L);

boolean SearchItem(ListItem L, char *X);

boolean isWordInt(Word w);
#endif