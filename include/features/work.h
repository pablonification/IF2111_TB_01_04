#ifndef WORK_H
#define WORK_H

// #include "../ADT/mesinkata.h"
#include "../ADT/boolean.h"

unsigned my_strlen( char *str);
boolean my_strcmp( char *str1,  char *str2);

typedef struct{
    char workName[100]; //nama pekerjaan
    int workPayment;    //gaji
    int workDuration;   //durasi kerja
} Work;

// void delay(int seconds);
// void collectInput(char *input);
// void work(int *balance);

#endif