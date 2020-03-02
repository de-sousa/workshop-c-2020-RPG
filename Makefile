compile : item.h item.c inventory.h inventory.c enemy.h enemy.c player.h player.c rpg.c
	gcc -Wall -o rpg item.c inventory.c enemy.c player.c rpg.c

clean :
	rm rpg
