#include <stdio.h>
#include <stdlib.h>
#include "../../include/features/main.h"
#include "../../include/features/work.h"

char pwdstr[MAX_LEN], userstr[MAX_LEN], currentUser[MAX_LEN] = "";


// Fungsi  Main
int main(){
    showMainMenu();
    return 0;
}

void showMainMenu(){   
    Global gameState = {0};
    gameState.isStarted = FALSE; 
    gameState.isLoaded = FALSE;
    gameState.isLogin = FALSE;
    makeListItem(&gameState);

    printf("                                                                                           \n"
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

    printf("Selamat datang di PURRMART!\nTolong masukkan command yang valid (START, LOAD, REGISTER, LOGIN, HELP, atau QUIT.)\n");

    while (1) {
        printf(">> ");
        Word command;
        STARTLINE();
        command = currentWord;

        if (compareWords("START", command, 5)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Anda harus load file konfigurasi terlebih dahulu.\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                Start(&gameState);
            }
        } 
        else if (compareWords("LOAD", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Masukkan nama file yang akan diload: ");
                Word filename;
                STARTLINE();
                filename = currentWord;

                char file[MAX_LEN];
                wordToString(filename, file);
                Load(file, &gameState);
            } else if  (!gameState.isStarted && gameState.isLoaded){
                printf("Program belum di-Start. Silahkan START terlebih dahulu.\n");
            } else if (gameState.isStarted && gameState.isLoaded){
                printf("Game sudah dimulai. Tidak bisa load file konfigurasi.\n");
            }
        }
        else if (compareWords("HELP", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted && !gameState.isLogin){
                printf("START -> Untuk masuk sesi baru\n");
                printf("LOAD -> Untuk memulai sesi berdasarkan file konfigurasi\n");
                printf("QUIT -> Untuk keluar dari program\n");
            } else if (gameState.isLoaded && !gameState.isStarted && !gameState.isLogin){ 
                printf("=====[ Login Menu Help PURRMART ]=====\n");
                printf("REGISTER -> Untuk melakukan pendaftaran akun baru\n");
                printf("LOGIN -> Untuk masuk ke dalam akun dan memulai sesi\n");
                printf("QUIT -> Untuk keluar dari program\n");   
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){ 
                printf("=====[ Menu Help PURRMART ]=====\n");
                printf("WORK -> Untuk bekerja\n");
                printf("WORK CHALLENGE -> Untuk mengerjakan challenge\n");
                printf("STORE LIST -> Untuk melihat barang-barang di toko\n");
                printf("STORE REQUEST -> Untuk meminta penambahan barang\n");
                printf("STORE SUPPLY -> Untuk menambahkan barang dari permintaan\n");
                printf("STORE REMOVE -> Untuk menghapus barang\n");
                printf("STORE REQUEST BIOWEAPON -> Untuk memproses DNA menjadi bioweapon\n");
                printf("WISHLIST SHOW -> Untuk melihat wishlist\n");
                printf("WISHLIST ADD -> Untuk menambahkan barang ke wishlist\n");
                printf("WISHLIST REMOVE -> Untuk menghapus barang dari wishlist\n");
                printf("WISHLIST CLEAR -> Untuk menghapus seluruh barang dari wishlist\n");
                printf("WISHLIST SWAP -> Untuk menukar posisi dua barang dalam wishlist\n");
                printf("PROFILE -> Untuk melihat profil\n");
                printf("LOGOUT -> Untuk keluar dari sesi\n");
                printf("SAVE -> Untuk menyimpan state ke dalam file\n");
                printf("QUIT -> Untuk keluar dari program\n");
            }
        }
        else if (compareWords("LOGIN", command, 5)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){
                printf("Anda masih tercatat sebagai %s. Silahkan LOGOUT terlebih dahulu.\n", currentUser);
            } else {
                Login(gameState.users, gameState.userCount);
                gameState.isLogin = TRUE;
                //gameState.users->money = gameState.users[0].money;
                //printf("%d\n", gameState.users->money);
            }
        }
        else if (compareWords("LOGOUT", command, 6)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Anda belum login. Silakan login terlebih dahulu\n");
            } else {
                Logout(gameState.users, gameState.userCount);
                gameState.isLogin = FALSE;
            }
        }
        else if (compareWords("REGISTER", command, 8)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){
                printf("Anda sudah login. Silahkan LOGOUT terlebih dahulu.\n");
            } else {
                Register(&gameState);
                gameState.isLogin = TRUE;
            }
        }
        else if (compareWords("PROFILE", command, 7)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                profile(gameState.users);
            }
        }
        else if (compareWords("HISTORY", command, 7)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                history(&gameState.users->history);
            }
        }
        else if (compareWords("WORK", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                work(&gameState.users->money);
            } 
        }
        else if (compareWords("WORK CHALLENGE", command, 14)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                printf("Daftar challenge yang tersedia:\n");
                printf("1. Tebak Angka (biaya main=200)\n");
                printf("2. W0RDL399 (biaya main=500)\n");
                printf("3. QUANTUM W0RDL399 (biaya main=1000)\n");

                printf("Masukan challenge yang hendak dimainkan: ");
                Word choice;
                STARTLINE();
                choice = currentWord;

                if (compareWords("1", choice, 1)){
                    tebakAngkaRNG(&gameState.users->money);
                }
                else if (compareWords("2", choice, 1)){
                    playWordl3(&gameState.users->money);
                }
                else if (compareWords("3", choice, 1)){
                    playQuantumWordl3(&gameState.users->money);
                }
            }
        }
        else if (compareWords("STORE LIST", command, 10)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeList(&gameState.itemList);
            }
        }
        else if (compareWords("STORE REQUEST", command, 13)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                storeRequest(&gameState.itemList, &gameState.requestQueue);
            }

        }
        else if (compareWords("STORE REQUEST BIOWEAPON", command, 23)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                processDNA();
            }

        }

        // Integrasi wishlist pada main
        else if (compareWords("WISHLIST SHOW", command, 13)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                wishlistShow(&gameState.users->wishlist);
            }
        }
        else if (compareWords("WISHLIST ADD", command, 12)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } 
            else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } 
            else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                wishlistAdd(&gameState.itemList, &gameState.users->wishlist);
            }
        }
        else if (compareWords("WISHLIST REMOVE", command, 15)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            }
            else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            }
            else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            }
            else {
                wishlistRemove(&gameState.users->wishlist);
            }
        }
        else if (compareWords("WISHLIST CLEAR", command, 14)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            }
            else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            }
            else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            }
            else {
                wishlistClear(&gameState.users->wishlist);
            }
        }

        // wishlistSwap
        else if (compareWords("WISHLIST SWAP", command, 13)) {
            if (!gameState.isLoaded && !gameState.isStarted) {
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted) {
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin) {
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                // Handling harus bawa i dan j pake STARTLINE dll
                int i, j;
                Word wordI, wordJ;

                printf("Masukkan nomor urut barang pertama: ");
                STARTLINE();
                wordI = currentWord;
                i = WordToInt(wordI);

                printf("Masukkan nomor urut barang kedua: ");
                STARTLINE();
                wordJ = currentWord;
                j = WordToInt(wordJ);

                printf("DEBUG: Calling wishlistSwap with i=%d, j=%d\n", i, j); // Debug statement

                if (i > 0 && j > 0) {
                    wishlistSwap(&gameState.users->wishlist, i, j);
                } else {
                    printf("Nomor urut tidak valid. Silakan coba lagi.\n");
                }
            }
        }

        else if (compareWords("GLOBALALIGNMENT", command, command.Length)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                deteksiKebocoranDNA();
            }
        }
        else if (compareWords("OPTIMASIRUTE", command, command.Length)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                OptimasiRuteEkspedisi();
            }
        }
        else if (compareWords("STORE SUPPLY", command, 12)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeSupply(&gameState.itemList, &gameState.requestQueue);
            }
        }
        else if (compareWords("STORE REMOVE", command, 12)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeRemove(&gameState.itemList);
            }
        }

        // else if (compareWords("WISHLIST SHOW", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         wishlistShow(&gameState.users);
        //     }
        // }
        // else if (compareWords("WISHLIST ADD", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         wishlistAdd(&gameState.itemList, &gameState.users);
        //     }
        // }
        // else if (compareWords("WISHLIST REMOVE", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         wishlistRemove(&gameState.users);
        //     }
        // }
        // else if (compareWords("CART ADD", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         Word itemCart, tempQty;
        //         int qtyCart;

        //         printf("Masukkan nama item yang ingin ditambahkan ke cart: ");
        //         STARTLINE();
        //         itemCart = currentWord;

        //         printf("Masukkan jumlah item yang ingin ditambahkan ke cart: ");
        //         STARTLINE();
        //         tempQty = currentWord;
        //         int Qty = WordToInt(tempQty);
                
        //         wordToString(itemCart, gameState.users->cart.Elements->Key);
        //         cartAdd(&gameState.users->cart, &gameState.itemList, &gameState.users->cart.Elements->Key, Qty);
        //     }
        // }
        // else if (compareWords("CART REMOVE", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         Word itemCart, tempQty;
        //         int qtyCart;

        //         printf("Masukkan nama item yang ingin ditambahkan ke cart: ");
        //         STARTLINE();
        //         itemCart = currentWord;

        //         printf("Masukkan jumlah item yang ingin ditambahkan ke cart: ");
        //         STARTLINE();
        //         tempQty = currentWord;
        //         int qtyCart = WordToInt(tempQty);
                
        //         wordToString(itemCart, gameState.users->cart.Elements->Key);
        //         cartRemove(&gameState.users->cart, &itemCart, qtyCart);
        //     }
        // }
        // else if (compareWords("CART SHOW", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         cartShow(&gameState.users->cart, &gameState.itemList);
        //     }
        // }
        // else if (compareWords("CART PAY", command, command.Length)){
        //     if (!gameState.isLoaded && !gameState.isStarted){
        //         printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
        //     } else if (gameState.isLoaded && !gameState.isStarted){
        //         printf("Anda belum start program\n");
        //     } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
        //         printf("Lakukan login atau register terlebih dahulu\n");
        //     } else {
        //         cartPay(&gameState.users->cart, gameState.itemList);
        //     }
        // }
        else if (compareWords("SAVE", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && !gameState.isStarted){
                printf("Anda belum start program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                 Save("savefile.txt", &gameState);
            }
        }
        else if (compareWords("QUIT", command, 4)){
            printf("Keluar dari program... \n");
            break;
        }
        else {
            printf("Command tidak valid. Silakan coba command yang valid.\n");
        }
    }
}

void Start(Global *gameState) {
    gameState->isStarted = TRUE;
    printf("Game berhasil dimulai. Selamat bermain!\n");
}

// Implement other functions as in your original code...

void Load(const char *filename, Global *global) {
    if (filename == NULL || *filename == '\0') {
        printf("Nama file tidak valid.\n");
        return;
    }

    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = openFile(filepath, "r");
    if (file == NULL) {
        printf("Save file tidak ditemukan. PURRMART gagal dijalankan.\n");
        return;
    }

    makeListItem(global);

    // Item di Store
    int itemCount;
    boolean succread_item = FALSE;
    if (readFile(file, "%d", &itemCount) != 1) {
        printf("Kesalahan format file: jumlah item tidak valid.\n");
        closeFile(file);
        return;
    }
    printf("DEBUG: Reading %d items\n", itemCount);

    for (int i = 0; i < itemCount; i++) {
        int price;
        char name[MAX_LEN];
        
        if (readItem(file, "%d %[^\n]", &price, name) != 2) {
            printf("Kesalahan format file: data item tidak valid.\n");
            closeFile(file);
            return;
        }
        printf("DEBUG: Read item %d: %s (price: %d)\n", i+1, name, price);

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
        printf("Kesalahan format file: jumlah user tidak valid.\n");
        closeFile(file);
        return;
    }
    printf("DEBUG: Reading %d users\n", userCount);

    for (int i = 0; i < userCount; i++) {
        int money;
        char username[MAX_LEN], password[MAX_LEN];

        if (readUser(file, "%d %s %s", &money, username, password) != 3) {
            printf("Kesalahan format file: data user tidak valid.\n");
            closeFile(file);
            return;
        }
        printf("DEBUG: Read user %d: %s (money: %d)\n", i+1, username, money);

        global->users[i].money = money;
        customStringCPY(global->users[i].name, username);
        customStringCPY(global->users[i].password, password);
        global->userCount++;
        global->users[i].history.TOP = -1;
        succread_user = TRUE; 

        // Load purchase history
        int historyCount;
        if (readFile(file, "%d", &historyCount) != 1) {
            printf("Kesalahan format file: jumlah riwayat pembelian tidak valid.\n");
            closeFile(file);
            return;
        }
        printf("DEBUG: Reading %d purchase history\n", historyCount);

        succread_ph = TRUE;
        for (int j = 0; j < historyCount; j++) {
            infotypeStack item;
            int cost;
            char itemName[MAX_LEN];
            if (readItem(file, "%d %[^\n]", &cost, itemName) != 2) {
                printf("Kesalahan format file: data riwayat pembelian tidak valid.\n");
                closeFile(file);
                return;
            }
            item.harga = cost;
            customStringCPY(item.name, itemName);
            Push(&global->users[i].history, item);
        }
        printf("\nDEBUG: Purchase History for user %s:\n", global->users[i].name);
        printStack(&global->users[i].history);

        // Load wishlist
        int wishlistCount;
        if (readFile(file, "%d", &wishlistCount) != 1) {
            printf("Kesalahan format file: jumlah wishlist tidak valid.\n");
            closeFile(file);
            return;
        }
        printf("DEBUG: Reading %d wishlist\n", wishlistCount);

        succread_wl = TRUE;
        global->users[i].wishlist.wishlist_item.First = NULL; 
        for (int j = 0; j < wishlistCount; j++) {
            char wishItem[MAX_LEN];
            if (readItem2(file, " %49[^\n]", wishItem) != 1) {
                printf("Kesalahan format file: data wishlist tidak valid.\n");
                closeFile(file);
                return;
            }
            global->users[i].wishlist.number = wishlistCount;
            InsertFirstLL(&global->users[i].wishlist.wishlist_item, wishItem);
            printf("DEBUG: Read wishlist %d: %s\n", j+1, global->users[i].wishlist.wishlist_item.First->info);
        }
    }

    if (succread_item && succread_user && succread_ph && succread_wl) {
        global->isLoaded = TRUE;
        printf("File konfigurasi berhasil diload. PURRMART siap digunakan.\n");
    } else {
        printf("Gagal load file konfigurasi. Silakan cek file konfigurasi.\n");
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

void Login(User *users, int user_count) {

    Word username,password;
    
    printf("Username: ");
    STARTLINE();
    username = currentWord;
    wordToString(username, userstr);

    printf("Password: ");
    STARTLINE();
    password = currentWord;
    wordToString(password, pwdstr);

    int userIndex = findUser(users, user_count, userstr, pwdstr);
    
    if(userIndex != -1) {
        customStringCPY(currentUser, users[userIndex].name);
        printf("Anda telah berhasil login sebagai %s.\n", currentUser);
    }
    else {
        printf("Username atau password salah. Silakan coba lagi.\n");
    }

}

void Logout(User *users, int user_count) {
    printf("%s telah logout dari sistem PURRMART. Silakan REGISTER/LOGIN kembali untuk melanjutkan.\n", currentUser);
    currentUser[0] = '\0';  // Clear the currentUser string
}

void Register(Global *gameState) {
    if (!gameState->isLoaded && !gameState->isStarted) {
        printf("Game belum dimulai. Silakan load dan start terlebih dahulu\n");
        return;
    }

    Word username, password;
    
    printf("Username: ");
    STARTLINE();
    username = currentWord;
    wordToString(username, userstr);
    
    printf("Password: ");
    STARTLINE();
    password = currentWord;
    wordToString(password, pwdstr);
    
    if (gameState->userCount >= MAX_USERS) {
        printf("Maksimum jumlah pengguna telah tercapai.\n");
        return;
    }
    
    for (int i = 0; i < gameState->userCount; i++) {
        if (compareWords(gameState->users[i].name, username, username.Length)) {
            printf("Username %s sudah terdaftar. Silakan gunakan username lain.\n", userstr);
            return;
        }
    }

    customStringCPY(gameState->users[gameState->userCount].name, userstr);
    customStringCPY(gameState->users[gameState->userCount].password, pwdstr);
    gameState->users[gameState->userCount].money = 0;
    gameState->users[gameState->userCount].history.TOP = -1;
    gameState->users[gameState->userCount].wishlist.wishlist_item.First = NULL;
    gameState->userCount++;

    printf("Akun dengan username %s telah berhasil dibuat.\n", userstr);
    printf("Silakan LOGIN untuk melanjutkan.\n");
}

void Save(const char *filename, Global *gameState) {
    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = openFile(filepath, "w");
    if (file == NULL) {
        printf("Gagal membuat file save.\n");
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
    printf("Game berhasil disimpan dalam %s.\n", filepath);
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
    printf("Usernane: %s\n", users[userIndex].name);
    printf("Money: %d\n", users[userIndex].money);
    
    if (userIndex != -1) {
        printf("Wishlist:\n");
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
    printf("\nDEBUG: Printing Stack Contents:\n");
    if (IsEmptyStack(*S)) {
        printf("Stack is empty\n");
        return;
    }
    
    for (int i = S->TOP; i >= 0; i--) {
        printf("Stack[%d]: %s (cost: %d)\n", 
               S->TOP - i + 1, 
               S->T[i].name, 
               S->T[i].harga);
    }
    printf("Total items in stack: %d\n", S->TOP + 1);
}

// store

void storeList (ListItem *L) {
    if (IsEmptyItem(L)) {
        printf("TOKO KOSONG\n");
    }
    else { 
        printf("List barang yang ada di toko: \n");
        for (int i  = 0; i < L->itemLength; i ++) {
            printf("");
            printf("%d. %s - Harga: %d\n", i + 1, L->item[i].name, L-> item[i].price);
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
    wordToString(req, reqstr); // Convert Word to string

    boolean isFoundInList = SearchItem(*L, reqstr);
    if (isFoundInList) {
        printf("Barang dengan nama yang sama sudah ada di toko\n");
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
            printf("Barang dengan nama yang sama sudah ada di antrian\n");
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
        printf("%s telah berhasil dihapus.\n", item_namestr);
    }
    else {
        printf("Toko tidak menjual %s.\n", item_namestr);
    }
}

void storeSupply(ListItem *L, QueueItem *Q) { 
    if (!isEmptyItem(*Q)) {
        char item_name[50];
        dequeueItem(Q, item_name);
        printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak): ", item_name);

        Word response;
        STARTLINE();
        char responsestr;
        response = currentWord;
        wordToString(response, &responsestr);
        boolean inputValid = FALSE;

        while (!inputValid) {
            if (customStringCMP(&responsestr, "Terima") == 0 || customStringCMP(&responsestr, "Tunda") == 0 || customStringCMP(&responsestr, "Tolak") == 0) {
                inputValid = TRUE;
            }
            else {
                printf("Input tidak valid. Silakan coba lagi: ");
                scanWord(&response);
                wordToString(response, &responsestr);
            }
        }

        if (customStringCMP(&responsestr, "Terima") == 0) {
            Word price;
            printf("Harga barang: ");
            scanWord(&price);
            boolean validprice = FALSE;

            while (!validprice) {
                if (isWordInt(price)) {
                    validprice = TRUE;
                }
                else {
                    printf("Harga tidak valid. Silakan coba lagi: ");
                    scanWord(&price);
                }
            }

            int priceint = convertWordToInt(price);
            Item new_item;
            customStringCPY(new_item.name, item_name);
            new_item.price = priceint;

            insertLastItem(L, new_item);
            printf("%s dengan harga %d telah ditambahkan ke toko.\n", item_name, priceint);
        }
        else if (customStringCMP(&responsestr, "Tunda") == 0) {
            printf("%s dikembalikan ke antrian.\n", item_name);
            enqueueItem(Q, item_name);
        }
        else if (customStringCMP(&responsestr, "Tolak") == 0) {
            printf("%s dihapus dari antrian.\n", item_name);
        }
    }
    else {
        printf("Antrian kosong.\n");
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
        printf("Berikut adalah isi wishlist-mu:\n");
        addressLL P = wishlist->wishlist_item.First;
        int idx = 1;
        while (P != Nil) {
            printf("%d %s\n", idx++, P->info);
            P = P->next;
        }
    } else {
        printf("Wishlist kamu kosong!\n");
    }
}

// Fitur wishlistAdd
// Menambahkan barang ke wishlist jika barang ada di store dan belum ada di wishlist
void wishlistAdd(ListItem *L, WishlistUser *wishlist) {
    Word item_name;
    printf("Masukkan nama barang: ");
    STARTLINE();

    char item_namestr[MaxEl];
    item_name = currentWord;    
    wordToString(item_name, item_namestr); 

    // Cek apakah barang ada di store
    boolean isFoundInList = SearchItem(*L, item_namestr);
    if (isFoundInList) {
        // Cek apakah barang sudah ada di wishlist
        if (isMemberLL(wishlist->wishlist_item, item_namestr)) {
            printf("%s sudah ada di wishlist\n", item_namestr);
            wishlistAdd(L, wishlist); // Minta input ulang
        } else {
            InsertLastLL(&wishlist->wishlist_item, item_namestr);
            wishlist->number++;
            printf("Berhasil menambahkan %s ke wishlist!\n", item_namestr);
        }
    } else {
        printf("Tidak ada barang dengan nama %s!\n", item_namestr);
        wishlistAdd(L, wishlist); // Minta input ulang
    }
}

// Fitur wishlistClear
// Menghapus semua barang di wishlist
void wishlistClear(WishlistUser *wishlist) {
    if (IsEmptyLL(wishlist->wishlist_item)) {
        printf("Wishlist sudah kosong.\n");
    } else {
        ClearLL(&wishlist->wishlist_item);
        printf("Wishlist telah dikosongkan.\n");
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
    Word input;
    printf("Masukkan nama/nomor barang yang akan dihapus: ");
    STARTLINE();

    char inputstr[MaxEl];
    input = currentWord;    
    wordToString(input, inputstr);

    // Cek apakah input berupa nomor atau nama barang
    if (isNumber(inputstr)) {
        int idx = convertWordToInt(input);
        if (idx > 0 && idx <= wishlist->number) {
            DeleteAtLL(&wishlist->wishlist_item, idx - 1);
            printf("Barang pada posisi %d berhasil dihapus dari wishlist!\n", idx);
        } else {
            printf("Penghapusan barang wishlist gagal dilakukan, posisi %d tidak ada di wishlist!\n", idx);
            wishlistRemove(wishlist); // Minta input ulang
        }
    } else {
        if (isMemberLL(wishlist->wishlist_item, inputstr)) {
            DeleteByValueLL(&wishlist->wishlist_item, inputstr);
            printf("%s berhasil dihapus dari wishlist!\n", inputstr);
        } else {
            printf("Penghapusan barang wishlist gagal dilakukan, %s tidak ada di wishlist!\n", inputstr);
            wishlistRemove(wishlist); // Minta input ulang
        }
    }
}

// Fitur wishlistSwap
// Menukar posisi dua barang dalam wishlist
void wishlistSwap(WishlistUser *wishlist, int i, int j) {
    printf("DEBUG: Entered wishlistSwap function\n");
    printf("DEBUG WISHLIST NUMBER %d\n", wishlist->number);
    if (i > 0 && i <= wishlist->number && j > 0 && j <= wishlist->number) {
        char item1[MaxEl], item2[MaxEl];
        char *tmp1 = GetLL(wishlist->wishlist_item, i);
        char *tmp2 = GetLL(wishlist->wishlist_item, j);
        
        // Salin nama barang
        int k;
        for (k = 0; tmp1[k] != '\0'; k++) item1[k] = tmp1[k];
        item1[k] = '\0';
        for (k = 0; tmp2[k] != '\0'; k++) item2[k] = tmp2[k];
        item2[k] = '\0';
        printf("TANDA1%%%%%%%%\n");
        swapListLinier(&wishlist->wishlist_item, i - 1, j - 1);
        
        printf("Urutan %s berubah dari %d menjadi %d. Sebaliknya, urutan %s berubah dari %d menjadi %d\n", 
               item1, i, j, item2, j, i);
    } else {
        if (wishlist->number <= 1) {
            printf("Hanya terdapat satu barang (%s) pada wishlist sehingga posisinya tidak dapat ditukar\n", 
                   GetLL(wishlist->wishlist_item, 1));
        } else {
            printf("Posisi tidak valid!\n");
        }
    }
}

// // Fungsi tambahan untuk string manipulasi
// int customStringCMP(const char *str1, const char *str2) {
//     int i = 0;
//     while (str1[i] != '\0' && str2[i] != '\0') {
//         if (str1[i] != str2[i]) {
//             return str1[i] - str2[i];
//         }
//         i++;
//     }
//     return str1[i] - str2[i];
// }

// void customStringCPY(char *dest, const char *src) {
//     int i = 0;
//     while (src[i] != '\0') {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
// }

void insertLastItem(ListItem *itemlist, Item item) {
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
    }
}

// // driver main untuk testing sementara
// int main(){
//     // testing wishlistAdd
//     ListItem itemList = {
//         .item = {
//         {"AK47", 20},
//         {"Lalabu", 20},
//         {"Ayam Goreng Crisbar", 10},
//         {"Kunjaw UAS Alstrukdat", 50}
//         },
//         .itemLength = 4
//     };
//     WishlistUser wishlist;
//     CreateEmptyLL(&wishlist.wishlist_item);
//     wishlist.number = 0;
//     wishlistAdd(&itemList, &wishlist);
//     // wishlistAdd(&itemList, &wishlist);
//     // wishlistAdd(&itemList, &wishlist);
//     // wishlistAdd(&itemList, &wishlist);

//     // wishlistShow(&wishlist);
//     // // wishlistClear(&wishlist);
//     // wishlistRemove(&wishlist);
//     // wishlistShow(&wishlist);
//     // wishlistRemove(&wishlist);
//     // wishlistShow(&wishlist);
//     wishlistSwap(&wishlist, 1, 2);
    
//     return 0;
// }*/

// Cart Function
// void cartPay(Map *M, ListItem L) {
//     Global userprofile = {0};
//     int price = 0;
//     int total = 0;
//     int val;
//     char input[50];
//     int uanguser = userprofile.users->money;

//     printf("Kamu akan membeli barang-barang berikut.\n");
//     if (IsEmptyMap(*M)) {
//         printf("Keranjang kamu kosong!\n");
//     }
//     else {
//         printf("Kuantitas       Nama            Total\n");
//         for (int i = 0; i < (*M).Count; i++) {
//             val = (*M).Elements[i].Value;
//             price = val * L.item[i].price;
//             printf("%-10d %-20s %d", val, (*M).Elements[i].Key, price);
//             total += price;
//         }
//         printf("Total biaya yang harus dikeluarkan adalah %d, apakah jadi dibeli?\n", total);
//         printf("(Ya/Tidak)\n");

//         STARTLINE();
//         collectInput(input);
//         wordToString(currentWord, input);     

//         if (my_strcmp("Ya", input)) {
//             if (total > uanguser) {
//                 printf("\n");
//                 printf("Uang kamu hanya %d, tidak cukup untuk membeli keranjang!\n", userprofile.users->money);
//             }
//             else {
//                 printf("Selamat kamu telah membeli barang-barang tersebut!\n");
//                 uanguser -= total;
//             }
//         } 
//     }
// }

// int cart(Map M, ListItem L){
//     char input[50];
//     char *firstWord, *secondWord, *thirdWord, *fourthWord;
//     int subtotal = 0;

//     if (IsEmptyMap(M)){
//         printf("Keranjang anda masih kosong.\n");
//     }
//     else{
//         printf("Isi Keranjang: \n");
//         DisplayMap(M, L, &subtotal);
//     }

//     while(1){
//         STARTLINE();
//         collectInput(input);
//         wordToString(currentWord, input);
            
//         firstWord = my_strtok(input, " "); // baca kata pertama
//         secondWord = my_strtok(NULL, " "); // baca kata kedua
//         thirdWord = my_strtok(NULL, " "); // baca kata ketiga
//         fourthWord = my_strtok(NULL, " "); // baca kata keempat

//         keytype barang = "";
//         valuetype jumlah = 0;
//         if (thirdWord != NULL && fourthWord != NULL) {
//             my_strcpy(barang, thirdWord);
//             jumlah = atoi(fourthWord);
//         }

//         if (my_strcmp(firstWord, "HELP")){
//             printf("Command list: \n");
//             printf("1. CART ADD <barang> <jumlah>\n");
//             printf("2. CART REMOVE <barang> <jumlah>\n");
//             printf("3. CART SHOW\n");
//             printf("4. CART PAY\n");
//             printf("5. EXIT\n");
//         }
//         else if (my_strcmp(firstWord, "EXIT")){
//             break;
//         }
//         else if (my_strcmp(firstWord, "CART")){
//             if (my_strcmp(secondWord, "ADD")){
//                 cartAdd(&M, &L, barang, jumlah);
//             }
//             else if (my_strcmp(secondWord, "REMOVE")){
//                 cartRemove(&M, barang, jumlah);
//             }
//             else if (my_strcmp(secondWord, "SHOW")){
//                 cartShow(&M, &L);
//                 printf("Total biaya yang harus dikeluarkan: %d\n", subtotal);
//             }
//         //     // else if (my_strcmp(secondWord, "PAY")){
//         //     //     cartPay(M, L);
//         //     // } beluumm implementt
//         }
//         else{
//             printf("Command tidak valid. Ketik HELP untuk melihat list command\n");
//         }
//     }
//     return 0;
// }


// void cartRemove(Map *M, keytype *k, valuetype v){
//     int i = 0;
//     boolean found = FALSE;

//     if (IsEmptyMap(*M)){
//         printf("Tidak bise remove, keranjang kosong.\n");
//         return;
//     }

//     if (v <= 0){
//         printf("Jumlah barang tidak valid.\n");
//         return;
//     }

//     if (!IsMemberMap(*M, k)){
//         printf("Barang tidak ada di keranjang.\n");
//         return;
//     }

//     valuetype currentJumlah = Value(*M, k);

//     if (currentJumlah < v){
//         printf("Gagal mengurangi. Hanya terdapat %d %s di keranjang.\n", currentJumlah, k);
//     }
//     else if (currentJumlah == v){
//         Delete(M, k);
//         printf("%s sebanyak %d berhasil dihapus dari keranjang.\n", k, v);
//     }
//     else{
//         for (int i = 0; i < M->Count; i++) {
//             if (my_strcmp(M->Elements[i].Key, k)) {
//                 M->Elements[i].Value -= v;
//                 printf("%s sebanyak %d berhasil dihapus dari keranjang.\n", k, v);
//                 break;
//             }
//         }
//     }
// }   


// void cartShow(Map *M, ListItem *L){
//     if (IsEmptyMap(*M)){
//         printf("Keranjang anda masih kosong.\n");
//     }
//     else{
//         int subtotal = 0;
//         printf("Isi Keranjangmu: \n");
//         DisplayMap(*M, *L, &subtotal);
//     }
// }

// // void cartPay(Map *M, Stack *H, int *balance);
// // GARAP HISTORY DULU

// char* my_strtok(char* str, const char* delim) {
//     static char* last;
//     if (str) {
//         last = str;
//     }
//     if (!last) {
//         return NULL;
//     }
//     char* start = last;
//     while (*last) {
//         const char* d = delim;
//         while (*d) {
//             if (*last == *d) {
//                 break;
//             }
//             d++;
//         }
//         if (*d) {
//             break;
//         }
//         last++;
//     }
//     if (*last) {
//         *last = '\0';
//         last++;
//     } else {
//         last = NULL;
//     }
//     return start;
// }

// void cartAdd(Map *M, ListItem *L, keytype k, valuetype v){

//     if (v <= 0){
//         printf("Jumlah barang tidak valid.\n");
//         return;
//     }

//     if (IsFullMap(*M)){
//         printf("Keranjang penuh.\n");
//         return;
//     }

//     int i = 0;
//     boolean found = FALSE;

//     while (i < L->itemLength && !found) {
//         if(my_strcmp(L->item[i].name, k)){
//             found = TRUE;
//             break;
//         }
//         i++;
//     }

//     if (found){
//         if (!IsMemberMap(*M, k)){
//             Insert(M, k, v);
//             printf("%s sebanyak %d berhasil ditambahkan ke keranjang.\n", k, v);
//         }
//         else{
//             M->Elements[i-1].Value += v;
//             printf("%s sebanyak %d berhasil ditambahkan ke keranjang.\n", k, v);
//         }
//     }
//     else{
//         printf("Barang tidak ditemukan.\n");
//     }
// }

void DisplayMap(Map M, ListItem L, int *subtotal){
    if (IsEmptyMap(M)) {
        printf("Map is empty.\n");
    } else {
        printf("Barang         Jumlah    Total\n");
        for (int i = 0; i < M.Count; i++) {
            int harga = 0;
            boolean found = FALSE;
            for (int j = 0; j < L.itemLength; j++) {
                if (my_strcmp(L.item[j].name, M.Elements[i].Key)) {
                    harga = L.item[j].price;
                    found = TRUE;
                    break;
                }
            }

            if (found) {
                int total = harga * M.Elements[i].Value;
                *subtotal += total;
                printf("%-15s %-8d %-d\n", M.Elements[i].Key, M.Elements[i].Value, total);
            }
            else {
                printf("%-15s %-8d (Harga tidak ditemukan)\n", M.Elements[i].Key, M.Elements[i].Value);
            }
        }
    }
}