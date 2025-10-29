#pragma once

#include <string>
using namespace std;

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
	virtual void use(Player* player) { cout << "Nothing happened."; return; }
	bool consumable() const { return consumable; }
};