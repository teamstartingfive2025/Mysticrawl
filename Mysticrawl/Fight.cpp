#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"
#include <iostream>
using namespace std;

void Fight::fightMenu(Player& player) {
    // 1. Retrieve a reference to the current room the player is standing in
    Room* room = player.getCurrentRoom();

    // 2. Validate that the room actually contains enemies
    if (room->getEnemies().empty()) {
        cout << "There are no enemies to fight here.\n";
        return;
    }
    // 3. Create our menu option list using lambdas.
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
    // 4. Display the fight menu and handle input

    RefreshSelectionMenu(fightOptions);
    SelectMenuOption();
}