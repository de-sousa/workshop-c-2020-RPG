#include <stdlib.h>

#include "item.h"

ITEM* makeWeapon(int damage, float crit_chance)
{
    ITEM* item = (ITEM*)malloc(sizeof(ITEM));
    item->flag = WEAPON;
    item->Union.Weapon.damage = damage;
    item->Union.Weapon.crit_chance = crit_chance;
    return item;
}

ITEM* makeShield(int defense)
{
    ITEM* item = (ITEM*)malloc(sizeof(ITEM));
    item->flag = SHIELD;
    item->Union.Shield.defense = defense;
    return item;
}
