#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <stdlib.h>

struct Enemy
{
    int hp;
    int attack;
    int defense;
} typedef ENEMY;


ENEMY* makeEnemy(int, int);
int calculateHP(int,int);
int calculateAttack(int,int);
int calculateDefense(int,int);

#endif // _ENEMY_H_
