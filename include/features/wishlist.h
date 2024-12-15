#ifndef WISHLIST_H
#define WISHLIST_H

#include <stdio.h>
// #include "../../include/features/wishlist.h"
#include "../../include/features/store.h"
#include "../../include/features/misc.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/ADT/mesinkarakter.h"
#include "../../include/ADT/listlinier.h"

typedef struct {
    ListLinier wishlist_item;
    int number;
} WishlistUser;

// Function prototypes
void wishlistShow(WishlistUser *wishlist);
void wishlistAdd(ListItem *L, WishlistUser *wishlist);
void wishlistClear(WishlistUser *wishlist);
void wishlistRemove(WishlistUser *wishlist);
boolean isNumber(char *str);
void wishlistSwap(WishlistUser *wishlist, int i, int j);

#endif