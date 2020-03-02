#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "item.h"

typedef struct Member MEMBER;
struct Member
{
    ITEM *item;
    MEMBER *next;
};

typedef struct Inventory INVENTORY;
struct Inventory
{
    MEMBER *first;
    MEMBER *last;
    int size;
};

//public
INVENTORY *makeInventory();
void insertItem(INVENTORY*,ITEM*);
//private (but public because C)
int isEmpty(INVENTORY*);
MEMBER *makeMember(ITEM*);
void insertMember(INVENTORY*,MEMBER*);
void destroyInventory(INVENTORY*);

#endif // _INVENTORY_H_
