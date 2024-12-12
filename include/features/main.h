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
#include "bonus2.h"

#define MAX_LEN 50
#define MAX_USERS 100

extern char currentUser[MAX_LEN];

typedef struct {
    char name[MAX_LEN];
    char password[MAX_LEN];
    int money;
    int purchaseCount;
    int wishlistCount;
    struct {
        int cost;
        char itemName[MAX_LEN];
    } purchaseHistory[MaxEl];
    char wishlist[MaxEl][MAX_LEN];
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
    User users[MAX_USERS];
    int userCount;
    QueueItem requestQueue;
    boolean isStarted;
    boolean isLoaded;
    boolean isLogin;
} GameState;

// typedef struct{
//     char workName[100]; // nama pekerjaan
//     int workPayment;    // gaji
//     int workDuration;   // durasi kerja
// } Work;

void showMainMenu();
boolean Start(GameState *gameState);
void Load(const char *filename, GameState *gameState);
void Login(GameState *gameState, User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
void Register(GameState *gameState);
void Save(const char *filename, GameState *gameState);
void Logout(User *users, int user_count);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);
void insertLastItem(ListItem *itemlist, Item item);
void makeListItem(GameState *gameState);

void printLoad(GameState *gameState);

// store
void storeList (ListItem *L);
void storeRemove(ListItem *L);
void storeRequest (ListItem *L, QueueItem *Q);
void storeSupply(ListItem *L, QueueItem *Q);
boolean IsEmptyItem(ListItem *L);
void DeleteAtItem(ListItem *L, IdxType i);
IdxType LastIdxItem(ListItem L);
boolean SearchItem(ListItem L, char *X);
boolean isWordInt(Word w);
unsigned my_strlen( char *str);
boolean my_strcmp( char *str1,  char *str2);

#endif
