#pragma once

#include "Room.h"
#include "Lockable.h"
#include <string>
#include <tuple>
#include <functional>
#include <vector>

using namespace std;

/**
 * Represents an exit to a dungeon room.
 * Each exit contains a direction (Ex: north, east, ...),
 * whether that exit is locked, and where it leads.
 */
class Exit : public Lockable {
private:
    string direction;
    Room* destination;
public:
    Exit(string direction, Room* destination, vector<function<bool()>> lockStatusFunctions = {}) :
        Lockable(lockStatusFunctions), direction(direction), destination(destination) {}

    string getDirection() const { return direction; }
    Room* getDestination() const { return destination; }
};