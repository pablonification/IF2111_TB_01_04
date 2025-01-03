#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/main.h"
#include "../../include/features/work.h"

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

char pwdstr[MAX_LEN], userstr[MAX_LEN], currentUser[MAX_LEN] = "";


// Fungsi  Main
int main(){
    showMainMenu();
    return 0;
}

boolean endsWith_txt(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    if (len < 4) return FALSE;
    
    return (str[len-4] == '.' && 
            str[len-3] == 't' && 
            str[len-2] == 'x' && 
            str[len-1] == 't');
}

void showMainMenu(){   
    Global gameState = {0};
    gameState.isStarted = FALSE; 
    gameState.isLoaded = FALSE;
    gameState.isLogin = FALSE;
    makeListItem(&gameState);
    CreateEmptyLL(&gameState.users->wishlist.wishlist_item);
    CreateEmptyMap(&gameState.users->cart);
    CreateQueueItem(&gameState.requestQueue); // kalo ada apa apa comment aja

    printf(GREEN"                                                                                           \n"
           "                                                                                           \n"
           "_________   _...._                               __  __   ___                              \n"
           "\\        |.'      '-.                           |  |/  `.'   `.                            \n"
           " \\        .'```'.    '.         .-,.--. .-,.--. |   .-.  .-.   '          .-,.--.      .|  \n"
           "  \\      |       \\     \\        |  .-. ||  .-. ||  |  |  |  |  |    __    |  .-. |   .' |_ \n"
           "   |     |        |    |_    _  | |  | || |  | ||  |  |  |  |  | .:--.'.  | |  | | .'     |\n"
           "   |      \\      /    .| '  / | | |  | || |  | ||  |  |  |  |  |/ |   \\ | | |  | |'--.  .-'\n"
           "   |     |\\`'-.-'   .'.' | .' | | |  '- | |  '- |  |  |  |  |  |`\" __ | | | |  '-    |  |  \n"
           "   |     | '-....-'`  /  | /  | | |     | |     |__|  |__|  |__| .'.''| | | |        |  |  \n"
           "  .'     '.          |   `'.  | | |     | |                     / /   | |_| |        |  '.'\n"
           "'-----------'        '   .'|  '/|_|     |_|                     \\ \\._,\\ '/|_|        |   / \n"
           "                      `-'  `--'                                  `--'  \"            `'-'   \n");

    printf(YELLOW"Selamat datang di PURRMART!\nTolong masukkan command yang valid (START, LOAD, REGISTER, LOGIN, HELP, atau QUIT.)\n"WHITE);

    while (1) {
        printf(">> ");
        STARTWORD2("", "");

        // Add validation for empty input
        if (currentWord.Length == 0) {
            printf(RED"Command tidak boleh kosong. Silakan coba lagi.\n"WHITE);
            continue;
        }

        if (compareWords("START", currentWord, 5)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda harus load file konfigurasi terlebih dahulu.\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                Start(&gameState);
            } else if (gameState.isStarted){
                printf(RED"Program sudah dimulai. Silahkan logout terlebih dahulu.\n"WHITE);
            }
        } 
        else if (compareWords("LOAD", currentWord, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                Word filenameWord;
                ADVWORD();
                filenameWord = currentWord;

                char filename[MAX_LEN] = {0};

                if (filenameWord.Length > 0) {
                    for (int i = 0; i < filenameWord.Length; i++) {
                        filename[i] = filenameWord.TabWord[i];
                    }
                    filename[filenameWord.Length] = '\0';
            
                    printf(CYAN"Loading file: %s\n"WHITE, filename);
                    Load(filename, &gameState);
                } else {
                    printf(RED"Error: Filename tidak diberikan.\n"WHITE);
                }
            } else if  (!gameState.isStarted && gameState.isLoaded){
                printf(RED"Program belum di-Start. Silahkan START terlebih dahulu.\n"WHITE);
            } else if (gameState.isStarted && gameState.isLoaded){
                printf(RED"Game sudah dimulai. Tidak bisa load file konfigurasi.\n"WHITE);
            }
        }
        else if (compareWords("HELP", currentWord, 4)){
            if (!gameState.isLoaded && !gameState.isStarted && !gameState.isLogin){
            printf("=====[ Welcome Menu Help PURRMART]=====\n");
            printf(YELLOW"\t1. START\t\t-> Untuk masuk sesi baru\n");
            printf("\t2. LOAD\t\t\t-> Untuk memulai sesi berdasarkan file konfigurasi\n");
            printf("\t3. QUIT\t\t\t-> Untuk keluar dari program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){ 
            printf("=====[ Login Menu Help PURRMART ]=====\n");
            printf(YELLOW"\t1. REGISTER\t\t-> Untuk melakukan pendaftaran akun baru\n");
            printf("\t2. LOGIN\t\t-> Untuk masuk ke dalam akun dan memulai sesi\n");
            printf("\t3. QUIT\t\t\t-> Untuk keluar dari program\n"WHITE);   
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){ 
            printf(YELLOW"=====[ Menu Help PURRMART ]=====\n");
            printf("\t1. WORK\t\t\t\t-> Untuk bekerja\n");
            printf("\t2. WORK CHALLENGE\t\t-> Untuk mengerjakan challenge\n");
            printf("\t3. STORE LIST\t\t\t-> Untuk melihat barang-barang di toko\n");
            printf("\t4. STORE REQUEST\t\t-> Untuk meminta penambahan barang\n");
            printf("\t5. STORE SUPPLY\t\t\t-> Untuk menambahkan barang dari permintaan\n");
            printf("\t6. STORE REMOVE\t\t\t-> Untuk menghapus barang\n");
            printf("\t7. STORE REQUEST BIOWEAPON\t-> Untuk memproses DNA menjadi bioweapon\n");
            printf("\t8. WISHLIST SHOW\t\t-> Untuk melihat wishlist\n");
            printf("\t9. WISHLIST ADD\t\t\t-> Untuk menambahkan barang ke wishlist\n");
            printf("\t10. WISHLIST REMOVE\t\t-> Untuk menghapus barang dari wishlist\n");
            printf("\t11. WISHLIST CLEAR\t\t-> Untuk menghapus seluruh barang dari wishlist\n");
            printf("\t12. WISHLIST SWAP\t\t-> Untuk menukar posisi dua barang dalam wishlist\n");
            printf("\t13. CART SHOW\t\t\t-> Untuk melihat isi keranjang\n");
            printf("\t14. CART ADD\t\t\t-> Untuk menambahkan barang ke keranjang\n");
            printf("\t15. CART REMOVE\t\t\t-> Untuk menghapus barang dari keranjang\n");
            printf("\t16. CART PAY\t\t\t-> Untuk membayar barang di keranjang\n");
            printf("\t17. GLOBALALIGNMENT\t\t-> Untuk melakukan deteksi kebocoran DNA\n");
            printf("\t18. OPTIMASIRUTE\t\t-> Untuk melakukan optimasi rute ekspedisi\n");
            printf("\t19. PROFILE\t\t\t-> Untuk melihat profil\n");
            printf("\t20. LOGOUT\t\t\t-> Untuk keluar dari sesi\n");
            printf("\t21. SAVE\t\t\t-> Untuk menyimpan state ke dalam file\n");
            printf("\t22. QUIT\t\t\t-> Untuk keluar dari program\n"WHITE);
            }
        }
        else if (compareWords("LOGIN", currentWord, 5)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){
                printf(RED"Anda masih tercatat sebagai %s. Silahkan LOGOUT terlebih dahulu.\n"WHITE, currentUser);
            } else {

                Login(&gameState, gameState.users, gameState.userCount);

            }
        }
        else if (compareWords("LOGOUT", currentWord, 6)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Anda belum login. Silakan login terlebih dahulu\n"WHITE);
            } else {
                Logout(&gameState.users[gameState.userIndex], gameState.userCount);
                gameState.isLogin = FALSE;
            }
        }
        else if (compareWords("REGISTER", currentWord, 8)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){
                printf(RED"Anda sudah login. Silahkan LOGOUT terlebih dahulu.\n"WHITE);
            } else {
                Register(&gameState);
            }
        }
        else if (compareWords("PROFILE", currentWord, 7)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } else {
                profile(&gameState.users[gameState.userIndex]);
            }
        }
        else if (compareWords("HISTORY", currentWord, 7)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } else {
                ADVWORD();
                if (!isWordInt(currentWord)){
                    history(&gameState.users[gameState.userIndex].history);
                } else {
                    int input = WordToInt(currentWord);
                    historyInt(&gameState.users[gameState.userIndex].history, &input);
                }
                
            }
        }

        // WORK
        else if (IsEqual("WORK", currentWord)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } else {
                ADVWORD();
                if (IsEqual("CHALLENGE", currentWord)){
                    printf(CYAN"Daftar challenge yang tersedia:\n");
                    printf("1. Tebak Angka (biaya main=200)\n");
                    printf("2. W0RDL399 (biaya main=500)\n");
                    printf("3. QUANTUM W0RDL399 (biaya main=1000)\n"WHITE);

                    printf("Masukan challenge yang hendak dimainkan (nomor challenge): ");
                    Word choice;
                    STARTLINE();
                    choice = currentWord;
                    
                    // cek input nomor atau bukan
                    if (!isKataInt(choice)){
                        printf(RED"Input harus berupa angka!\n"WHITE);
                    } 

                    if (compareWords("1", choice, 1)){
                        tebakAngkaRNG(&gameState.users[gameState.userIndex].money);
                    }
                    else if (compareWords("2", choice, 1)){
                        playWordl3(&gameState.users[gameState.userIndex].money);
                    }
                    else if (compareWords("3", choice, 1)){
                        playQuantumWordl3(&gameState.users[gameState.userIndex].money);
                    } else {
                        printf(RED"Nomor challenge tidak valid. Silakan coba lagi.\n"WHITE);
                    }
                } else {
                    work(&gameState.users[gameState.userIndex].money);
                } 
            }
        }
    
        // STORE
        else if (IsEqual("STORE", currentWord)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } else {
                ADVWORD();
                if (IsEqual("SUPPLY", currentWord)){
                    storeSupply(&gameState.itemList, &gameState.requestQueue);
                }
                else if (IsEqual("REMOVE", currentWord)){
                    storeRemove(&gameState.itemList);
                }
                else if (IsEqual("LIST", currentWord)){
                    storeList(&gameState.itemList);
                }
                else if (IsEqual("REQUEST", currentWord)){
                    ADVWORD();
                    if (IsEqual("BIOWEAPON", currentWord)){
                        processDNA();
                    }
                    else {
                        storeRequest(&gameState.itemList, &gameState.requestQueue);
                    }
                } else {
                    printf(RED"Command tidak valid. Silakan coba lagi.\n"WHITE);
                }
            }
        }

        // WISHLIST
        else if (IsEqual("WISHLIST", currentWord)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            }
            else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            }
            else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            }
            else {
                ADVWORD();
                if (IsEqual("CLEAR", currentWord)){
                    wishlistClear(&gameState.users[gameState.userIndex].wishlist);
                }
                else if (IsEqual("SHOW", currentWord)){
                    wishlistShow(&gameState.users[gameState.userIndex].wishlist);
                }
                else if (IsEqual("ADD", currentWord)){
                    wishlistAdd(&gameState.itemList, &gameState.users[gameState.userIndex].wishlist);
                }
                else if (IsEqual("REMOVE", currentWord)){
                    wishlistRemove(&gameState.users[gameState.userIndex].wishlist);
                }
                else if (IsEqual("SWAP", currentWord)){
                    int i, j;
                    Word wordI, wordJ;
                    ADVWORD();

                    wordI = currentWord;
                    i = WordToInt(wordI);

                    ADVWORD();
                    wordJ = currentWord;
                    j = WordToInt(wordJ);

                    // printf("DEBUG: Calling wishlistSwap with i=%d, j=%d\n", i, j); // Debug statement

                    if (i > 0 && j > 0) {
                        wishlistSwap(&gameState.users[gameState.userIndex].wishlist, i, j);
                    } else {
                        printf(RED"Nomor urut tidak valid. Silakan coba lagi.\n"WHITE);
                    }
                } else {
                    printf(RED"Command tidak valid. Silakan coba lagi.\n"WHITE);
                }
            }
      
        }
        else if (compareWords("GLOBALALIGNMENT", currentWord, currentWord.Length)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } 
            else {
                GlobalAlignment();
            }
        }
        else if (compareWords("OPTIMASIRUTE", currentWord, currentWord.Length)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } 
            else {
                OptimasiRute();
            }
        }
 
        // CART
        else if (compareWords("CART", currentWord, currentWord.Length)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                ADVWORD();
                if (IsEqual("SHOW", currentWord)){
                    cartShow(&gameState, &gameState.users[gameState.userIndex], gameState.itemList);
                } else if (IsEqual("PAY", currentWord)){
                    cartPay(&gameState ,&gameState.users[gameState.userIndex], gameState.itemList);
                } else if (IsEqual("ADD", currentWord)){
                    Word itemCart, tempQty;
                    char itemStr[MAX_LEN];

                    readItemWithBlanks(&itemCart, &tempQty, "CART ADD");

                    //itemCart = currentWord;
                    if (isWordEmpty(itemCart)){
                        printf(RED"Masukan Tidak valid, format masukan adalah CART ADD <Nama Barang> <Jumlah Barang>\n"WHITE);
                        continue;
                    }
                    wordToString(itemCart, itemStr);

                    if (!isWordInt(tempQty)){
                        printf(RED"Masukan Tidak valid, format masukan adalah CART ADD <Nama Barang> <Jumlah Barang>\n"WHITE);
                        continue;
                    }

                    // printf("DEBUG: itemCart = %s\n", itemCart.TabWord);
                    // printf("DEBUG: tempQty = %s\n", tempQty.TabWord);

                    int Qty = WordToInt(tempQty);
                    cartAdd(&gameState, &gameState.users[gameState.userIndex], &gameState.itemList, itemStr, &Qty);

                } else if (IsEqual("REMOVE", currentWord)){
                    Word itemCart, tempQty;
                    char itemStr[MAX_LEN];

                    readItemWithBlanks(&itemCart, &tempQty, "CART REMOVE");

                    if (isWordEmpty(itemCart)){
                        printf(RED"Masukan Tidak valid, format masukan adalah CART REMOVE <Nama Barang> <Jumlah Barang>\n"WHITE);
                        continue;
                    }
                    wordToString(itemCart, itemStr);

                    if (!isWordInt(tempQty)){
                        printf(RED"Masukan Tidak valid, format masukan adalah CART REMOVE <Nama Barang> <Jumlah Barang>\n"WHITE);
                        continue;
                    }
                    int Qty = WordToInt(tempQty);

                    cartRemove(&gameState, &gameState.users[gameState.userIndex], itemStr, &Qty);
                } else {
                    printf(RED"Command tidak valid. Silakan coba lagi.\n"WHITE);
                }
            }
        }


        else if (compareWords("SAVE", currentWord, 4)) {
            if (!gameState.isLoaded && !gameState.isStarted) {
                printf(RED"Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n"WHITE);
            } else if (gameState.isLoaded && !gameState.isStarted) {
                printf(RED"Anda belum start program\n"WHITE);
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin) {
                printf(RED"Lakukan login atau register terlebih dahulu\n"WHITE);
            } else {
                ADVWORD(); // Read the filename
                if (currentWord.Length == 0 || compareWords("SAVE", currentWord, 4)) {
                    printf(RED"Nama file tidak diberikan. Silakan coba lagi.\n"WHITE);
                } else {
                    char filename[MaxEl];
                    wordToString(currentWord, filename);
                    
                    if (!endsWith_txt(filename)) {
                        printf(RED"Nama file harus berakhiran .txt\n"WHITE);
                    } else {
                        Save(filename, &gameState);
                        printf(GREEN"Game berhasil disimpan dalam data/%s.\n"WHITE, filename);
                    }
                }
            }
        }

        else if (compareWords("QUIT", currentWord, 4)){
            if (!gameState.isLogin) {
                printf("\nKamu keluar dari PURRMART.\n");
                printf("Dadah ^_^/\n");
                break;
            } else {
                boolean validResponse = FALSE;
                while (!validResponse) {
                    printf("\nApakah kamu ingin menyimpan data sesi sekarang (Y/N)? ");
                    STARTLINE();
                    if (currentWord.Length == 0) {
                        printf(RED"Input tidak boleh kosong. Silakan masukkan Y/N.\n"WHITE);
                        continue;
                    }
                    
                    char response = currentWord.TabWord[0];
                    if (response == 'Y' || response == 'y') {
                        printf("Masukkan nama file penyimpanan: ");
                        STARTLINE();
                        if (currentWord.Length == 0) {
                            printf(RED"Tolong masukkan nama file yang benar.\n"WHITE);
                            continue;
                        } else {
                            char filename[MaxEl];
                            wordToString(currentWord, filename);
                            if (!endsWith_txt(filename)) {
                                printf(RED"Nama file harus berakhiran .txt\n"WHITE);
                                continue;
                            }
                            Save(filename, &gameState);
                            printf(GREEN"Game berhasil disimpan dalam data/%s.\n"WHITE, filename);
                        }
                        validResponse = TRUE;
                    } else if (response == 'N' || response == 'n') {
                        validResponse = TRUE;
                    } else {
                        printf(RED"Input tidak valid. Silakan masukkan Y/N.\n"WHITE);
                    }
                }
                
                printf("\nKamu keluar dari PURRMART.\n");
                printf("Dadah ^_^/\n");
                break;
            }
        }
        else {
            printf(RED"Command tidak valid. Silakan coba command yang valid.\n"WHITE);
        }
    }
}

int CharToInt(Word tempQty){
    int res = 0;
    for (int i = 0; i < tempQty.Length; i++){
        res = res * 10 + (tempQty.TabWord[i] - '0');
    }
    return res;
}

void Start(Global *gameState) {
    gameState->isStarted = TRUE;
    printf(GREEN"File konfigurasi aplikasi berhasil dibaca. PURRMART berhasil dijalankan.\n"WHITE);
}

// Implement other functions as in your original code...

void Load(const char *filename, Global *global) {
    if (filename == NULL || *filename == '\0') {
        printf(RED"Nama file tidak valid.\n"WHITE);
        return;
    }

    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = openFile(filepath, "r");
    if (file == NULL) {
        printf(RED"Save file tidak ditemukan. PURRMART gagal dijalankan.\n"WHITE);
        return;
    }

    makeListItem(global);

    // Item di Store
    int itemCount;
    boolean succread_item = FALSE;
    if (readFile(file, "%d", &itemCount) != 1) {
        printf(RED"Kesalahan format file: jumlah item tidak valid.\n"WHITE);
        closeFile(file);
        return;
    }
    // printf(CYAN"DEBUG: Reading %d items\n"WHITE, itemCount);

    for (int i = 0; i < itemCount; i++) {
        int price;
        char name[MAX_LEN];
        
        if (readItem(file, "%d %[^\n]", &price, name) != 2) {
            printf(RED"Kesalahan format file: data item tidak valid.\n"WHITE);
            closeFile(file);
            return;
        }
        // printf(CYAN"DEBUG: Read item %d: %s (price: %d)\n"WHITE, i+1, name, price);

        global->itemList.item[i].price = price;
        customStringCPY(global->itemList.item[i].name, name);
        global->itemList.itemLength++;
        succread_item = TRUE;
    }

    // Jumlah User
    int userCount;
    boolean succread_user = FALSE;
    boolean succread_ph = FALSE;
    boolean succread_wl = FALSE;
    if (readFile(file, "%d", &userCount) != 1) {
        printf(RED"Kesalahan format file: jumlah user tidak valid.\n"WHITE);
        closeFile(file);
        return;
    }
    // printf(CYAN"DEBUG: Reading %d users\n"WHITE, userCount);

    for (int i = 0; i < userCount; i++) {
        int money;
        char username[MAX_LEN], password[MAX_LEN];

        if (readUser(file, "%d %s %s", &money, username, password) != 3) {
            printf(RED"Kesalahan format file: data user tidak valid.\n"WHITE);
            closeFile(file);
            return;
        }
        // printf(CYAN"DEBUG: Read user %d: %s (money: %d)\n"WHITE, i+1, username, money);

        global->users[i].money = money;
        customStringCPY(global->users[i].name, username);
        customStringCPY(global->users[i].password, password);
        global->userCount++;
        global->users[i].history.TOP = -1;
        succread_user = TRUE; 

        // Load purchase history
        int historyCount;
        if (readFile(file, "%d", &historyCount) != 1) {
            printf(RED"Kesalahan format file: jumlah riwayat pembelian tidak valid.\n"WHITE);
            closeFile(file);
            return;
        }
        // printf(CYAN"DEBUG: Reading %d purchase history\n"WHITE, historyCount);

        succread_ph = TRUE;
        for (int j = 0; j < historyCount; j++) {
            infotypeStack item;
            int cost;
            char itemName[MAX_LEN];
            if (readItem(file, "%d %[^\n]", &cost, itemName) != 2) {
                printf(RED"Kesalahan format file: data riwayat pembelian tidak valid.\n"WHITE);
                closeFile(file);
                return;
            }
            item.harga = cost;
            customStringCPY(item.name, itemName);
            Push(&global->users[i].history, item);
        }
        // printf(CYAN"\nDEBUG: Purchase History for user %s:\n"WHITE, global->users[i].name);
        // printStack(&global->users[i].history);

        // Load wishlist
        int wishlistCount;
        if (readFile(file, "%d", &wishlistCount) != 1) {
            printf(RED"Kesalahan format file: jumlah wishlist tidak valid.\n"WHITE);
            closeFile(file);
            return;
        }
        // printf(CYAN"DEBUG: Reading %d wishlist\n"WHITE, wishlistCount);

        succread_wl = TRUE;
        global->users[i].wishlist.wishlist_item.First = NULL; 
        for (int j = 0; j < wishlistCount; j++) {
            char wishItem[MAX_LEN];
            if (readItem2(file, " %49[^\n]", wishItem) != 1) {
                printf(RED"Kesalahan format file: data wishlist tidak valid.\n"WHITE);
                closeFile(file);
                return;
            }
            global->users[i].wishlist.number = wishlistCount;
            InsertFirstLL(&global->users[i].wishlist.wishlist_item, wishItem);
            // printf(CYAN"DEBUG: Read wishlist %d: %s\n"WHITE, j+1, global->users[i].wishlist.wishlist_item.First->info);
        }
    }

    if (succread_item && succread_user && succread_ph && succread_wl) {
        global->isLoaded = TRUE;
        printf(GREEN"Save file berhasil dibaca. PURRMART berhasil dijalankan..\n"WHITE);
    } else {
        printf(RED"Save file tidak ditemukan. PURRMART gagal dijalankan.\n"WHITE);
    }
    closeFile(file);
}

int findUser(User *users, int user_count, const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (customStringCMP(users[i].name, username) == 0 && 
            customStringCMP(users[i].password, password) == 0) { 
            return i;
        }
    }
    return -1;
}

void disableEcho() {
    printf("\033[8m"); // ANSI escape code to disable echo
}

void enableEcho() {
    printf("\033[28m"); // ANSI escape code to enable echo
}

void Login(Global *gameState, User *users, int user_count) {
    Word username,password;
    
    printf("Username: ");
    STARTLINE();
    username = currentWord;
    wordToString(username, userstr);

    if (isWordEmpty(username)) {
        printf(RED"Username tidak boleh kosong.\n"WHITE);
        return;
    }

    printf("Password: ");
    disableEcho(); // kalo gamau tinggal di comment dan apus aja ges
    STARTLINE();
    enableEcho(); // kalo gamau tinggal di comment dan apus aja ges
    password = currentWord;
    wordToString(password, pwdstr);
    printf("\n"); // Move to the next line

    if (isWordEmpty(password)) {
        printf(RED"Password tidak boleh kosong.\n"WHITE);
        return;
    }

    int userIndex = findUser(users, user_count, userstr, pwdstr);
    
    if (userIndex != -1) {
        customStringCPY(currentUser, users[userIndex].name);
        printf(GREEN"Anda telah login ke PURRMART sebagai %s.\n"WHITE, currentUser);
        users[userIndex].money = users[userIndex].money;
        printf(GREEN"Saldo anda: %d\n"WHITE, users[userIndex].money);
        gameState->isLogin = TRUE;
        gameState->userIndex = userIndex;
    }
    else {
        printf(RED"Username atau password salah.\n"WHITE);
    }
}

void Logout(User *users, int user_count) {
    printf(YELLOW"%s telah logout dari sistem PURRMART. Silakan REGISTER/LOGIN kembali untuk melanjutkan.\n"WHITE, currentUser);
    currentUser[0] = '\0';  // Clear the currentUser string
}

void Register(Global *gameState) {
    if (!gameState->isLoaded && !gameState->isStarted) {
        printf(RED"Game belum dimulai. Silakan load dan start terlebih dahulu\n"WHITE);
        return;
    }

    Word username, password;
    
    printf("Username: ");
    STARTLINE();
    username = currentWord;
    wordToString(username, userstr);

    if (isWordEmpty(username)) {
        printf(RED"Username tidak boleh kosong.\n"WHITE);
        return;
    }
    
    printf("Password: ");
    disableEcho(); // kalo gamau tinggal di comment dan apus aja ges
    STARTLINE();
    enableEcho(); // kalo gamau tinggal di comment dan apus aja ges
    password = currentWord;
    wordToString(password, pwdstr);

    if (isWordEmpty(password)) {
        printf(RED"Password tidak boleh kosong.\n"WHITE);
        return;
    }
    
    if (gameState->userCount >= MAX_USERS) {
        printf(RED"Maksimum jumlah pengguna telah tercapai.\n"WHITE);
        return;
    }
    
    for (int i = 0; i < gameState->userCount; i++) {
        if (compareWords(gameState->users[i].name, username, username.Length)) {
            printf(RED"Akun dengan username %s gagal dibuat. Silakan lakukan REGISTER ulang.\n"WHITE, userstr);
            return;
        }
    }

    customStringCPY(gameState->users[gameState->userCount].name, userstr);
    customStringCPY(gameState->users[gameState->userCount].password, pwdstr);
    gameState->users[gameState->userCount].money = 0;
    gameState->users[gameState->userCount].history.TOP = -1;
    gameState->users[gameState->userCount].wishlist.wishlist_item.First = NULL;
    gameState->userCount++;

    printf(GREEN"Akun dengan username %s telah berhasil dibuat.\n"WHITE, userstr);
    printf(YELLOW"Silakan LOGIN untuk melanjutkan.\n"WHITE);
}

void Save(const char *filename, Global *gameState) {
    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = openFile(filepath, "w");
    if (file == NULL) {
        printf(RED"Gagal membuat file save.\n"WHITE);
        return;
    }

    // Save items in store
    writeLen(file, "%d\n", gameState->itemList.itemLength);
    for (int i = 0; i < gameState->itemList.itemLength; i++) {
        writeItem(file, "%d %s\n", 
            gameState->itemList.item[i].price,
            gameState->itemList.item[i].name);
    }

    // Save users count
    writeLen(file, "%d\n", gameState->userCount);

    // For each user, save their data including history and wishlist
    for (int i = 0; i < gameState->userCount; i++) {
        // Save user basic info
        writeUser(file, "%d %s %s\n",
            gameState->users[i].money,
            gameState->users[i].name,
            gameState->users[i].password);

        // Save purchase history
        Stack *history = &gameState->users[i].history;
        int historyCount = history->TOP + 1;
        writeLen(file, "%d\n", historyCount);
        
        // Write history items from bottom to top to maintain order when loading
        for (int j = 0; j < historyCount; j++) {
            writeItem(file, "%d %s\n",
                history->T[j].harga,
                history->T[j].name);
        }

        // Save wishlist
        ListLinier *wishlist = &gameState->users[i].wishlist.wishlist_item;
        int wishlistCount = NbElmt(*wishlist);
        writeLen(file, "%d\n", wishlistCount);

        // Write wishlist items
        addressLL curr = wishlist->First;
        while (curr != Nil) {
            fprintf(file, "%s\n", curr->info);
            curr = curr->next;
        }
    }

    closeFile(file);
    // printf(GREEN"Game berhasil disimpan dalam %s.\n"WHITE, filepath);
}

void profile(User *users) {
    // Find the current user's index
    int userIndex = -1;
    for (int i = 0; i < MAX_USERS; i++) {
        if (customStringCMP(users[i].name, currentUser) == 0) {
            userIndex = i;
            break;
        }
    }
    if (userIndex != -1) {
        User* currentUserData = &users[userIndex];
        printf(CYAN"Username: %s\n"WHITE, currentUserData->name);
        printf(CYAN"Money: %d\n"WHITE, currentUserData->money);
        printf(CYAN"Wishlist:\n"WHITE);
        displayListLinier(users[userIndex].wishlist.wishlist_item);
    }
}

int customStringCMP(const char *str1, const char *str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void customStringCPY(char *dest, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// void insertLastItem(ListItem *itemlist, Item item){
//     if (itemlist->itemLength < MaxEl) {
//         itemlist->item[itemlist->itemLength] = item;
//         itemlist->itemLength++;
//     } else {
//         printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
//     }
// }

void makeListItem(Global *gameState) {
    for (int i = 0; i < MaxEl; i++) {
        gameState->itemList.item[i].price = 0;
        gameState->itemList.item[i].name[0] = '\0';
    }
    
    gameState->userCount = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        gameState->users[i].money = 0;
        gameState->users[i].name[0] = '\0';
        gameState->users[i].password[0] = '\0';
    }
}

/* buat ngetes hasil load-an tadi*/
void printStack(Stack *S) {
    // printf(CYAN"\nDEBUG: Printing Stack Contents:\n"WHITE);
    if (IsEmptyStack(*S)) {
        printf(RED"Stack is empty\n"WHITE);
        return;
    }
    
    for (int i = S->TOP; i >= 0; i--) {
        printf(CYAN"Stack[%d]: %s (cost: %d)\n"WHITE, 
               S->TOP - i + 1, 
               S->T[i].name, 
               S->T[i].harga);
    }
    printf(CYAN"Total items in stack: %d\n"WHITE, S->TOP + 1);
}

// store

void storeList (ListItem *L) {
    if (IsEmptyItem(L)) {
        printf(RED"TOKO KOSONG\n"WHITE);
    }
    else { 
        printf(CYAN"List barang yang ada di toko: \n"WHITE);
        for (int i  = 0; i < L->itemLength; i ++) {
            printf("");
            printf(CYAN"%d. %s - Harga: %d\n"WHITE, i + 1, L->item[i].name, L-> item[i].price);
        }
    // }   
    printf("\n");
    // }
    }
}
  // int itemCount = sizeof(itemList) / sizeof(itemList[0]);
  
void storeRequest(ListItem *L, QueueItem *Q) {
    Word req;
    char reqstr[MaxEl]; // Ensure sufficient size
    boolean found = FALSE;

    printf("Nama barang yang diminta: ");
    STARTLINE();
    req = currentWord;

    if (isWordEmpty(req)) {
        printf(RED"Nama barang tidak boleh kosong.\n"WHITE);
        storeRequest(L, Q);
    }

    wordToString(req, reqstr); // Convert Word to string

    boolean isFoundInList = SearchItem(*L, reqstr);
    if (isFoundInList) {
        printf(RED"Barang dengan nama yang sama sudah ada di toko\n"WHITE);
    } else if (isEmptyItem(*Q)) {
        enqueueItem(Q, reqstr);
    } else {
        boolean foundInQueue = FALSE;
        int queueLength = lengthQueueItem(*Q);

        for (int i = 0; i < queueLength; i++) {
            char temp[MaxEl];
            dequeueItem(Q, temp); // Dequeue an item to temp
            if (customStringCMP(temp, reqstr) == 0) {
                foundInQueue = TRUE;
            }
            enqueueItem(Q, temp); // Re-enqueue the item
        }

        if (foundInQueue) {
            printf(RED"Barang dengan nama yang sama sudah ada di antrian\n"WHITE);
        } else {
            enqueueItem(Q, reqstr);
        }
    }
}

void storeRemove(ListItem *L) {
    Word item_name;
    printf("Nama barang yang akan dihapus: ");
    STARTLINE();
    item_name = currentWord;

    if (isWordEmpty(item_name)) {
        printf(RED"Nama barang tidak boleh kosong.\n"WHITE);
        storeRemove(L);
    }
    
    char item_namestr[50];
    wordToString(item_name, item_namestr);

    
    boolean found = 0;
    int i = 0;

    while (i < L->itemLength && !found) {
        if (customStringCMP(item_namestr, (*L).item[i].name) == 0) {
            found = 1;
        }
        i++;
    }

    if (found) {
        DeleteAtItem(L, i-1);
        printf(GREEN"%s telah berhasil dihapus.\n"WHITE, item_namestr);
    }
    else {
        printf(RED"Toko tidak menjual %s.\n"WHITE, item_namestr);
    }
}

void storeSupply(ListItem *L, QueueItem *Q) { 
    if (!isEmptyItem(*Q)) {
        char item_name[50];
        dequeueItem(Q, item_name); // Dequeue the item first
        printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak): ", item_name);
        
        Word response;
        STARTLINE();
        response = currentWord;
        char responsestr[50];
        wordToString(response, responsestr);
        boolean inputValid = FALSE;

        while (!inputValid) {
            if (customStringCMP(responsestr, "Terima") == 0 || customStringCMP(responsestr, "Tunda") == 0 || customStringCMP(responsestr, "Tolak") == 0) {
                inputValid = TRUE;
            } else {
                printf("Input tidak valid. Silakan coba lagi: ");
                STARTLINE();
                response = currentWord;
                wordToString(response, responsestr);
            }
        }

        if (customStringCMP(responsestr, "Terima") == 0) {
            Word price;
            printf("Harga barang: ");
            STARTLINE();
            price = currentWord;
            int priceint = WordToInt(price);
            boolean validprice = FALSE;

            while (!validprice) {
                if (priceint > 0) {
                    validprice = TRUE;
                } else {
                    printf("Harga tidak valid. Silakan coba lagi: ");
                    STARTLINE();
                    price = currentWord;
                }
            }

            Item new_item;
            customStringCPY(new_item.name, item_name);
            new_item.price = priceint;

            insertLastItem(L, new_item);
            printf(GREEN"%s dengan harga %d telah ditambahkan ke toko.\n"WHITE, item_name, priceint);
        } else if (customStringCMP(responsestr, "Tunda") == 0) {
            enqueueItem(Q, item_name);
            printf(YELLOW"%s dikembalikan ke antrian.\n"WHITE, item_name);
        } else if (customStringCMP(responsestr, "Tolak") == 0) {
            printf(RED"%s dihapuskan dari antrian.\n"WHITE, item_name);
        }
    } else {
        printf(RED"Antrian kosong. Tidak ada barang yang perlu disupply.\n"WHITE);
    }
}

boolean IsEmptyItem(ListItem *L) {
    return L->itemLength == 0;
}

void DeleteAtItem(ListItem *L, IdxType i) {
	int j = LastIdxItem(*L);
	while (i < j) {
		(*L).item[i] = (*L).item[i+1];
        i++;
	}
    (*L).itemLength -= 1;
}

IdxType LastIdxItem(ListItem L) {
	int i = 0;
	while ((i < MaxEl) && (L.item[i+1].name[0] != '\0'))  {
		i += 1;
	}
	return i;
}

boolean SearchItem(ListItem L, char *X) {
	int i = 0;
    
	int j = L.itemLength;
	boolean found = FALSE;
	while ((i < L.itemLength) && !found) {
		if (customStringCMP(L.item[i].name, X) == 0) {
			found = TRUE;
            // i++;
		}
		i += 1;
	}
    return found;
}

void CreateQueueItem(QueueItem *q) {
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}

boolean isEmptyItem(QueueItem q){
    return (IDX_HEAD(q) == IDX_UNDEF) && (IDX_TAIL(q) == IDX_UNDEF);
}

int lengthQueueItem(QueueItem q) {
    if (isEmptyItem(q)) {
        return 0;
    } else {
        return (IDX_TAIL(q) - IDX_HEAD(q) + 100) % 100 + 1;
    }
}

void enqueueItem(QueueItem *q, char *item_name) {
    if (q->idxTail == (q->idxHead - 1 + CAPACITY) % CAPACITY) {
        printf("Queue is full! Cannot add new item.\n");
        return;
    }

    if (isEmptyItem(*q)) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
    } else {
        IDX_TAIL(*q) = (IDX_TAIL(*q) + 1) % CAPACITY;
    }
    int i = 0;
    while (item_name[i] != '\0' && i < 100 - 1) {
        q->item_name[q->idxTail][i] = item_name[i];
        i++;
    }
    q->item_name[q->idxTail][i] = '\0';
}

void dequeueItem(QueueItem *q, char *item_name) {   
    customStringCPY(item_name, (q)->item_name[(q)->idxHead]);
    if (lengthQueueItem(*q) == 1) {
        CreateQueueItem(q);
    } else {
        IDX_HEAD(*q) = (IDX_HEAD(*q) + 1) % CAPACITY;
    }
}

boolean isWordInt(Word w) {
    int i = 0;
    for (i = 0; i < w.Length; i++) {
        if (w.TabWord[i] < '0' || w.TabWord[i] > '9') {
            return FALSE;
        }
    }
    return TRUE;
}

// Kode wishlist
// Fitur wishlistShow
// Menampilkan isi wishlist pengguna
void wishlistShow(WishlistUser *wishlist) {
    if (!IsEmptyLL(wishlist->wishlist_item)) {
        printf(CYAN"Berikut adalah isi wishlist-mu:\n"WHITE);
        addressLL P = wishlist->wishlist_item.First;
        int idx = 1;
        while (P != Nil) {
            printf("%d %s\n", idx++, P->info);
            P = P->next;
        }
    } else {
        printf(YELLOW"Wishlist kamu kosong!\n"WHITE);
    }
}

// Fitur wishlistAdd
// Menambahkan barang ke wishlist jika barang ada di store dan belum ada di wishlist
void wishlistAdd(ListItem *L, WishlistUser *wishlist) {
    Word item_name;
    printf("Masukkan nama barang: ");
    STARTLINE();
    item_name = currentWord;

    if (isWordEmpty(item_name)) {
        printf(RED"Nama barang tidak boleh kosong.\n"WHITE);
        wishlistAdd(L, wishlist); // Minta input ulang
    }

    char item_namestr[MaxEl];
    wordToString(item_name, item_namestr); 

    // Cek apakah barang ada di store
    boolean isFoundInList = SearchItem(*L, item_namestr);
    if (isFoundInList) {
        // Cek apakah barang sudah ada di wishlist
        if (isMemberLL(wishlist->wishlist_item, item_namestr)) {
            printf(RED"%s sudah ada di wishlist\n"WHITE, item_namestr);
            wishlistAdd(L, wishlist); // Minta input ulang
        } else {
            InsertLastLL(&wishlist->wishlist_item, item_namestr);
            wishlist->number++;
            printf(GREEN"Berhasil menambahkan %s ke wishlist!\n"WHITE, item_namestr);
        }
    } else {
        printf(RED"Tidak ada barang dengan nama %s!\n"WHITE, item_namestr);
        wishlistAdd(L, wishlist); // Minta input ulang
    }
}

// Fitur wishlistClear
// Menghapus semua barang di wishlist
void wishlistClear(WishlistUser *wishlist) {
    if (IsEmptyLL(wishlist->wishlist_item)) {
        printf(YELLOW"Wishlist sudah kosong.\n"WHITE);
    } else {
        ClearLL(&wishlist->wishlist_item);
        printf(GREEN"Wishlist telah dikosongkan.\n"WHITE);
    }
}

// Fitur wishlistRemove
// Menghapus barang dari wishlist berdasarkan nama atau nomor urut
boolean isNumber(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

void wishlistRemove(WishlistUser *wishlist) {
    if (wishlist->number == 0) {
        printf(RED"Penghapusan barang WISHLIST gagal dilakukan, WISHLIST kosong!\n"WHITE);
        return;
    }
    int idx;
    Word input;
    ADVWORD(); // baca "REMOVE"
    ADVWORD(); // baca input selanjutnya, bisa berupa nomor atau nama barang
    input = currentWord;

    char inputstr[MaxEl];
    wordToString(input, inputstr);

    // cek apakah wishlist kosong, kalau kosong remove tidak bisa dilakukan
    if (IsEmptyLL(wishlist->wishlist_item)) {
        printf(RED"Penghapusan barang WISHLIST gagal dilakukan, WISHLIST kosong!\n"WHITE);
        return;
    }

    // cek apakah input berupa nomor
    if (isNumber(inputstr)) {
        idx = convertWordToInt(input);
        if (idx > 0 && idx <= wishlist->number) {
            DeleteAtLL(&wishlist->wishlist_item, idx - 1);
            printf(GREEN"Berhasil menghapus barang posisi ke-%d dari wishlist!\n"WHITE, idx);
            wishlist->number--;
            
        } else {
            printf(RED"Penghapusan barang WISHLIST gagal dilakukan, Barang ke-%d tidak ada di WISHLIST!\n"WHITE, idx);
        }
    } else if (compareWords("REMOVE", input, 6)) {
        // If no number is provided, ask for the item name
        printf("Masukkan nama barang yang akan dihapus: ");
        STARTLINE(); // Read the item name
        input = currentWord;
        wordToString(input, inputstr);

        if (isMemberLL(wishlist->wishlist_item, inputstr)) {
            DeleteByValueLL(&wishlist->wishlist_item, inputstr);
            printf(GREEN"%s berhasil dihapus dari wishlist!\n"WHITE, inputstr);
        } else {
            printf(RED"Penghapusan barang WISHLIST gagal dilakukan, %s tidak ada di WISHLIST!\n"WHITE, inputstr);
        }
    } else {
        printf(RED"Penghapusan barang WISHLIST gagal dilakukan, command tidak valid!\n"WHITE);
    }
}

// Fitur wishlistSwap
// Menukar posisi dua barang dalam wishlist
void wishlistSwap(WishlistUser *wishlist, int i, int j) {
    if (wishlist == NULL) {
        printf(RED"Error: Invalid wishlist pointer\n"WHITE);
        return;
    }

    if (wishlist->wishlist_item.First == NULL) {
        printf(RED"Wishlist kosong\n"WHITE);
        return;
    }

    int actualSize = 0;
    addressLL temp = wishlist->wishlist_item.First;
    while (temp != NULL) {
        actualSize++;
        temp = temp->next;
    }
    wishlist->number = actualSize;


    if (i == j) {
        printf(RED"Nomor tidak boleh sama. Silakan masukkan nomor yang berbeda.\n"WHITE);
        printf(RED"Pastikan input berupa nomor dan nomor tersebut valid.\n"WHITE);
        return;
    }

    if (i <= 0 || j <= 0 ) {
        // || i > wishlist->number || j > wishlist->number
        printf(RED"Posisi tidak valid! (i=%d, j=%d, max=%d)\n"WHITE, i, j, wishlist->number);
        return;
    }

    addressLL curr = wishlist->wishlist_item.First;
    addressLL node1 = NULL;
    addressLL node2 = NULL;
    int pos = 1;

    while (curr != NULL) {
        if (pos == i) node1 = curr;
        if (pos == j) node2 = curr;
        curr = curr->next;
        pos++;
    }

    if (wishlist->number <= 1) {
        printf(RED"Gagal menukar posisi %s!\n"WHITE, node1 ? node1->info : "item");
        printf(YELLOW"Wishlist hanya memiliki satu item\n"WHITE);
        return;
    }

    if (node1 == NULL || node2 == NULL) {
        printf(RED"Gagal menukar posisi %s!\n"WHITE, node1 ? node1->info : "item");
        return;
    }

    char tempInfo[100];
    my_strcpy(tempInfo, node1->info);
    my_strcpy(node1->info, node2->info);
    my_strcpy(node2->info, tempInfo);

    printf(GREEN"Berhasil menukar posisi %s dengan %s pada wishlist!\n"WHITE, tempInfo, node1->info);
}


void insertLastItem(ListItem *itemlist, Item item) {
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf(RED"Item sudah penuh. Tidak bisa menambahkan item %s\n"WHITE, item.name);
    }
}

// Cart Implementation
void cartPay(Global *gameState, User *profile, ListItem L) {
    int price = 0;
    int total = 0;
    int val;
    char input[50];
    int max = 0;
    int harga_per_barang = 0;
    int idxmax = 0;
    int lexical = 0;

    int uanguser = profile->money;
    
    printf("Kamu akan membeli barang-barang berikut.\n");
    if (IsEmptyMap(profile->cart)) {
        printf("Keranjang kamu kosong!\n");
    }
    else {
        printf("Kuantitas       Nama                      Total\n");
        for (int i = 0; i < profile->cart.Count; i++) {
            int harga = 0;
            boolean found = FALSE;
            for (int j = 0; j < L.itemLength; j++) {
                if (my_strcmp(L.item[j].name, profile->cart.Elements[i].Key)) {
                    harga = L.item[j].price;
                    found = TRUE;
                    break;
                }
            }

            if (found) {
                harga_per_barang = harga * profile->cart.Elements[i].Value;
                total += harga_per_barang;
                printf("%-15d %-25s %-d\n", profile->cart.Elements[i].Value, profile->cart.Elements[i].Key, harga_per_barang);
            }
            else {
                printf("%-30s %-8d (Harga tidak ditemukan)\n", profile->cart.Elements[i].Key, profile->cart.Elements[i].Value);
            }
            }
        }

        
        printf("Total biaya yang harus dikeluarkan adalah %d, apakah jadi dibeli?\n", total);
        printf("(Ya/Tidak)\n");

        STARTLINE();
        collectInput(input);
        wordToString(currentWord, input);     

        if (my_strcmp("Ya", input)) {
            if (total > uanguser) {
                printf("\n");
                printf("Uang kamu hanya %d, tidak cukup untuk membeli keranjang!\n", uanguser);
            }
            else {
                printf("Selamat kamu telah membeli barang-barang tersebut!\n");
                uanguser -= total;
                gameState->users[gameState->userIndex].money = uanguser;

                for (int i = 0; i < profile->cart.Count; i++) {
                    for (int j = 0; j < L.itemLength; j++) {
                        if (max > harga_per_barang) {
                            max = max;
                            idxmax = idxmax;
                        }
                        else if (max < harga_per_barang) {
                            max = harga_per_barang;
                            idxmax = i;
                        }
                        else if (max == harga_per_barang) {
                            if (lexical < profile->cart.Elements[i].Key[0]) {
                                lexical = profile->cart.Elements[i].Key[0];
                                idxmax = i;
                            }
                            else {
                                lexical = lexical;
                                idxmax = idxmax;
                            }
                        }
                }
                }
                infotypeStack x;
                x.harga = max;
                customStringCPY(x.name, profile->cart.Elements[idxmax].Key);
                Push(&profile->history, x); 

                while (!IsEmptyMap(profile->cart)) {
                    Delete(&profile->cart, profile->cart.Elements->Key);
                }
        } 

    }
    // printStack(&profile->history);
}


void cartRemove(Global *gameState, User *profile, char* removestr, int* idxint){
    int i = 0;
    boolean found = FALSE;

    if (IsEmptyMap(profile->cart)){
        printf(RED"Tidak bisa remove, keranjang kosong.\n"WHITE);
        return;
    }

    if (*idxint <= 0){
        printf(RED"Jumlah barang tidak valid.\n"WHITE);
        return;
    }

    if (!IsMemberMap(profile->cart, removestr)){
        printf(RED"Barang tidak ada di keranjang.\n"WHITE);
        return;
    }

    valuetype currentJumlah = Value(profile->cart, profile->cart.Elements->Key);

    if (currentJumlah < *idxint){
        printf(RED"Gagal mengurangi. Hanya terdapat %d %s di keranjang.\n"WHITE, currentJumlah, profile->cart.Elements->Key);
    }
    else if (currentJumlah == *idxint){
        printf(GREEN"%s sebanyak %d berhasil dihapus dari keranjang.\n"WHITE, profile->cart.Elements->Key, profile->cart.Elements->Value);
        Delete(&profile->cart, profile->cart.Elements->Key);
    }
    else{
        for (int i = 0; i < profile->cart.Count; i++) {
            if (my_strcmp(profile->cart.Elements[i].Key, removestr)){
                profile->cart.Elements[i].Value -= *idxint;
                printf(GREEN"%s sebanyak %d berhasil dihapus dari keranjang.\n"WHITE, removestr, *idxint);
                break;
            }
        }
    }
}

void cartShow(Global *gameState, User *profile, ListItem L){
    if (IsEmptyMap(profile->cart)){
        printf(RED"Keranjang anda masih kosong.\n"WHITE);
    }
    else{
        int subtotal = 0;
        printf(CYAN"Isi Keranjangmu: \n"WHITE);
        DisplayMap(profile, L);
    }
}

void cartAdd(Global *gameState, User *profile, ListItem *L, char* addstr, int* qtyint) {
    if (*qtyint <= 0){
        printf(RED"Jumlah barang tidak valid.\n"WHITE);
        return;
    }

    if (IsFullMap(profile->cart)){
        printf(RED"Keranjang penuh.\n"WHITE);
        return;
    }

    int i = 0;
    boolean found = FALSE;

    while (i < L->itemLength && !found) {
        if(my_strcmp(L->item[i].name, addstr)){
            found = TRUE;
            break;
        }
        i++;
    }

    if (found){
        if (!IsMemberMap(profile->cart, addstr)){
            Insert(&profile->cart, addstr, *qtyint);
            printf(GREEN"%s sebanyak %d berhasil ditambahkan ke keranjang.\n"WHITE, addstr, *qtyint);
        }
        else{
            profile->cart.Elements[i].Value += *qtyint;
            printf(GREEN"%s sebanyak %d berhasil ditambahkan ke keranjang.\n"WHITE, addstr, *qtyint);
        }
    }
    else{
        printf(RED"Barang tidak ditemukan.\n"WHITE);
    }
}

void DisplayMap(User *profile, ListItem L){
    int total = 0;
    int harga_per_barang = 0;

    int uanguser = profile->money;
    
    printf("Kamu akan membeli barang-barang berikut.\n");
    if (IsEmptyMap(profile->cart)) {
        printf("Keranjang kamu kosong!\n");
    }
    else {
        printf("Kuantitas       Nama                      Total\n");
        for (int i = 0; i < profile->cart.Count; i++) {
            int harga = 0;
            boolean found = FALSE;
            for (int j = 0; j < L.itemLength; j++) {
                if (my_strcmp(L.item[j].name, profile->cart.Elements[i].Key)) {
                    harga = L.item[j].price;
                    found = TRUE;
                    break;
                }
            }

            if (found) {
                harga_per_barang = harga * profile->cart.Elements[i].Value;
                total += harga_per_barang;
                printf("%-15d %-25s %-d\n", profile->cart.Elements[i].Value, profile->cart.Elements[i].Key, harga_per_barang);
            }
            else {
                printf("%-25s %-8d (Harga tidak ditemukan)\n", profile->cart.Elements[i].Key, profile->cart.Elements[i].Value);
            }
            }
        }

        
        printf("Total biaya yang harus dikeluarkan adalah %d.\n", total);
}
