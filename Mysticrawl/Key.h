#pragma once
#include "Item.h"
#include "Dungeon.h"

class Key : public Item {
private:
	Exit* exitKeyUnlocks;
public:
	Key(string name, Exit* exitKeyUnlocks) : Item(name), exitKeyUnlocks(exitKeyUnlocks) {}
	void unlockExit();
};