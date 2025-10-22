#include "Fight.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"

void Fight::fightMenu(Player& player) {
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