#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
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

            player.basicAttack(*target, *room); // dereference for attack

            if (!target->isAlive()) {
                cout << target->getName() << " is defeated!\n";
                enemies.erase(enemies.begin());
            }
        }
        });

    // --- DEFEND OPTION ---
    if (player.getDefenceCooldown() == 0) {
        fightOptions.push_back({
            "Defend",
            [&player]() {
                cout << "You brace yourself for an incoming attack.\n";
                player.setDefenceTurns(2); //next enemy attack reduced
                player.setDefenceCooldown(4);
            }
        });
    }

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
}