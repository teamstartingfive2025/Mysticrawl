#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Potion.h"
#include <string>

class Potion : public Item {
private:
	int healing;
public:
	Potion(string name, const int healing) : Item(name), healing(healing) { setConsumable(true); }
	void use(Player* player) override {
		player->heal(healing);
		cout << "Healed " << healing << "hit points";
	}
};
