#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/ADT/mesinkata.h"
#include "../../include/features/misc.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void tebakAngkaRNG(int *money) {
    int guess, answer, chance = 10, initial_reward = 500, reward;
    int min = 1;
    int max = 100;
    int cost = 200;
    Word inputWord;

    // cek duit
    if (*money < cost) {
        printf(RED"Uang anda kurang, permainan ini membutuhkan 200 koin, koin anda saat ini %d\n"WHITE, *money);
        return;
    }

    // kurangi duit
    *money -= cost;

    srand(time(0));
    answer = (rand() % max) + min;
    // printf(CYAN"%d<<<<JAWABAN\n"WHITE, answer); // sementara di liatin buat testing aje

    for (int i = 1; i <= chance; i++) {
        printf("Tebak angka: ");
        scanWord(&inputWord);

        // convert
        if (isKataInt(inputWord)) {
            guess = convertWordToInt(inputWord);
        } else {
            printf(RED"Input tidak valid. Tolong masukkan angka!\n"WHITE);
            i--;
            continue;
        }

        if (guess == answer) {
            reward = initial_reward - ((i - 1) * (initial_reward / chance));
            if (reward < 50) {
                reward = 50;
            }
            printf(GREEN"Tebakanmu benar!, +%d rupiah telah ditambahkan ke akun anda.\n"WHITE, reward);
            *money += reward; // tambah duit
            return;
        } else if (guess > answer) {
            printf(YELLOW"Tebakanmu lebih besar!\n"WHITE);
        } else if (guess < answer) {
            printf(YELLOW"Tebakanmu lebih kecil.\n"WHITE);
        }
    }
    printf(RED"Kesempatan habis! Angka yang benar adalah %d.\n"WHITE, answer);
}


/*int main() {
    int *money = 1000; 
    tebakAngkaRNG(&*money);
    printf("Sisa uang anda: %d\n", *money);
    return 0;
}*/
