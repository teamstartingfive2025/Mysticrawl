#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Interactable.h"
#include "Item.h"
#include "SimpleMechanism.h"
using namespace std;

// Forward declarations to avoid circular dependency
class Enemy;
class Room;
class Item;

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
    int defenceTurns = 0; // How many turns the player has before attack
    int defenceCooldown = 0; // How many turns the player has until they can defend
public:
    // Constructor initializes the player at the starting room
    // updated constructor (initialize maxHealth to starting health)
    Player(Room* currentRoom, string name, int health)
        : currentRoom(currentRoom), playerName(name), health(health), maxHealth(health) {
    }

    // LV - true Singleton design pattern makes the constructor private, attribution?
    Player(const Player&) = delete; // Disable copy constructor
    static Player& GetInstance(); // Singleton access method

    // New health-related accessors/mutators
    int getMaxHealth() const;
    bool isAlive() const;

    // takeDamage applies positive damage to the player, clamps at 0, and returns the actual damage applied
    int takeDamage(int amount);

    void setDefenceTurns(int turns);
    int getDefenceTurns() const { return defenceTurns; }
    bool isDefending() const;

    void setDefenceCooldown(int amount);
    int getDefenceCooldown() const { return defenceCooldown; }
    void decrementDefenceCooldown();

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
    
    void interact();
    // Displays selection menu of all items the player has collected
    shared_ptr<Item> itemSelectMenu();

    // Manages item usage
    void useItem(shared_ptr<Item> item);

    bool inventoryEmpty();

    // Checks if the player currently has a specific item
    bool hasItem(const shared_ptr<Item> itemPointer) const;

    // Accessor and mutator for the current room pointer
    Room* getCurrentRoom() const;
    void setCurrentRoom(Room* room);

    int getHealth() const { return health; }
    const string& getName() const { return playerName; }

    // changeHealth accepts positive (heal) or negative (damage) values
    void changeHealth(int delta) { health += delta; }

    //view healthbar
    void displayHealthBar(int width = 20) const;
    
    // Performs a basic attack with bare hands against an enemy.
    void basicAttack(Enemy& target, Room& currentRoom);
};