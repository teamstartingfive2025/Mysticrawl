#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"
#include <iostream>
using namespace std;

void Fight::fightMenu(Player& player) {
    // 1. Retrieve a reference to the current room the player is standing in
    // 2. Validate that the room actually contains enemies
    // 3. Create our menu option list using lambdas.
    // 4. Display the fight menu and handle input
    vector<tuple<string, function<void()>>> fightOptions;

    fightOptions = {
        { "Attack", [&/*Relevent object*/]() { cout << "You attack."; /*replace with relevant function*/} },
        { "Defend", [&/*Relevent object*/]() { cout << "You defend."; /*replace with relevant function*/} },
        { "Check", [&player]() { 
            for (Enemy enemy : player.getCurrentRoom()->getEnemies()) {
				cout << "Enemies present:\n";
				cout << " - " << enemy.getName() << " (Health: " << enemy.getHealth() << ")\n";
            }
        }},
    };

    RefreshSelectionMenu(fightOptions);
    SelectMenuOption();
}