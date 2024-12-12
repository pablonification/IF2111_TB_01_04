#include <stdio.h>
#include <time.h>
#include "ADT/mesinkata.h"
#include "work.h"
#include "misc.h"

//IMPLEMENTASI FUNGSI DAN PROSEDUR WORK

//Implementasi fungsi delay
void delay(int seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds);
}

unsigned my_strlen(char *str){
    unsigned len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}

boolean my_strcmp(char *str1, char *str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return FALSE;
        }
        i++;
    }
    return str1[i] == str2[i];
}

void work(int *balance){
    Work workList[] = {
        {"Asisten Praktikum Alstrukdat", 1000, 10},
        {"Penghangat Kursi Labdas", 500, 6},
        {"Teknisi Wifi Eduroam", 700, 8}
    };

    int workCount = sizeof(workList) / sizeof(workList[0]); //jumlah pekerjaan tersedia

    printf("Daftar pekerjaan:\n"); //print daftar pekerjaan yang tersedia
    for(int i = 0; i < workCount; i++){
        printf("%d. %s (pendapatan: %d, durasi: %ds)\n", i+1, workList[i].workName, workList[i].workPayment, workList[i].workDuration);
    }

    boolean validWork = FALSE; //inisialisasi
    Word selectedWork;
    char selectedWorkStr[100];
    int selectedWorkIndex;

    while(!validWork){
        printf("\nPilih nama pekerjaan: ");
        STARTLINE();
        selectedWork = currentWord;
        wordToString(selectedWork, selectedWorkStr);

        for (int i = 0; i < workCount; i++){ //cek apakah pekerjaan yang dipilih valid
            if (my_strcmp(selectedWorkStr, workList[i].workName) == 1){ //jika valid
                validWork = TRUE;
                selectedWorkIndex = i;
                break;
            }
        }
        if (!validWork){ //jika tidak valid, kembali ke loop, input lagi
            printf("Pekerjaan tidak valid, silakan coba lagi. "); 
        }
    }
    
    printf("Anda sedang bekerja sebagai %s. Harap tunggu...\n", selectedWorkStr);
    delay(workList[selectedWorkIndex].workDuration);
    printf("Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n", workList[selectedWorkIndex].workPayment);

    *balance += workList[selectedWorkIndex].workPayment;
}
