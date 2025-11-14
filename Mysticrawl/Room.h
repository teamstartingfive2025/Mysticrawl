#pragma once

#include "Interactable.h"
#include "Item.h"
#include "Enemy.h"
#include "Exit.h"
#include "Container.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

class Exit;

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
    vector<shared_ptr<SimpleMechanism>> mechanisms;
    vector<Container> containers;

public:
    Room(string name, string description, vector<shared_ptr<Item>> items = {}, vector<shared_ptr<Item>> hiddenItems = {});

    void setExits(const vector<Exit>& exits);
    Exit* getExit(const string& exitName);
    const vector<Exit>& getExits() const { return exits; }
    vector<Exit>& getExits() { return exits; }

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

    void addMechanism(shared_ptr<SimpleMechanism> mech);
    const vector<shared_ptr<SimpleMechanism>>& getMechanisms() const;

    vector<Container>& getContainers() { return containers; }
    const vector<Container>& getContainers() const { return containers; }
	void addContainer(const Container& container) { containers.push_back(container); }
};