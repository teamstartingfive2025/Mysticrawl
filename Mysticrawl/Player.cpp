#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Key.h"
#include "Weapons.h"
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

        //Show weapon description
        if (auto weapon = dynamic_pointer_cast<Weapon>(item)) {

            cout << " - " << weapon->getWeaponDescription();
        }
        cout << "\n";
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

    string currentRoomName;
    if (currentRoom != nullptr) {
        currentRoomName = currentRoom->getName();
    }
    else {
        currentRoomName = "";
    }

    for (const auto& item : inventory) {
        bool allow = true;

        //If user choices weapon, apply logic
        if (auto weapon = dynamic_pointer_cast<Weapon>(item))
        {
            if (weapon->getName() == "Staff")
            {
                //Only allow staff usage in GR room
                if (currentRoomName != "The Trial of the Greater Rat") {
                    allow = false;
                }
            }
        }

        if (!allow) continue;
        itemOptions.push_back({ item->getName(), [item, &selection]() { selection = item; } });
    }
    RefreshSelectionMenu(itemOptions);
    SelectMenuOption();

    return selection;
}

// Manages item usage
void Player::useItem(shared_ptr<Item> item) {

    //Behavior if staff is used
    if (auto weapon = dynamic_pointer_cast<Weapon>(item)) {
        if (weapon->getName() == "Staff")
        {
            cout << "You have equipped the Mighty Staff. It provides magical energy to defeat the Greater Rat.";
        }
        return;
    }

    item->use(this);
    if (item->isConsumable()) inventory.erase(find(inventory.begin(), inventory.end(), item)); //delete consumables after use

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

void Player::setDefending(bool value) {
    defending = value;
}

bool Player::isDefending() const {
    return defending;
}

// Applies positive damage; returns actual damage applied (clamped to current health)
int Player::takeDamage(int amount) {
    if (amount <= 0) return 0;
    if (defending)
    {
        amount -= 2; //next enemy attack damage = -2 of normal
        defending = false;
    }
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

//Player has option of using Staff or fists
void Player::attack(Enemy& target, Room& currentRoom, shared_ptr<Weapon> weapon) {
    int damage = 0;

    //Determine damage
    if (weapon) {
        if (weapon->getName() == "Staff") {
            damage = Random::GetInstance().randInt(5, 8); // damage ranges from 5-8
        }
    }
    else {
        //no weapon = basic attack (fists)
        damage = Random::GetInstance().randInt(2, 6); // damage ranges from 2-6
    }

    if (damage < 0) damage = 0;

    //Print combat message
    if (weapon) {
        cout << "You attacked the enemy with " << weapon->getName() << " for " << damage << " damage.\n";
    }
    else {
        cout << "You attacked the enemy for " << damage << " damage.\n";
    }

    //Apply damage
    target.takeDamage(damage);

    //Staff and Greater Rat disappearance/destruction
    if (!target.isAlive()) {
        cout << "The " << target.getName() << " collapses to the ground. You are victorious!\n";

        if (weapon && weapon->getName() == "Staff" && target.getName() == "Greater Rat" && !target.isAlive()) {
            cout << "During battle, the staff was damaged and was left behind. "
                << "You drop the staff, and see a wisp of smoke and the staff magically disappears.\n";
        }

        //Remove Staff from Inventory
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (*it && (*it)->getName() == "Staff") {
                inventory.erase(it);
                break; //stops after removing Staff
            }
            else {
                cout << "The " << target.getName() << " still has " << target.getHealth() << " HP left.\n";
            }
        }  
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
