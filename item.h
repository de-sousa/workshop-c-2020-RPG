#ifndef _ITEM_H_
#define _ITEM_H_

struct Item
{
    enum {WEAPON,SHIELD} flag;
    union
    {
        struct
        {
            int damage;
            float crit_chance;
        } Weapon;
        struct
        {
            int defense;
        } Shield;
        
    } Union;
    
} typedef ITEM;

ITEM *makeWeapon(int,float);
ITEM *makeShield(int);
void destroyItem(ITEM*);

#endif // _ITEM_H_
