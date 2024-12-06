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
    GameState gameState = {0};
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
            if (!gameState.isLoaded) {
                printf("Anda harus load file konfigurasi terlebih dahulu.\n");
            } else {
                Start(&gameState);
                gameState.isStarted = TRUE;
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
                gameState.isLoaded = TRUE;
                gameState.users[0].money = 1000;
            } else{
                printf("Game sudah dimulai. Tidak bisa load file konfigurasi.\n");
            }
        }
        else if (compareWords("HELP", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted && !gameState.isLogin){
                printf("START -> Untuk masuk sesi baru\n");
                printf("LOAD -> Untuk memulai sesi berdasarkan file konfigurasi\n");
                printf("QUIT -> Untuk keluar dari program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){ 
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
                printf("LOGOUT -> Untuk keluar dari sesi\n");
                printf("SAVE -> Untuk menyimpan state ke dalam file\n");
                printf("QUIT -> Untuk keluar dari program\n");
            }
        }
        else if (compareWords("LOGIN", command, 5)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
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
            } else if (gameState.isLoaded && gameState.isStarted && gameState.isLogin){
                printf("Anda sudah login. Silahkan LOGOUT terlebih dahulu.\n");
            } else {
                Register(&gameState);
                gameState.isLogin = TRUE;
            }
        }
        else if (compareWords("WORK", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                work(&gameState.users->money);
            } 
        }
        else if (compareWords("WORK CHALLENGE", command, 14)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
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
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeList(&gameState.itemList);
            }
        }
        else if (compareWords("STORE REQUEST", command, 13)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
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
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } 
            else {
                processDNA();
            }

        }
        else if (compareWords("STORE SUPPLY", command, 12)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeSupply(&gameState.itemList, &gameState.requestQueue);
            }
        }
        else if (compareWords("STORE REMOVE", command, 12)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
            } else if (gameState.isLoaded && gameState.isStarted && !gameState.isLogin){
                printf("Lakukan login atau register terlebih dahulu\n");
            } else {
                storeRemove(&gameState.itemList);
            }
        }
        else if (compareWords("SAVE", command, 4)){
            if (!gameState.isLoaded && !gameState.isStarted){
                printf("Lakukan Command LOAD dan START terlebih dahulu untuk memulai program\n");
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

boolean Start(GameState *gameState) {
    if (!gameState->isLoaded) {
        printf("Anda harus load file konfigurasi terlebih dahulu.\n");
        return FALSE;
    } else {
        printf("Game berhasil dimulai. Selamat bermain!\n");
        return TRUE;
    }
}

// Implement other functions as in your original code...

void Load(const char *filename, GameState *gameState) {
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

    makeListItem(gameState);

    int itemCount;
    if (readFile(file, "%d", &itemCount) != 1) {
        printf("Kesalahan format file: jumlah item tidak valid.\n");
        closeFile(file);
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        int price;
        char name[MAX_LEN];
        
        if (readItem(file, "%d %[^\n]", &price, name) != 2) {
            printf("Kesalahan format file: data item tidak valid.\n");
            closeFile(file);
            return;
        }

        gameState->itemList.item[i].price = price;
        customStringCPY(gameState->itemList.item[i].name, name);
        gameState->itemList.itemLength++;
    }

    int userCount;
    if (readFile(file, "%d", &userCount) != 1) {
        printf("Kesalahan format file: jumlah user tidak valid.\n");
        closeFile(file);
        return;
    }

    for (int i = 0; i < userCount; i++) {
        int money;
        char username[MAX_LEN], password[MAX_LEN];
        
        if (readUser(file, "%d %s %s", &money, username, password) != 3) {
            printf("Kesalahan format file: data user tidak valid.\n");
            closeFile(file);
            return;
        }

        gameState->users[i].money = money;
        printf("%d\n", money);
        customStringCPY(gameState->users[i].name, username);
        customStringCPY(gameState->users[i].password, password);
        gameState->userCount++;
    }

    gameState->isLoaded = TRUE;
    closeFile(file);
    printLoad(gameState);
    printf("File konfigurasi berhasil diload. PURRMART siap digunakan.\n");
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
        users->money = users[userIndex].money;

    }
    else {
        printf("Username atau password salah. Silakan coba lagi.\n");
    }

}

void Logout(User *users, int user_count) {
    printf("%s telah logout dari sistem PURRMART. Silakan REGISTER/LOGIN kembali untuk melanjutkan.\n", currentUser);
    currentUser[0] = '\0';  // Clear the currentUser string
}

void Register(GameState *gameState) {
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
    gameState->userCount++;

    printf("Akun dengan username %s telah berhasil dibuat.\n", userstr);
    printf("Silakan LOGIN untuk melanjutkan.\n");
}

void Save(const char *filename, GameState *gameState) {
    if (!gameState->isLoaded && !gameState->isStarted) {
        printf("Game belum dimulai. Tidak ada data yang disimpan.\n");
        return;
    }
    if (filename == NULL || *filename == '\0') {
        printf("Nama file tidak valid.\n");
        return;
    }

    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = openFile(filepath, "w");
    if (file == NULL) {
        printf("Gagal membuat file save.\n");
        return;
    }

    writeLen(file, "%d\n", gameState->itemList.itemLength);

    for (int i = 0; i < gameState->itemList.itemLength; i++) {
        writeItem(file, "%d %s\n", 
            gameState->itemList.item[i].price,
            gameState->itemList.item[i].name);
    }

    writeLen(file, "%d\n", gameState->userCount);

    for (int i = 0; i < gameState->userCount; i++) {
        writeUser(file, "%d %s %s\n",
            gameState->users[i].money,
            gameState->users[i].name,
            gameState->users[i].password);
    }

    closeFile(file);
    printf("Game berhasil disimpan dalam %s.\n", filepath);
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

void insertLastItem(ListItem *itemlist, Item item){
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
    }
}

void makeListItem(GameState *gameState) {
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
void printLoad(GameState *gameState) {
    printf("\n=== Testing Game State ===\n");
    
    if (gameState->itemList.itemLength == 0) {
        printf("Tidak ada item.\n");
    } else {
        for (int i = 0; i < gameState->itemList.itemLength; i++) {
                printf("%d. %s (Harga: %d)\n", 
                    i + 1, 
                    gameState->itemList.item[i].name, 
                    gameState->itemList.item[i].price);
        }
    }
    
    
    printf("\nDaftar User (%d user):\n", gameState->userCount);
    if (gameState->userCount == 0) {
        printf("Tidak ada user terdaftar.\n");
    } else {
        for (int i = 0; i < gameState->userCount; i++) {
            printf("%d. Username: %s, Password: %s, Saldo: %d\n", 
                   i + 1, 
                   gameState->users[i].name, 
                   gameState->users[i].password, 
                   gameState->users[i].money);
        }
    }

    printf("\nStatus Inisialisasi: %s\n", 
           gameState->isLoaded ? "Sudah Terinisialisasi" : "Belum Terinisialisasi");
}

// Work

void delay(int seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds);
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

    printf(">> WORK\nDaftar pekerjaan:\n"); //print daftar pekerjaan yang tersedia
    for(int i = 0; i < workCount; i++){
        printf("%d. %s (pendapatan: %d, durasi: %ds)\n", i+1, workList[i].workName, workList[i].workPayment, workList[i].workDuration);
    }

    boolean validWork = FALSE; //inisialisasi
    char selectedWork[100];
    int selectedWorkIndex;

    while(!validWork){
        printf("\nPilih nama pekerjaan: ");
        STARTWORD(); //baca input
        collectInput(selectedWork);

        for (int i = 0; i < workCount; i++){ //cek apakah pekerjaan yang dipilih valid
            if (my_strcmp(selectedWork, workList[i].workName) == 0){ //jika valid
                validWork = TRUE;
                selectedWorkIndex = i;
                break;
            }
        }
        if (!validWork){ //jika tidak valid, kembali ke loop, input lagi
            printf("Pekerjaan tidak valid, silakan coba lagi. "); 
        }
    }

    printf("Anda sedang bekerja sebagai %s. Harap tunggu...\n", selectedWork);
    delay(workList[selectedWorkIndex].workDuration);
    printf("Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n", workList[selectedWorkIndex].workPayment);

    balance += workList[selectedWorkIndex].workPayment;
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
            printf("%d. %s\n", i + 1, L->item[i].name);
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
