#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include "Fight.h"
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
        { make_shared<Item>("Torch") }
    );

    Room nextRoom(
        "Next Room",
        "You step into a darker chamber. Runes glow faintly on the wall. "
        "A torch might help illuminate the strange scroll lying on the ground.",
        { make_shared<Item>("Scroll with Riddle") }
    );

    Room fightRoom(
        "Dusty Cellar",
        "Old crates and the smell of mildew.\n"
    );

    Enemy* rat = new Enemy("Rat", "A rat suddenly appears! It bites you and scurries away.\n", 5);
    fightRoom.addEnemy(rat);

    // Connect rooms via exits
    spawnRoom.setExits({ Exit("east", &nextRoom, Constants::Gameplay::DOOR_LOCKED) });
    spawnRoom.addHiddenItem(make_shared<Key>("Key", spawnRoom.getExit("east")));

    nextRoom.setExits({ Exit("west", &spawnRoom), Exit("east", &fightRoom) });
    fightRoom.setExits({ Exit("west", &nextRoom) });

    // --- Initialize the player ---
    Player player(&spawnRoom, "Hero", 100);

    // --- Initialize fight manager ---
    Fight fight;

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
                
            };

            if (!player.getCurrentRoom()->getEnemies().empty()) {
                cout << "Dungeon: " << player.getCurrentRoom()->getEnemies().empty() << endl;
                options.push_back({ "Fight", [&]() {
                    fight.fightMenu(player);
                } });
            }

            options.push_back(
                { "Exit Game", [&]() {
                    WaitForEnterPrompt("You leave the dungeon for now...\n\n");
                    throw runtime_error("exit lambda and dungeon loop");
                }}
            );

            for (Enemy* enemy : player.getCurrentRoom()->getEnemies()) {
                if (enemy && enemy->hostilityTrigger()) {
                    int damage = enemy->attack(player);
                    cout << enemy->getName() << " attacked you, health decreased by " << damage << endl;
                }
            }

            player.displayHealthBar();

		    player.getCurrentRoom()->RefreshSelectionMenu(options);
            player.getCurrentRoom()->SelectMenuOption();
        }
    }
    catch (const runtime_error&) {
        return;
    }
}