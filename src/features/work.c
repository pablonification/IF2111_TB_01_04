#include <stdio.h>
#include <time.h>
#include "../../include/ADT/mesinkata.h"
#include "../../include/features/work.h"
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

//Implementasi fungsi pengumpulan input
void collectInput(char *input){ //input per kata jadiin kalimat
    input[0] = '\0'; //inisialisasi
    Word currentWord;

    while(!EndWord){
        int len = my_strlen(input);

        if(len + currentWord.Length + 1 > 100){ //cek apakah kata yang akan dimasukkan melebihi panjang maksimum
            break;
        }

        for (int i = 0; i < currentWord.Length; i++){
            input[len + i] = currentWord.TabWord[i];
        }
        input[len + currentWord.Length] = ' '; //tambahin spasi tiap akhir kata
        input[len + currentWord.Length + 1] = '\0'; //terminate string
        ADVWORD();
    }
    
    int len = my_strlen(input);
    if(len > 0 && input[len - 1] == ' '){
        input[len - 1] = '\0'; //hapus spasi terakhir
    }
}


void work(int *balance){
    Work workList[] = {
        {"Asisten Praktikum Alstrukdat", 1000, 10},
        {"Penghangat Kursi Labdas", 500, 6},
        {"Teknisi Wifi Eduroam", 700, 8}
    };

    int workCount = sizeof(workList) / sizeof(workList[0]); //jumlah pekerjaan tersedia

    printf(CYAN"Daftar pekerjaan:\n"WHITE); //print daftar pekerjaan yang tersedia
    for(int i = 0; i < workCount; i++){
        printf(CYAN"%d. %s (pendapatan: %d, durasi: %ds)\n"WHITE, i+1, workList[i].workName, workList[i].workPayment, workList[i].workDuration);
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
            if (my_strcmp(selectedWorkStr, workList[i].workName)){ //jika valid
                validWork = TRUE;
                selectedWorkIndex = i;
                break;
            }
        }
        if (!validWork){ //jika tidak valid, kembali ke loop, input lagi
            printf(RED"Pekerjaan tidak valid, silakan coba lagi.\n"WHITE); 
        }
    }
    // printf("%d\n", selectedWorkIndex);
    printf(CYAN"Anda sedang bekerja sebagai %s. Harap tunggu...\n"WHITE, workList[selectedWorkIndex].workName);
    delay(workList[selectedWorkIndex].workDuration);
    printf(GREEN"Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n"WHITE, workList[selectedWorkIndex].workPayment);

    *balance += workList[selectedWorkIndex].workPayment;
}