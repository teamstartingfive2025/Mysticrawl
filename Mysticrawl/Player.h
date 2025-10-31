#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Interactable.h"
#include "Item.h"
using namespace std;

// Forward declarations to avoid circular dependency
class Enemy;
class Room;

/**
 * The Player class represents the user-controlled character.
 * It tracks the player's current room, inventory, and provides methods
 * for interacting with the dungeon world.
 */
class Player : public Interactable {
private:
    Room* currentRoom;            // Pointer to the room the player is currently in
    vector<shared_ptr<Item>> inventory;     // List of items collected by the player
    std::string playerName;
    int health;
    int maxHealth;

    bool skipNextEnemyTurn = false;

    bool calculateRunChance() const;


public:
    // Constructor initializes the player at the starting room
    // updated constructor (initialize maxHealth to starting health)
    Player(Room* currentRoom, string name, int health)
        : currentRoom(currentRoom), playerName(name), health(health), maxHealth(health) {
    }

    Player(const Player&) = delete; // Disable copy constructor
    static Player& GetInstance(); // Singleton access method

    // New health-related accessors/mutators
    int getMaxHealth() const;
    bool isAlive() const;

    // takeDamage applies positive damage to the player, clamps at 0, and returns the actual damage applied
    int takeDamage(int amount);

    // heal increases health up to maxHealth and returns amount healed
    int heal(int amount);

    // optional: set current health directly (clamped)
    void setHealth(int hp);

    // optional: change player's maximum health (adjusts current health if needed)
    void setMaxHealth(int newMax);

    // Describes the current room and visible items
    void look() const;

    // Allows the player to move between rooms
    void move();

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

    // accessors for the per-player skip flag
    void setSkipNextEnemyTurn(bool v) { skipNextEnemyTurn = v; }
    bool shouldSkipNextEnemyTurn() const { return skipNextEnemyTurn; }

    // changeHealth accepts positive (heal) or negative (damage) values
    void changeHealth(int delta) { health += delta; }

    // convenience: apply damage (positive amount)
    void applyDamage(int amount) { changeHealth(-amount); }

    //view healthbar
    void displayHealthBar(int width = 20) const;
    
    // Performs a basic attack with bare hands against an enemy.
    void basicAttack(Enemy& target, Room& currentRoom);
    // Try to flee to a specific destination room while enemies are present.
    // Returns true if moved, false if blocked by failed flee.
    bool attemptFleeTo(Room* destination);
};