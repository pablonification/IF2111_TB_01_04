#include <stdio.h>
#include "../include/features/store.h"

void storelist(){
    ListItem L = {
        .item = {
        {"AK47", 20},
        {"Lalabu", 20}
        },
        .itemLength = 2
    };

    storeList(&L);
}

int main() {
    storelist();
    return 0;
}