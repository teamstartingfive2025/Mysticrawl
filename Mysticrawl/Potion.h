#pragma once
#include <string>
#include "Item.h"

class Potion : public Item {
private:
	bool consumable = true;
	int healing;
public:
	Potion(string name, const int healing) : Item(name), healing(healing) {}
	void use(Player* player);
};
