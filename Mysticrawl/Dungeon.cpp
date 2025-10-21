#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

void Exit::unlock() {
    locked = false;
}

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

/**
 * The StartDungeon function runs the dungeon portion of the game.
 * It sets up the initial rooms, links them together, initializes the player,
 * and manages the main gameplay loop (exploration, movement, and interaction).
 */
void StartDungeon() {
    // --- Define dungeon layout and content ---
    Room spawnRoom(
        "Spawn Room",
        "You awake in a dimly lit dungeon cell, confused and dazed. \n"
        "The fiery light of a torch flickers against the dark, cold walls. \n"
        "The room is barren except for a sole flowerpot resting beside a pile of stones in the corner. \n"
        "A large iron-clad door stands to the east, bearing a large lock on the handle.\n",
        { make_shared<Item>("Torch") },
        {}
    );

    Room nextRoom(
        "Next Room",
        "You step into a darker chamber. Runes glow faintly on the wall. "
        "A torch might help illuminate the strange scroll lying on the ground.",
        { make_shared<Item>("Scroll with Riddle") },
        {}  // empty key
    );

    Room fightRoom(
        "Rat Room",
        "This is the combat demo.\n",
		{}, // empty items
        {}  // empty key
    );

    // Connect rooms via exits
    spawnRoom.setExits({ Exit("east", &nextRoom, Constants::Gameplay::DOOR_LOCKED) });
    spawnRoom.addHiddenItem(make_shared<Key>("Key", spawnRoom.getExit("east")));

    nextRoom.setExits({ Exit("west", &spawnRoom), Exit("east", &fightRoom) });
    fightRoom.setExits({ Exit("west", &nextRoom) });

    // --- Initialize the player ---
    Player player(&spawnRoom, "Hero", 100);

    // --- Main dungeon loop ---
    player.look();

    try {
        while (true) {
            vector< tuple<string, function<void()>> > options;
        
                options = {
                    {"Look around", [&player]() { player.look(); }},
                    {"Investigate the area", [&player]() { player.investigate(); }},
                    {"Check Inventory", [&player]() { player.showInventory(); }},
					{"Move Somewhere", [&player]() { player.move(); }},
                    {"Pickup Item", [&player]() { player.pickup(); }},
                    {"Exit Game", [&]() {
                        WaitForEnterPrompt("You leave the dungeon for now...\n\n");
                        throw runtime_error("exit lambda and dungeon loop");
                    }}
                };

		    player.getCurrentRoom()->RefreshSelectionMenu(options);
            player.getCurrentRoom()->SelectMenuOption();
        }
    }
    catch (const runtime_error&) {
        return;
    }
}

/*void StartDungeon() {
    // Seed std random (defensive)
    std::srand((unsigned)std::time(nullptr));
    cout << "You enter the dimly lit dungeon. Your starting health is " << player.getHealth() << ".\n\n";

    // Create a single room for a simple demo
    Room entry;
    entry.name = "Dusty Cellar";
    entry.description = "Old crates and the smell of mildew.";

    cout << "You step into: " << entry.name << "\n";
    cout << entry.description << "\n\n";
    cout << "Press Enter to proceed into the room..." << endl;
    std::string dummy; getline(cin, dummy);

    // Spawn a rat enemy
    Enemy rat(Enemy::Type::Rat, 5);

    if (rat.hostilityTrigger()) {
        // Rat will attack immediately once
        int damage = rat.attack(player);

        // Acceptance criteria text:
        cout << "A rat suddenly appears! It bites you and scurries away.\n";
        cout << "enemy attacked you, health decreased by " << damage
             << ", your new health is " << player.getHealth() << "\n\n";
    } else {
        cout << "A small rat appears but it is startled and runs away without biting you.\n\n";
    }

    cout << "Press Enter to return to the title screen." << endl;
    getline(cin, dummy);
}*/