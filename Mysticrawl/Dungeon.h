#pragma once
#include <string>
#include <vector>
#include <map>
#include "Enemy.h"
#include "Interactable.h"
#include "Item.h"
using namespace std;
// Forward declaration to break circular dependency


/**
 * Starts the dungeon gameplay loop.
 * Handles room navigation, interaction, and the lock/unlock system.
 */
void StartDungeon();