#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Key.h"
#include "Random.h"
#include "Lockable.h"
#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace std;

// Prints details about the current room and visible items
void Player::look() const {
    cout << "\n== " << currentRoom->getName() << " ==\n";
    cout << currentRoom->getDescription() << "\n";

    if (!currentRoom->getItems().empty()) {
        cout << "You see:\n";
        for (const auto& item : currentRoom->getItems())
            cout << " - " << item->getName() << "\n";
    }
    else {
        cout << "You don't see any items.\n";
    }
    // Show mechanisms in the room (like levers or buttons)
    if (!currentRoom->getMechanisms().empty()) {
        cout << "\nYou notice the following mechanisms:\n";
        for (const auto& mech : currentRoom->getMechanisms()) {
            cout << " - " << mech->getDescription() << "\n";
        }
    }
	// Show containers in the room
    if (!currentRoom->getContainers().empty()) {
        cout << "\nYou notice the following containers:\n";
        for (const auto& container : currentRoom->getContainers()) {
            cout << " - " << container.getName() << "\n";
		}
    }
    auto& enemies = currentRoom->getEnemies();
    for (Enemy* enemy : enemies) {
        if (enemy) enemy->DisplayIntroText();
    }

    cout << "\nExits:\n";
    for (const auto& exit : currentRoom->getExits()) {
        cout << " - " << exit.getDirection();
        if (exit.isLocked())
            cout << " (locked)\n";
        else
            cout << " (unlocked)\n";
    }
}

void Player::investigate() {
    if (currentRoom->getHiddenItems().empty()) {
        cout << "You search the area but find nothing unusual.\n";
        return;
    }

    cout << "You carefully search the room and discover:\n";
    for (const auto& item : currentRoom->getHiddenItems()) {
        cout << " - " << item->getName() << "\n";
        currentRoom->addItem(item); // Move to visible items
    }
    currentRoom->clearHiddenItems();
}

// Picks up the first item available in the current room
void Player::pickup() {
    auto& roomItems = currentRoom->getItems();

    if (roomItems.empty()) {
        cout << "There is nothing to pick up here.\n";
        return;
    }

    vector<tuple<string, function<void()>>> itemOptions;

    cout << "Items available to pick up:\n";

    for (size_t i = 0; i < roomItems.size(); ++i) {
        auto& item = roomItems[i];
        itemOptions.push_back({
            item->getName(),
            [this, &roomItems, i]() {
                if (i < roomItems.size()) {
                    shared_ptr<Item> pickedItem = roomItems[i];
                    cout << "You pick up the " << pickedItem->getName() << ".\n";

                    if (auto key = dynamic_pointer_cast<Key>(pickedItem)) {
                        key->printUnlockText();
                    }

                    inventory.push_back(pickedItem);
                    roomItems.erase(roomItems.begin() + i);
                }
            }
            });
    }

    RefreshSelectionMenu(itemOptions);
    SelectMenuOption();
}

// Allows the player to move between rooms
void Player::move()
{
    if (currentRoom->getExits().empty()) {
        cout << "You don't see any exits.\n";
        return;
    }

	// Check if enemy will block movement
    string enemyBlockingExit = "";

    for (Enemy* enemy : currentRoom->getEnemies()) {
            if (enemy && enemy->isBlockingExit()) {
				enemyBlockingExit = enemy->getName();
                break;
            }
	}

    vector< tuple<string, function<void()>> > moveOptions;

    for (const auto& exit : currentRoom->getExits()) {
        string label = string("Go ") + exit.getDirection() + " ";

        moveOptions.emplace_back(
            label,
            [this, exit, enemyBlockingExit]() {
                if (!enemyBlockingExit.empty()) {
                    cout << "You tried to escape " << exit.getDirection()
                        << " but " << enemyBlockingExit << " blocks your way.\n";
                    return;
                }

                if (exit.isLocked()) {
                    cout << "The way " << exit.getDirection() << " is locked.\n";
                    return;
                }

                setCurrentRoom(exit.getDestination());
                cout << "You move " << exit.getDirection() << ".\n";

                for (Enemy* enemy : currentRoom->getEnemies())
                {
                    function <void(Enemy* self, Player& target)> encounterFunction = enemy->getEncounterFunction();
                    if (encounterFunction != nullptr) {
                        encounterFunction(enemy, *this);
                    }
                }

                look();
            }
        );
    }

    RefreshSelectionMenu(moveOptions);
    SelectMenuOption();
}


// Displays the player's inventory contents
void Player::showInventory() const {
    cout << "\nInventory:";
    if (inventory.empty()) cout << " (empty)";
    for (auto& item : inventory) cout << " " << item->getName();
    cout << "\n";
}

// Displays selection menu of all items in player inventory and returns player choice
shared_ptr<Item> Player::itemSelectMenu() {
    shared_ptr<Item> selection;
    
    vector< tuple<string, function<void()>>> itemOptions;
    for (const auto& item : inventory) {
        itemOptions.push_back({ item->getName(), [item, &selection]() { selection = item; } });
    }
    RefreshSelectionMenu(itemOptions);
    SelectMenuOption();

    return selection;
}

// Manages item usage
void Player::useItem(shared_ptr<Item> item) {
    item->use(this);

    if(item->isConsumable()) inventory.erase(find(inventory.begin(), inventory.end(), item)); //delete consumables after use
}

bool Player::inventoryEmpty() { return inventory.empty(); }

// Checks whether a specific item exists in the player's inventory
bool Player::hasItem(const shared_ptr<Item> itemPointer) const {
    for (const auto& item : inventory) {
        if (item == itemPointer)
            return true;
    }
    return false;
}

// Returns the current room the player is in
Room* Player::getCurrentRoom() const { return currentRoom; }

// Updates the current room pointer (used for movement)
void Player::setCurrentRoom(Room* room) { currentRoom = room; }

// Health accessors
int Player::getMaxHealth() const {
    return maxHealth;
}

bool Player::isAlive() const {
    return health > 0;
}

// Applies positive damage; returns actual damage applied (clamped to current health)
int Player::takeDamage(int amount) {
    if (amount <= 0) return 0;
    int actual = std::min(amount, health);
    health -= actual;
    return actual;
}

// Heals player by amount, clamped to maxHealth; returns actual healed amount
int Player::heal(int amount) {
    if (amount <= 0) return 0;
    int space = maxHealth - health;
    int healed = std::min(space, amount);
    health += healed;
    return healed;
}

// Set current health (clamped 0..maxHealth)
void Player::setHealth(int hp) {
    if (hp < 0) health = 0;
    else if (hp > maxHealth) health = maxHealth;
    else health = hp;
}

// Adjust max health (optionally adjust current health if it exceeds new max)
void Player::setMaxHealth(int newMax) {
    if (newMax < 1) return; // ignore invalid values
    maxHealth = newMax;
    if (health > maxHealth) health = maxHealth;
}

void Player::setPoisoned(bool p, int c, int min, int max) { // make the player poisoned and increment time until poison is cured
    poisoned = p;
    poisonCounter += c;
    if (min > poisonMin) poisonMin = min;
    if (max > poisonMax) poisonMax = max;
}

bool Player::isPoisoned() { return poisoned; }

int Player::getPoisonMin() { return poisonMin; }

int Player::getPoisonMax() { return poisonMax; }

void Player::decrementPoison() {
    poisonCounter--;
    if (poisonCounter < 1) {
        setPoisoned(false, 0, 0, 0);
    }
}

void Player::displayHealthBar(int width) const {
    if (width < 4) width = 4; // ensure space for brackets and numbers

    // avoid divide-by-zero if maxHealth somehow 0
    int maxHp = (maxHealth > 0 ? maxHealth : 1);
    int filled = static_cast<int>((static_cast<double>(health) / maxHp) * (width - 2));
    if (filled < 0) filled = 0;
    else if (filled > width - 2) filled = width - 2;
    int empty = (width - 2) - filled;

    // Build bar
    std::string bar;
    bar.reserve(width);
    bar.push_back('[');
    bar.append(filled, '#');
    bar.append(empty, '-');
    bar.push_back(']');

    // Print with numeric readout
    std::cout << "\nHealth " << bar << " " << health << "/" << maxHp;
}

// Player::basicAttack() Generic unarmed strike implementation.
void Player::basicAttack(Enemy& target, Room& currentRoom) {
    // Generate random damage between 2 and 6
	int damage = Random::GetInstance().randInt(2, 6);

    // Print attack message
    cout << "You swing your fists at the " << target.getName()
        << " for " << damage << " damage!\n";

    // Apply the damage
    target.takeDamage(damage);

    // If the enemy's HP has dropped to 0 or below, print a message
    if (!target.isAlive()) {
        cout << "The " << target.getName()
            << " collapses to the ground. You are victorious!\n";
    }
    else {
        // If the enemy still has health, display the remaining HP
        cout << "The " << target.getName()
            << " still has " << target.getHealth() << " HP left.\n";
    }
}
    void Player::interact() {

        auto& mechs = currentRoom->getMechanisms();
        auto& containers = currentRoom->getContainers();

        if (mechs.empty() && containers.empty()) {
            cout << "There is nothing here to interact with.\n";
            return;
        }

        // Create a list of menu options from available mechanisms
        vector<tuple<string, function<void()>>> interactOptions;

        for (const auto& mech : mechs) {
            // Each menu item triggers that mechanism's use() function
            interactOptions.push_back({
                mech->getDescription(),
                [mech]() { mech->use(); }
            });
        }

        for (auto& container : containers) {
            // Each menu item attempts to open container menu
            interactOptions.push_back({
                container.getName(),
                [&container]() { container.openContainerSelection(); }
            });
        }

        // Optional exit option so the player can back out
        interactOptions.push_back({
            "Cancel", []() { cout << "You don't interact with anything.\n"; }
        });

        // Refresh and show the arrow-key menu
        RefreshSelectionMenu(interactOptions);
        SelectMenuOption();
    }
