#pragma once

#include "Room.h"
#include <string>
#include <tuple>
#include <functional>
#include <variant>

using namespace std;

/**
 * Represents an exit to a dungeon room.
 * Each exit contains a direction (Ex: north, east, ...),
 * whether that exit is locked, and where it leads.
 */
class Exit {
private:
    string direction;
    // Keeps track of keys used to unlock this exit and the unlock status
    vector<function<bool()>> lockStatusFunctions;
    Room* destination;
public:
    Exit(string direction, Room* destination, vector<function<bool()>> lockStatusFunctions = {}) :
        direction(direction), destination(destination), lockStatusFunctions(lockStatusFunctions) {
    }

    string getDirection() const { return direction; }
    Room* getDestination() const { return destination; }
    bool isLocked() const;
    void addLock(function<bool()> lock) { lockStatusFunctions.push_back(lock); };
};