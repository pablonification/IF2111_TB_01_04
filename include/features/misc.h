#ifndef MISC_H
#define MISC_H

#include "../ADT/mesinkata.h"

void scanWord(Word *inputWord);
int convertWordToInt(Word inputWord);
boolean isWordEqual(Word W1, Word W2);
void displayWordWithNewline(Word W);
int stringLength(char *str);
void stringCopy(char *dest, char *src);
void stringConcat(char *dest, const char *src);
boolean stringEqual(char *str1, char *str2);
boolean compareWords(const char *str, Word word, int length);
void wordToString(Word word, char *str);
int max(int a, int b, int c);
boolean IsEqual(char *str2, Word str1);

#endif
