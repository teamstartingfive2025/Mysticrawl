#pragma once
#include <string>
#include <vector>
#include <map>
#include "UI.h"
#include "Enemy.h"
#include "Interactable.h"
#include "Item.h"
using namespace std;
// Forward declaration to break circular dependency
class Enemy;
class Room;

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
        : direction(direction), destination(destination), locked(locked) {}
	string getDirection() const { return direction; }
    Room* getDestination() const { return destination; }
    bool isLocked() const { return locked; }
    void unlock();
};

/**
 * Represents a single room in the dungeon.
 * Each room can contain items, a description, exits to other rooms,
 * and an optional locked state (for doors or passages).
 */
class Room : public Interactable {
private:
    string name;                       // Room name (displayed in look())
    string description;                // Narrative description of the room
    vector<shared_ptr<Item>> items;              // visable Items currently in the room
    vector<shared_ptr<Item>> hiddenItems;        // Items that must be discovered by investigation
    vector<Exit> exits;          // Adjacent rooms by direction (e.g., "east")
	vector<Enemy*> enemies;        // Enemies present in the room

public:
    Room(string name, string description, vector<shared_ptr<Item>> items = {}, vector<shared_ptr<Item>> hiddenItems = {});

    void setExits(const vector<Exit>& exits);
    Exit* getExit(const string& exitName);
    const vector<Exit>& getExits() const { return exits; }

	string getName() const { return name; }
	string getDescription() const { return description; }

    vector<shared_ptr<Item>>& getItems() { return items; }
    vector<shared_ptr<Item>>& getHiddenItems() { return hiddenItems; }

    const vector<shared_ptr<Item>>& getItems() const { return items; }
    const vector<shared_ptr<Item>>& getHiddenItems() const { return hiddenItems; }

    void addItem(const shared_ptr<Item>& item) { items.push_back(item); }
    void addHiddenItem(const shared_ptr<Item>& item) { hiddenItems.push_back(item); }
    void clearHiddenItems() { hiddenItems.clear(); }

    void addEnemy(Enemy* enemy) { enemies.push_back(enemy); }
    vector<Enemy*>& getEnemies() { return enemies; }
};

/**
 * Starts the dungeon gameplay loop.
 * Handles room navigation, interaction, and the lock/unlock system.
 */
void StartDungeon();