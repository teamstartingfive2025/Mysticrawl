#pragma once

#include <string>
using namespace std;

/**
 * Item base class for any item in the game.
 */
class Item {
private:
	string name;
public:
	Item(const string name) : name(name) {}
	virtual string getName() const { return name; }
};