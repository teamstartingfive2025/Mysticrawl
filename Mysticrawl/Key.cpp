#include <iostream>
#include "Key.h"
#include "Exit.h"
#include "Lockable.h"

using namespace std;

void Key::printUnlockText() {
	if (exitKeyUnlockDestination != nullptr && exitKeyUnlockDestination->isLocked()) {
		cout << "You use the " << getName() << " to unlock the " << exitKeyUnlockDestination->getDirection() << " exit.\n";
	}
}