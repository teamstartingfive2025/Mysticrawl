#include "Room.h"
#include "Exit.h"

Room::Room(string name, string description, vector<shared_ptr<Item>> items, vector<shared_ptr<Item>> hiddenItems)
    : name(name), description(description), items(items), hiddenItems(hiddenItems) {
}

void Room::setExits(const vector<Exit>& exits) {
    this->exits = exits;
}

Exit* Room::getExit(const string& exitName) {
    for (auto& exit : exits) { // remove const
        if (exit.getDirection() == exitName) {
            return &exit;
        }
    }
    return nullptr;
}

// addMechanism()
// Adds a new lever or button to the room’s mechanism list.
void Room::addMechanism(shared_ptr<SimpleMechanism> mech) {
    mechanisms.push_back(mech);
}

// getMechanisms()
// Returns all mechanisms currently in the room.
// Used by the player when they look or interact.
const vector<shared_ptr<SimpleMechanism>>& Room::getMechanisms() const {
    return mechanisms;
}