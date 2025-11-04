#include <iostream>
#include "Key.h"
#include "Exit.h"
using namespace std;

void Key::unlockExit() {
	if (exitKeyUnlocks != nullptr && exitKeyUnlocks->isLocked()) {
		exitKeyUnlocks->unlock();
		cout << "You use the " << getName() << " to unlock the " << exitKeyUnlocks->getDirection() << " exit.\n";
	}
}