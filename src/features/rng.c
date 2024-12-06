#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/ADT/mesinkata.h"
#include "../../include/features/misc.h"

void tebakAngkaRNG(int *money) {
    int guess, answer, chance = 10, initial_reward = 500, reward;
    int min = 1;
    int max = 100;
    int cost = 200;
    Word inputWord;

    // cek duit
    if (*money < cost) {
        printf("Uang anda kurang, permainan ini membutuhkan 200 koin, koin anda saat ini %d\n", *money);
        return;
    }

    // kurangi duit
    *money -= cost;

    srand(time(0));
    answer = (rand() % max) + min;
    printf("%d<<<<JAWABAN\n", answer); // sementara di liatin buat testing aje

    for (int i = 1; i <= chance; i++) {
        printf("Tebak angka: ");
        scanWord(&inputWord);

        // convert
        if (isKataInt(inputWord)) {
            guess = convertWordToInt(inputWord);
        } else {
            printf("Input tidak valid. Tolong masukkan angka!\n");
            i--;
            continue;
        }

        if (guess == answer) {
            reward = initial_reward - ((i - 1) * (initial_reward / chance));
            if (reward < 50) {
                reward = 50;
            }
            printf("Tebakanmu benar!, +%d rupiah telah ditambahkan ke akun anda.\n", reward);
            *money += reward; // tambah duit
            return;
        } else if (guess > answer) {
            printf("Tebakanmu lebih besar!\n");
        } else if (guess < answer) {
            printf("Tebakanmu lebih kecil.\n");
        }
    }
    printf("Kesempatan habis! Angka yang benar adalah %d.\n", answer);
}


/*int main() {
    int *money = 1000; 
    tebakAngkaRNG(&*money);
    printf("Sisa uang anda: %d\n", *money);
    return 0;
}*/
