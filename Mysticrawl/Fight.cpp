#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "Weapons.h"
#include <iostream>
using namespace std;

void Fight::fightMenu(Player& player) {
    // 1. Retrieve a reference to the current room the player is standing in
    Room* room = player.getCurrentRoom();

    // 2. Validate that the room actually contains enemies
    if (room->getEnemies().empty()) {
        cout << "Fight: " << room->getEnemies().empty() << endl;

        cout << "There are no enemies to fight here.\n";
        return;
    }
    // 3. Create our menu option list using lambdas.
    vector<tuple<string, function<void()>>> fightOptions;

    // --- ATTACK OPTION ---
    fightOptions.push_back({
        "Attack",
        [&player, room]() {
        auto& enemies = room->getEnemies();
            
            // Player attacks first enemy in the room
            Enemy* target = enemies.front();  

            //Collect player weapons
            vector<shared_ptr<Weapon>> weapons;
            for (const auto& item : player.getInventory())
            {
                if (auto weapon = dynamic_pointer_cast<Weapon>(item))
                {
                    weapons.push_back(weapon);
                }
            }

            //Player has no weapons, basicAttack used
            if (weapons.empty())
            {
                player.basicAttack(*target, *room); // dereference for attack

                if (!target->isAlive())
                {
                    cout << target->getName() << " is defeated!\n";
                    enemies.erase(enemies.begin());
                }
                return;
            }

            //Sub-Menu for weapons
            vector<tuple<string, function<void()>>> weaponOptions;

            for (auto& weapon : weapons) {
                string label = "Use " + weapon->getName();

                weaponOptions.push_back({
                    label,
                    [&player, room, weapon]() {
                        auto& enemies = room->getEnemies();
                        if (enemies.empty()) return;

                        Enemy* t = enemies.front();

                        // Use the weapon-based attack (Staff, Sword, etc.)
                        player.attack(*t, *room, weapon);

                        if (!t->isAlive()) {
                            cout << t->getName() << " is defeated!\n";
                            enemies.erase(enemies.begin());
                        }
                    }
                });
            }
            // Show weapon sub-menu 
            Fight subMenu;
            subMenu.RefreshSelectionMenu(weaponOptions);
            subMenu.SelectMenuOption();

            



        }
    });

    // --- DEFEND OPTION (functional) ---
    fightOptions.push_back({
        "Defend",
        [&player]() {
            cout << "You brace yourself for an incoming attack.\n";
            player.setDefending(true); //next enemy attack reduced
        }
        });

    // --- CHECK OPTION ---
    fightOptions.push_back({
        "Check",
        [&player]() {
            cout << "\nEnemies present:\n";
            for (Enemy* enemy : player.getCurrentRoom()->getEnemies()) {
                if (enemy)
                    cout << " - " << enemy->getName()
                    << " (Health: " << enemy->getHealth() << ")\n";
            }
        }
        });

    // 4. Display the fight menu and handle input

    RefreshSelectionMenu(fightOptions);
    SelectMenuOption();
};