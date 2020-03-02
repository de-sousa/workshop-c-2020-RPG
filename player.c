#include "player.h"


PLAYER *makePlayer(char *name)
{
    PLAYER *player = malloc(sizeof(PLAYER));
    player -> name = name;
    player -> hp = 100;
    player -> inventory = makeInventory();
    player -> wallet = 0;
    player -> left_hand = makeWeapon(INITIAL_DAMAGE,INITIAL_CRIT_CHANCE);
    player -> right_hand = makeShield(INITIAL_DEFENSE);
    insertItem(player -> inventory, player -> left_hand);
    insertItem(player -> inventory, player -> right_hand);

    return player;
}

int calculateCritical(PLAYER *player)
{
    return (critHands(player)<=((float)rand()/RAND_MAX))?1:0;
}

float critHands(PLAYER *player)
{
    float chance = 0;
    if (player->left_hand->flag == WEAPON)
        chance = 1.0-((1.0-chance)*(1.0-player->left_hand->Union.Weapon.crit_chance));
    if (player->right_hand->flag == WEAPON)
        chance = 1.0-((1.0-chance)*(1.0-player->right_hand->Union.Weapon.crit_chance));
    return chance;
}

int damageHands(PLAYER *player)
{
    int damage = 0;
    if(player->left_hand->flag == WEAPON)
        damage += player->left_hand->Union.Weapon.damage;
    if(player->right_hand->flag == WEAPON)
        damage += player->right_hand->Union.Weapon.damage;
    return damage;
}

int defenseHands(PLAYER *player)
{
    int defense = 0;
    if (player->left_hand->flag == SHIELD)
        defense += player->left_hand->Union.Shield.defense;
    if (player->right_hand->flag == SHIELD)
        defense += player->right_hand->Union.Shield.defense;
    return defense;
}

void destroyPlayer(PLAYER *player)
{
    // Carlos: I don't remember if doing free(player) would free
    //       everything inside it as well, so I prefer to free
    //       everything dynamically allocated inside first.
    destroyInventory(player->inventory);
    free(player);
}
