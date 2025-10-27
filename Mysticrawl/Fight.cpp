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

    // --- RUN OPTION ---
    fightOptions.push_back({
        "Run",
        [&player, room, this]() {
            if (room->getEnemies().empty()) {
                cout << "There's nothing to run from.\n";
                return;
            }
            Enemy* enemy = room->getEnemies().front();
            bool battleEnded = false;
            AttemptRun(player, *enemy, battleEnded);
            if (battleEnded) {
                cout << "You dash back toward safety!\n";
                // return to dungeon (just end fightMenu)
                room->getEnemies().clear();
                throw runtime_error("Player fled battle");
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
    // 60% base chance to successfully run away
    return d(rng) < 60;
}

void Fight::HandleRunOutcome(bool success, Player& player, Enemy& enemy, bool& battleEnded) {
    if (success) {
        cout << "You turn and sprint into the shadows... You escaped!\n";
        battleEnded = true; // success → exit battle loop
        return;
    }

    // failure → counterattack
    cout << "You trip—no escape! The " << enemy.getName() << " strikes back!\n";
    int damage = enemy.attack(player);
    cout << "enemy attacked you, health decreased by " << damage
        << ", your new health is " << player.getHealth() << "\n";
    player.displayHealthBar();
}