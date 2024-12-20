#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/ADT/boolean.h"
#include "../../include/ADT/mesinkarakter.h"
#include "../../include/ADT/mesinkata.h"
#include "../../include/features/wordl32.h"
#include "../../include/features/misc.h"
#include "../../include/features/qwordl3.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 5

char board[MAX_ATTEMPTS][WORD_LENGTH * 3 + 1];

void evaluateGuess(const char *target, Word guess, char *result) {
    int matched[WORD_LENGTH] = {0}; 
    int used[WORD_LENGTH] = {0};    

    for (int i = 0; i < WORD_LENGTH; i++) {
        result[i * 3] = guess.TabWord[i];
        result[i * 3 + 1] = '%'; 
        result[i * 3 + 2] = ' ';
    }
    result[WORD_LENGTH * 3] = '\0'; 

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess.TabWord[i] == target[i]) {
            result[i * 3 + 1] = ' '; 
            matched[i] = 1;         
            used[i] = 1;            
        }
    }

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i * 3 + 1] == '%') { 
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!matched[j] && !used[j] && guess.TabWord[i] == target[j]) {
                    result[i * 3 + 1] = '*'; 
                    used[j] = 1;            
                    break;
                }
            }
        }
    }
}


boolean isValidGuess(Word guess) {
    return (guess.Length == WORD_LENGTH);
}

// boolean compareWords(const char *target, Word guess, int LENGTH) {
//     Word targetWord;
//     targetWord.Length = LENGTH;
//     for (int i = 0; i < LENGTH; i++) {
//         targetWord.TabWord[i] = target[i];
//     }

//     return isKataEqual(targetWord, guess);
// }

// void INITIALIZED_WORDL3(char ***wordsList, int *wordCount) {
//     LoadWordsFromFile("words.txt", wordsList, wordCount);
// }

void playWordl3(int *money) {
    if (*money < 500){
        printf(RED"Uang anda kurang, challange ini membutuhkan 500 koin, koin anda saat ini %d\n"WHITE, *money);
        return;
    } else {
        *money -= 500;
        char **wordsList;
        int wordCount;
        INITIALIZED_QWORDL3(&wordsList, &wordCount);

        srand(time(NULL));
        char *answer = wordsList[rand() % wordCount];

        char board[MAX_ATTEMPTS][WORD_LENGTH * 3 + 1];
        for (int i = 0; i < MAX_ATTEMPTS; i++) {
            for (int j = 0; j < WORD_LENGTH * 3; j += 3) {
                board[i][j] = '_';
                board[i][j + 1] = ' ';
                board[i][j + 2] = ' ';
            }
            board[i][WORD_LENGTH * 3] = '\0'; 
        }

        int attempts = 0;
        boolean win = FALSE;
        Word guess;

        printf(CYAN"WELCOME TO W0RDL3, YOU HAVE %d CHANCES TO ANSWER BEFORE YOU LOSE!\n"WHITE, MAX_ATTEMPTS);

        while (attempts < MAX_ATTEMPTS && !win) {
            for (int i = 0; i < MAX_ATTEMPTS; i++) {
                printf("%s\n", board[i]);
            }
        // printf(CYAN"ANSWER>>>>>>>>>>%s\n"WHITE, answer);
            printf("Masukkan kata tebakan Anda: ");
            do {
                STARTLINE();
                guess = currentWord;


                if (guess.Length != WORD_LENGTH) {
                    printf(RED"Invalid input! Please enter a %d-letter word: "WHITE, WORD_LENGTH);
                }
            } while (guess.Length != WORD_LENGTH);

            char result[WORD_LENGTH * 3 + 1] = {0}; 
            evaluateGuess(answer, guess, result);
            for (int i = 0; i < WORD_LENGTH * 3 + 1; i++) {
                board[attempts][i] = result[i];
            }

            // Check for win condition
            if (compareWords(answer, guess, WORD_LENGTH)) {
                win = TRUE;
            }
            attempts++;
        }

        for (int i = 0; i < MAX_ATTEMPTS; i++) {
            printf("%s\n", board[i]);
        }

        if (win) {
            printf(GREEN"Selamat, Anda menang!\n+1000 rupiah telah ditambahkan ke akun Anda.\n"WHITE);
            *money += 1000;
        } else {
            printf(RED"Boo! Anda kalah. Jawaban yang benar adalah: %s\n"WHITE, answer);
        }

        free(wordsList);
    }
}