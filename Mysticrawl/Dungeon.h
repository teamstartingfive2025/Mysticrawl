#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

/**
 * Represents a single room in the dungeon.
 * Each room can contain items, a description, exits to other rooms,
 * and an optional locked state (for doors or passages).
 */
struct Room {
    string name;                       // Room name (displayed in look())
    string description;                // Narrative description of the room
    vector<string> items;              // visable Items currently in the room
    vector<string> hiddenItems;        // Items that must be discovered by investigation
    map<string, Room*> exits;          // Adjacent rooms by direction (e.g., "east")
    bool locked = false;               // Whether the room's exit is locked
};

/**
 * Starts the dungeon gameplay loop.
 * Handles room navigation, interaction, and the lock/unlock system.
 */
void StartDungeon();