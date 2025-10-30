#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Potion.h"
#include <string>
using namespace std;

void Potion::use(Player* player) {
	player->heal(healing);
	cout << "\nHealed " << healing << " hit points";
}
