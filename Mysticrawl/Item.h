#pragma once

#include <string>
using namespace std;

/**
 * Item base class for any item in the game.
 */
class Item {
private:
	string name;
	bool consumable = false;
protected:
	void setConsumable(bool c) { consumable = c; }
public:
	Item(const string name) : name(name) {}
	virtual string getName() const { return name; }
	bool consumable() const { return consumable; }
};