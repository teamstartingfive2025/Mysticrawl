#pragma once
#include "Constants.h"

// Returns false if the game should end (player HP <= 0).
// Returns true if the game should continue (return to dungeon flow).
bool EndOfBattle(Player& player);