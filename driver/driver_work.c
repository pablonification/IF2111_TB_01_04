#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/ADT/mesinkata.h"
#include "../include/features/work.h"

void delay(int seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds);
}

void collectInput(char *input){ //input per kata jadiin kalimat
    input[0] = '\0'; //inisialisasi

    while(!EndWord){
        int len = strlen(input);

        if(len + currentWord.Length + 1 > NMax - 1){ //cek apakah kata yang akan dimasukkan melebihi panjang maksimum
            break;
        }

        for (int i = 0; i < currentWord.Length; i++){
            input[len + i] = currentWord.TabWord[i];
        }
        input[len + currentWord.Length] = ' '; //tambahin spasi tiap akhir kata
        input[len + currentWord.Length + 1] = '\0'; //terminate string
        ADVWORD();
    }
    
    int len = strlen(input);
    if(len > 0 && input[len - 1] == ' '){
        input[len - 1] = '\0'; //hapus spasi terakhir
    }
}

void main(int balance){
    Work workList[] = {
        {"Asisten Praktikum Alstrukdat", 1000, 10},
        {"Penghangat Kursi Labdas", 500, 6},
        {"Teknisi Wifi Eduroam", 700, 8}
    };

    int workCount = sizeof(workList) / sizeof(workList[0]);

    printf(">> WORK\nDaftar pekerjaan:\n");
    for(int i = 0; i < workCount; i++){
        printf("%d. %s (pendapatan: %d, durasi: %ds)\n", i+1, workList[i].workName, workList[i].workPayment, workList[i].workDuration);
    }

    boolean validWork = FALSE;
    char selectedWork[100];
    int selectedWorkIndex;

    while(!validWork){
        printf("\nPilih nama pekerjaan: ");
        STARTWORD(); //baca input
        collectInput(selectedWork);

        for (int i = 0; i < workCount; i++){
            if (strcmp(selectedWork, workList[i].workName) == 0){
                validWork = TRUE;
                selectedWorkIndex = i;
                break;
            }
        }
        if (!validWork){
            printf("Pekerjaan tidak valid, silakan coba lagi. ");
        }
    }

    printf("Anda sedang bekerja sebagai %s. Harap tunggu...\n", selectedWork);
    delay(workList[selectedWorkIndex].workDuration);
    printf("Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n", workList[selectedWorkIndex].workPayment);

    balance += workList[selectedWorkIndex].workPayment;
}