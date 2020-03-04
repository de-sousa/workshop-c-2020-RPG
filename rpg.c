#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "item.h"
#include "inventory.h"
#include "enemy.h"
#include "player.h"

#define MAX_NAME 50
#define NUM_RACES 1
#define NUM_CLASSES 5
#define NUM_OPTIONS 3
#define MAX_HP 200

const char *RACES[NUM_RACES] = {"Bug"};
const char *CLASSES[NUM_CLASSES] = {"Minion","Soldier","Sergeant","Commander","King"};
const char *OPTIONS[NUM_OPTIONS] = {"Attack", "Defend, Plan and Organize", "Analyze Inventory"};


void printPlayerCommand()
{
    printf(">>  ");
    fflush(stdout);
}

void printNarratorCommand()
{
    printf("||  ");
    fflush(stdout);
}

void printPrompt()
{
    printNarratorCommand();
    puts("You live in a fantastic world filled with rainbows and happiness.");
    printNarratorCommand();
    puts("But, one day the BUGS appeared!");
    printNarratorCommand();
    puts("You grab your Shield and Sword, and off you go on an adventure.");
}

char* getName()
{
    printNarratorCommand();
    printf("What's your name? (maximum %d characters)\n", MAX_NAME);
    char *name = malloc(sizeof(char) * MAX_NAME);
    printPlayerCommand();
    scanf("%s", name);
    return name;
}

void printLine()
{
    printNarratorCommand();
    puts("--------------------------------------------------------");
}

char getOption()
{
    printNarratorCommand();
    printf("What are you going to do?\n");
    for (int option = 0; option < NUM_OPTIONS; option++)
    {
        printNarratorCommand();
        printf("%d) %s\n", option, OPTIONS[option]);
    }
    char option;
    printNarratorCommand();
    putchar('\n');
    printPlayerCommand();
    scanf(" %c", &option);
   
    char ch;
    while ((ch = getchar()) != '\n');
    
    return option;
}

void playerAttack(PLAYER *player, ENEMY *enemy)
{
    printNarratorCommand();
    printf("You are attacking!\n");
    int critical = calculateCritical(player);
    int damage = damageHands(player);
    if(critical)
    {
        damage *= 2;
        enemy->hp -= damage;
        printNarratorCommand();
        printf("Critical!\n");
    }
    else
    {
        damage = ((damage-enemy->defense)>0)?damage-enemy->defense:1;
        enemy->hp -= damage;
    }    
    printNarratorCommand();
    printf("You have dealt %d damage.\n", damage);
}

void playerDefend(PLAYER *player)
{
    printNarratorCommand();
    printf("You are defending!\n");
    int health = defenseHands(player);
    health = (health>0)?health:1;
    player->hp += health;
    int remainder = 0;
    if(player->hp > MAX_HP)
    {
        remainder = player->hp - MAX_HP;
        player->hp = MAX_HP;
    }
    printNarratorCommand();
    printf("You have regained %d hp points.\n", health - remainder);
}

void listInventory(PLAYER *player)
{
    printNarratorCommand();
    printf("Your inventory has:\n");
    MEMBER *iterator = player->inventory->first;
    while(iterator != NULL)
    {
        if (iterator->item->flag == WEAPON)
        { 
            printNarratorCommand();
            printf("> Weapon with damage %d and critical chance %f\n", iterator->item->Union.Weapon.damage, iterator->item->Union.Weapon.crit_chance);
        }
        else
        {
            printNarratorCommand();
            printf("> Shield with defense %d\n", iterator->item->Union.Shield.defense);
        }
        iterator = iterator->next;        
    }
}

void playerTurn(PLAYER *player, ENEMY *enemy)
{
    while(1){           
        int chose = 0;
        
        printLine();
        printNarratorCommand();
        printf("YOU : %d HP ---  %d HP : ENEMY\n", player->hp, enemy->hp);
        char option = getOption();
        printLine();
        switch (option)
        {
            case '0':
                chose = 1;
                playerAttack(player, enemy);
                break;
            case '1':
                chose = 1;
                playerDefend(player);
                break;
            case '2':
                listInventory(player);
                break;
            default:
                printNarratorCommand();
                printf("Can you repeat?\n");
                break;
        }
        if (chose) break;
    }
}

void enemyTurn(ENEMY *enemy, PLAYER *player)
{
    int defense = defenseHands(player);
    int damage = ((enemy->attack - defense)>0)?enemy->attack-defense:1;
    player->hp -= damage;
    printNarratorCommand();
    printf("The enemy has dealt %d damage\n", damage);
}

int fight(PLAYER *player, ENEMY *enemy)
{
    while(1){
        playerTurn(player,enemy);
        if((enemy->hp) <= 0)
            return 1;
        enemyTurn(enemy,player);
        if((player->hp) <= 0)
            return 0;
    }
}

int main(int argc, char **argv)
{
    srand(time(0));
    PLAYER *player = makePlayer(getName());
    printLine();
    printPrompt();
    printLine();
    int result = 1;
    for(int race = 0; race < NUM_RACES; race++)
    {
        for (int class = 0; class < NUM_CLASSES; class++)
        {
            printNarratorCommand();
            printf("A %s %s appears!\n", RACES[race], CLASSES[class]);
            ENEMY *enemy = makeEnemy(race,class);
            result = fight(player,enemy);
            free(enemy);
            if(!result) break;
            else
            {
                printNarratorCommand();
                printf("The %s %s died!\n", RACES[race], CLASSES[class]);
            }
            printLine();
        }
        if(!result) break;
        //INSERT POSSIBILITY TO BUY ITEMS AND EQUIP THEM
    }

    if(result)
    {
        printNarratorCommand();
        printf("Congratulations %s! You won the game!\n", player -> name);
    }
    else
    {
        printNarratorCommand();
        printf("You lost :( Better luck next time\n");
    }
    destroyPlayer(player);

    return EXIT_SUCCESS;
}
