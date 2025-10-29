#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Potion.h"
#include <string>

void Potion::use(Player* player) {
	player->heal(healing);
}
