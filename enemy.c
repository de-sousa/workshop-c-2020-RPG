#include "enemy.h"

ENEMY *makeEnemy(int race, int class)
{
    ENEMY *enemy = malloc(sizeof(ENEMY));
    enemy->hp = calculateHP(race,class);
    enemy->attack = calculateAttack(race,class);
    enemy->defense = calculateDefense(race,class);
    return enemy;
}

int calculateHP(int race,int class)
{
    return 10*class + 5*race + 50;
}

int calculateAttack(int race,int class)
{
    return 4*class + race;
}

int calculateDefense(int race,int class)
{
    return 2*class + race;
}

void destroyEnemy(ENEMY *enemy)
{
    free(enemy);
}
