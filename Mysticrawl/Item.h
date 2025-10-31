#pragma once

#include <string>
#include "Player.h"
using namespace std;

//declaration to avoid circular dependency
class Player;

/**
 * Item base class for any item in the game.
 */
class Item {
private:
	string name;
protected:
	void setConsumable(bool c) { consumable = c; }
	bool consumable = false;
public:
	Item(const string name) : name(name) {}
	virtual string getName() const { return name; }
	virtual void use(Player* player) { cout << "Nothing happened.\n"; return; }
	bool isConsumable() const { return consumable; }
};