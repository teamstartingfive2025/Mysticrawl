#pragma once
#include "Item.h"
#include "Dungeon.h"

/**
 * Key item that can unlock a specific exit in the dungeon.
 */
class Key : public Item {
private:
	Exit* exitKeyUnlocks;
public:
	Key(string name, Exit* exitKeyUnlocks) : Item(name), exitKeyUnlocks(exitKeyUnlocks) {}
	void unlockExit();
};