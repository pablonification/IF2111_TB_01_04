#ifndef MAIN_H
#define MAIN_H

#include "../ADT/boolean.h"
#include "../ADT/queue.h"
#include "../ADT/list.h"
#include "../ADT/mesinkarakter.h"
#include "misc.h"
#include "wordl32.h"
#include "rng.h"
#include "qwordl3.h"
#include "DNA.h"

#define MAX_LEN 50
#define MAX_USERS 100

extern char currentUser[MAX_LEN];

typedef struct{
    char name[MAX_LEN];
    char password[MAX_LEN];
    int money;
} User;

typedef struct{
    char name[MAX_LEN];
    int price;
} Item;

typedef struct {
    Item item[MaxEl];
    int itemLength;
} ListItem;

typedef struct {
    ListItem itemList;
    User users[MAX_LEN];
    int userCount;
    QueueItem requestQueue;
    boolean isStarted;
    boolean isLoaded;
    boolean isLogin;
} Global;

// typedef struct{
//     char workName[100]; // nama pekerjaan
//     int workPayment;    // gaji
//     int workDuration;   // durasi kerja
// } Work;

void showMainMenu();
boolean Start(Global *Global);
void Load(const char *filename, Global *Global);
boolean loadGlobal(Global *Global, const char *filename);
void Login(User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
void Register(Global *Global);
void Save(const char *filename, Global *Global);
void Logout(User *users, int user_count);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);
void insertLastItem(ListItem *itemlist, Item item);
void makeListItem(Global *Global);

void printLoad(Global *Global);

// work
unsigned my_strlen(char *str);

boolean my_strcmp(char *str1, char *str2);

void delay(int seconds);

void collectInput(char *input);

void work(int *balance);

// store
void storeList (ListItem *L);
// I.S List bisa saja kosong
// F.S Jika list kosong, mencetak "TOKO KOSONG"
// Jika list tidak kosong, mencetak seluruh barang yang ada di toko

void storeRemove(ListItem *L);

void storeRequest (ListItem *L, QueueItem *Q);

void storeSupply(ListItem *L, QueueItem *Q);

boolean IsEmptyItem(ListItem *L);

void DeleteAtItem(ListItem *L, IdxType i);

IdxType LastIdxItem(ListItem L);

boolean SearchItem(ListItem L, char *X);

boolean isWordInt(Word w);

#endif