#include "Player.h"
#include "Dungeon.h"

// Initializes the player in a starting room
Player::Player(Room* startRoom) : currentRoom(startRoom) {}

// Prints details about the current room and visible items
void Player::look() const {
    cout << "\n== " << currentRoom->name << " ==\n";
    cout << currentRoom->description << "\n";

    if (!currentRoom->items.empty()) {
        cout << "You see:\n";
        for (const auto& i : currentRoom->items)
            cout << " - " << i << "\n";
    }
    else {
        cout << "Nothing special here.\n";
    }
}

void Player::investigate() {
    if (currentRoom->hiddenItems.empty()) {
        cout << "You search the area but find nothing unusual.\n";
        return;
    }

    cout << "You carefully search the room and discover:\n";
    for (const auto& item : currentRoom->hiddenItems) {
        cout << " - " << item << "\n";
        currentRoom->items.push_back(item); // Move to visible items
    }
    currentRoom->hiddenItems.clear();
}

// Picks up the first item available in the current room
void Player::pickup() {
    if (currentRoom->items.empty()) {
        cout << "There’s nothing to pick up here.\n";
        return;
    }
    cout << "\nItems available to pick up:\n";
    for (size_t i = 0; i < currentRoom->items.size(); ++i) {
        cout << i + 1 << ". " << currentRoom->items[i] << "\n";
    }

    cout << "Enter the number of the item you want to pick up: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > static_cast<int>(currentRoom->items.size())) {
        cout << "Invalid choice. No item picked up.\n";
        return;
    }

    // Pick up the selected item
    string item = currentRoom->items[choice - 1];
    cout << "You pick up the " << item << ".\n";

    // Add to player inventory and remove from room
    inventory.push_back(item);
    currentRoom->items.erase(currentRoom->items.begin() + (choice - 1));
}

// Displays the player's inventory contents
void Player::showInventory() const {
    cout << "\nInventory:";
    if (inventory.empty()) cout << " (empty)";
    for (auto& i : inventory) cout << " " << i;
    cout << "\n";
}

// Checks whether a specific item exists in the player's inventory
bool Player::hasItem(const string& itemName) const {
    for (const auto& item : inventory)
        if (item == itemName) return true;
    return false;
}

// Returns the current room the player is in
Room* Player::getCurrentRoom() const { return currentRoom; }

// Updates the current room pointer (used for movement)
void Player::setCurrentRoom(Room* room) { currentRoom = room; }