#include <stdlib.h>

#include "inventory.h"
#include "item.h"

INVENTORY* makeInventory()
{
    INVENTORY* inventory = (INVENTORY*)malloc(sizeof(INVENTORY));
    inventory -> first = NULL;
    inventory -> last = NULL;
    inventory -> size = 0;
    return inventory;
}

MEMBER* makeMember(ITEM* item)
{
    MEMBER* member = (MEMBER*) malloc(sizeof(MEMBER));
    member -> item = item;
    member -> next = NULL;
    return member;
}

void insertItem(INVENTORY* inventory,ITEM* item)
{
    insertMember(inventory, makeMember(item));
}

void insertMember(INVENTORY* inventory, MEMBER* member)
{
    if (isEmpty(inventory))
    {
        inventory -> first = member;
        inventory -> last = member;
    }
    else
    {
        inventory -> last -> next = member;
    }
    inventory -> size += 1;
}

int isEmpty(INVENTORY* inventory)
{
    int flag;

    flag = (inventory -> size == 0)? 1 : 0;

    return flag;
}