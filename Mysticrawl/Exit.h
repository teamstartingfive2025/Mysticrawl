#pragma once

#include "Room.h"
#include <string>
using namespace std;

/**
 * Represents an exit to a dungeon room.
 * Each exit contains a direction (Ex: north, east, ...),
 * whether that exit is locked, and where it leads.
 */
class Exit {
private:
    string direction;
    bool locked;
    Room* destination;
public:
    Exit(string direction, Room* destination, bool locked = false)
        : direction(direction), destination(destination), locked(locked) {
    }
    string getDirection() const { return direction; }
    Room* getDestination() const { return destination; }
    bool isLocked() const { return locked; }
    void unlock();
};