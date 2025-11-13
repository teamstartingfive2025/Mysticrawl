#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include "Potion.h"
#include "Fight.h"
#include "SimpleMechanism.h"
#include "EnemyTemplates.h"
#include "Prompt.h"
#include "Lockable.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

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

    Room wizardRoom(
        "Wizard's Lair",
        "The air crackles with magical energy. Ancient tomes and potions clutter the space.\n"
    );

    // --- Initialize the player ---
    Player player(&spawnRoom, "Hero", 100);

	Enemy wizard = WizardTemplate;
    wizardRoom.addEnemy(&wizard);

    // New N/S rooms
    Room northRoom(
        "North Corridor",
        "A narrow passage runs north-south. The air is colder here, and the stones are slick with moss.\n"
    );

    Room southRoom(
        "South Cellar",
        "A low-ceiling cellar stuffed with broken barrels. Something skitters beneath the debris.\n"
    );

    Enemy rat = RatTemplate;

    fightRoom.addEnemy(&rat);

    fightRoom.addItem(make_shared<Potion>("Potion of Healing", 10));

    Room leverRoom(
        "Lever Room",
        "You step into a dimly lit chamber. A single iron lever is fixed to the wall."
    );

    Room buttonRoom(
        "Button Room",
        "The air smells of dust. A round stone button is embedded in the far wall."
    );

    Room greaterRatRoom(
        "The trial of the Greater Rat",
        "Special attack demo. This room definitely doesn't have to be in the final game."
    );

    Enemy gRat = GreaterRatTemplate;
    greaterRatRoom.addEnemy(&gRat);

    // Connect rooms via exits
    shared_ptr<Key> key = make_shared<Key>();
    spawnRoom.setExits({ Exit("east", &nextRoom, { [&]() -> bool { return player.hasItem(key); } }) });
    key->setName("Key");
    key->setExitKeyUnlockDestination(spawnRoom.getExit("east"));
    spawnRoom.addHiddenItem(key);

    // Next Room connects in all four directions
    nextRoom.setExits({
        Exit("west",  &spawnRoom),
        Exit("east",  &fightRoom),
        Exit("north", &wizardRoom),
        Exit("south", &southRoom)
    });

    wizardRoom.setExits({
        Exit("south", &nextRoom)
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

    fightRoom.setExits({
        Exit("west", &nextRoom),
        Exit("east", &leverRoom),
        Exit("north", &greaterRatRoom)
    });

    greaterRatRoom.setExits({
        Exit("south", &fightRoom)
    });

    leverRoom.setExits({
        Exit("west", &fightRoom),
        Exit("east", &buttonRoom) // locked initially
    });

    buttonRoom.setExits({
        Exit("west", &leverRoom)
    });

    shared_ptr<SimpleMechanism> lever = make_shared<SimpleMechanism>(
        "Iron Lever", true, // true = lever type
        [&leverRoom](bool state) {                // capture leverRoom by reference
            if (exit) {
                if (state) {
                    cout << "You hear gears turning, the eastern door unlocks!\n";
                }
                else {
                    cout << "The lever resets, the door locks again.\n";
                }
            }
        }
    );

    leverRoom.getExit("east")->addLock([&]() -> bool { return lever->getState(); });

    leverRoom.addMechanism(lever);

    auto button = make_shared<SimpleMechanism>(
        "Stone Button", false,
        [&buttonRoom](bool) {
            cout << "A hidden panel opens revealing a glittering amulet!\n";
            auto amulet = make_shared<Item>("Glittering Amulet");
            buttonRoom.addItem(amulet); 
        }
    );

    buttonRoom.addMechanism(button);

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
                options.push_back({ "Use Item", [&player]() { player.useItem(player.itemSelectMenu());  } });
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
                } }
            );

            for (Enemy* enemy : player.getCurrentRoom()->getEnemies()) {
                if (enemy) {
                    enemy->action(player);
                    if (player.getHealth() <= 0) {
                        return;
                    }
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