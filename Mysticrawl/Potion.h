#pragma once
#include <string>
#include "Item.h"

class Potion : public Item {
private:
	int healing;
public:
	Potion(string name, const int healing) : Item(name), healing(healing) { setConsumable(true); }
	void use(Player* player);
};
