#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"
#include <iostream>
#include <random>
#include <chrono>
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
                delete target; // prevent memory leak
            }
        }
        });

    // --- DEFEND OPTION (placeholder) ---
    fightOptions.push_back({
        "Defend",
        []() {
            cout << "You brace yourself for an incoming attack.\n";
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
}
void Fight::AttemptRun(Player& player, Enemy& enemy, bool& battleEnded) {
    bool success = CalculateRunChance();
    HandleRunOutcome(success, player, enemy, battleEnded);
}

bool Fight::CalculateRunChance() {
    static std::mt19937 rng(
        (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    std::uniform_int_distribution<int> d(0, 99);
    // 40% base chance to successfully run away
    return d(rng) < 40;
}

void Fight::HandleRunOutcome(bool success, Player& player, Enemy& enemy, bool& battleEnded) {
    if (success) {
        cout << "\nYou turn and sprint into the shadows... You escaped!\n\n";
        battleEnded = true;
        return;
    }

    // failure → counterattack
    cout << "\nYou trip, no escape! The " << enemy.getName() << " strikes back!\n";
    int damage = enemy.attack(player);
    cout << "enemy attacked you, health decreased by " << damage
        << ", your new health is " << player.getHealth() << "\n\n";
    player.displayHealthBar();
    cout << "\n"; // extra space for readability
}
