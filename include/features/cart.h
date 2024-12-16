#ifndef CART_H
#define CART_H
#include <stdio.h>
#include "../ADT/setmap.h"
#include "../ADT/mesinkata.h"
#include "../ADT/mesinkarakter.h"

int cart(Map M, ListItem L);

void cartAdd(Map *M, ListItem *L, keytype k, valuetype v);

void cartRemove(Map *M, keytype k, valuetype v);

void cartShow(Map *M, ListItem *L, int *subtotal);

// void cartPay(Map *M, Stack *H, int *balance); /***temporary asumsi gini sih, ngerjain history dulu brg omar***/

char* my_strtok(char* str, const char* delim);

#endif