#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include "Potion.h"
#include "Fight.h"
#include "Mechanism.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

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

    // Template N/S Rooms
    Room northRoom(
        "North Corridor",
        "A narrow passage runs north-south. The air is colder here, and the stones are slick with moss.\n"
    );

    Room southRoom(
        "South Cellar",
        "A low-ceiling cellar stuffed with broken barrels. Something skitters beneath the debris.\n"
    );

    Enemy* rat = new Enemy("Rat", "A rat suddenly appears! It bites you and scurries away.\n", 5);
    fightRoom.addEnemy(rat);

    fightRoom.addItem(make_shared<Potion>("Potion of Healing", 10));

    Room leverRoom(
        "Lever Room",
        "You step into a dimly lit chamber. A single iron lever is fixed to the wall."
    );

    Room buttonRoom(
        "Button Room",
        "The air smells of dust. A round stone button is embedded in the far wall."
    );

    // Connect rooms via exits
    spawnRoom.setExits({ Exit("east", &nextRoom, Constants::Gameplay::DOOR_LOCKED) });
    spawnRoom.addHiddenItem(make_shared<Key>("Key", spawnRoom.getExit("east")));

    // Next Room connects in all four directions
    nextRoom.setExits({
        Exit("west",  &spawnRoom),
        Exit("east",  &fightRoom),
        Exit("north", &northRoom),
        Exit("south", &southRoom)
        });

    // Fight room unchanged besides its west return
    fightRoom.setExits({
        Exit("west", &nextRoom)
        });

    // New rooms return to Next Room
    northRoom.setExits({
        Exit("south", &nextRoom)
        });

    southRoom.setExits({
        Exit("north", &nextRoom)
        });


    auto button = make_shared<SimpleMechanism>(
        "Stone Button", false,
        [&buttonRoom](bool) {
            cout << "A hidden panel opens revealing a glittering amulet!\n";
            auto amulet = make_shared<Item>("Glittering Amulet");
            buttonRoom.addItem(amulet); 
        }
    );

    buttonRoom.addMechanism(button);
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
            if (!player.inventoryEmpty()) {
                options.push_back({ "Use Item", [&player]() { player.useItem(player.itemSelectMenu());  }});
            }

            //only give fight option if enemy is present
            if (!player.getCurrentRoom()->getEnemies().empty()) {
                options.push_back({ "Fight", [&]() {
                    fight.fightMenu(player);
                } });
            }

            if (!player.getCurrentRoom()->getMechanisms().empty()) {
                options.push_back({ "Interact", [&]() { player.interact(); } });
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
                    string attackMessage = enemy->getName() + " attacked you, health decreased by " + to_string(damage);

                    if (player.getHealth() <= 0) {
                        WaitForEnterPrompt(attackMessage + Constants::Gameplay::GAME_OVER_TEXT);
                        return;
                    }

                    cout << attackMessage << endl;
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