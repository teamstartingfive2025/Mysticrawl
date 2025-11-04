#pragma once
#include "Item.h"
#include "Dungeon.h"
#include "Exit.h"

/**
 * Key item that can unlock a specific exit in the dungeon.
 */
class Key : public Item {
private:
	Exit* exitKeyUnlockDestination;
public:
	Key() {}
	Key(string name, Exit* exitKeyUnlockDestination) 
		: Item(name), exitKeyUnlockDestination(exitKeyUnlockDestination) {}
	void printUnlockText();
	void setExitKeyUnlockDestination(Exit *exitKeyUnlockDestination) { 
		this->exitKeyUnlockDestination = exitKeyUnlockDestination;
	}
};