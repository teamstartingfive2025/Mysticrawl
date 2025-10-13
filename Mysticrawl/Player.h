#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Forward declaration to avoid circular dependency with Dungeon.h
struct Room;

/**
 * The Player class represents the user-controlled character.
 * It tracks the player's current room, inventory, and provides methods
 * for interacting with the dungeon world.
 */
class Player {
private:
    Room* currentRoom;            // Pointer to the room the player is currently in
    vector<string> inventory;     // List of items collected by the player
    std::string playerName;
    int health;

public:
    // Constructor initializes the player at the starting room
    Player(Room* currentRoom, string name, int health)
        : currentRoom(currentRoom), playerName(name), health(health) {}

    // Describes the current room and visible items
    void look() const;

    void investigate();  // Search the current room for hidden items

    // Picks up an item from the room (if available)
    void pickup();

    // Displays all items the player has collected
    void showInventory() const;

    // Checks if the player currently has a specific item
    bool hasItem(const string& itemName) const;

    // Accessor and mutator for the current room pointer
    Room* getCurrentRoom() const;
    void setCurrentRoom(Room* room);

    int getHealth() const { return health; }
    const std::string& getName() const { return playerName; }

    // changeHealth accepts positive (heal) or negative (damage) values
    void changeHealth(int delta) { health += delta; }

    // convenience: apply damage (positive amount)
    void applyDamage(int amount) { changeHealth(-amount); }
};