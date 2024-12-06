#ifndef QUANTUMWORDL3_H
#define QUANTUMWORDL3_H

#include "../ADT/boolean.h"
#include "../ADT/mesinkarakter.h"
#include "../ADT/mesinkata.h"

#define WORD_LENGTH 5
#define MAX_ATTEMPTSQ 9
#define TOTAL_WORDS 4

extern char boardq[MAX_ATTEMPTSQ][WORD_LENGTH * 3 + 1];


void evaluateGuessq(const char *target, Word guess, char *result);

boolean isValidGuessq(Word guess);

void INITIALIZED_QWORDL3(char ***wordsList, int *wordCount);

boolean compareWordss(const char *word1, const char *word2);

void playQuantumWordl3(int *money);

#endif 
