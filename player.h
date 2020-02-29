#ifndef _PLAYER_H_
#define _PLAYER_H_

#define INITIAL_DAMAGE 10
#define INITIAL_CRIT_CHANCE 0.1
#define INITIAL_DEFENSE 9

#include <stdlib.h>
#include "item.h"
#include "inventory.h"

struct Player
{
    char* name;
    int hp;
    INVENTORY* inventory;
    int wallet;
    ITEM* left_hand;
    ITEM* right_hand;   
} typedef PLAYER;


PLAYER* makePlayer(char*);
int calculateCritical(PLAYER*);
float critHands(PLAYER*);
int damageHands(PLAYER*);
int defenseHands(PLAYER*);

#endif