#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include "Potion.h"
#include "Fight.h"
#include "Prompt.h"

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

    Enemy* wizard = new Enemy("Evil Wizard", "An evil wizard glares at you, ready to cast a spell!\n", 30);
    wizardRoom.addEnemy(wizard);

    Enemy* rat = new Enemy("Rat", "A rat suddenly appears! It bites you and scurries away.\n", 5);
    fightRoom.addEnemy(rat);

    fightRoom.addItem(make_shared<Potion>("Potion of Healing", 10));

    // Connect rooms via exits
    shared_ptr<Key> key = make_shared<Key>();
    spawnRoom.setExits({ Exit("east", &nextRoom, { [&]() -> bool { return player.hasItem(key); } }) });
    key->setName("Key");
    key->setExitKeyUnlockDestination(spawnRoom.getExit("east"));
    spawnRoom.addHiddenItem(key);

    nextRoom.setExits({ Exit("west", &spawnRoom), Exit("north", &wizardRoom), Exit("east", &fightRoom) });
    wizardRoom.setExits({ Exit("south", &nextRoom) });
    fightRoom.setExits({ Exit("west", &nextRoom) });

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


            options.push_back(
                { "Exit Game", [&]() {
                    WaitForEnterPrompt("You leave the dungeon for now...\n\n");
                    throw runtime_error("exit lambda and dungeon loop");
                } }
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