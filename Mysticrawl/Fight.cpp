#include "Fight.h"

void Fight::fightMenu() {
    vector<tuple<string, function<void()>>> fightOptions;

    fightOptions = {
        {"Attack", [&/*Relevent object*/]() { cout << "You attack."; /*replace with relevant function*/} },
        {"Defend", [&/*Relevent object*/]() { cout << "You defend."; /*replace with relevant function*/} }
    };

    RefreshSelectionMenu(fightOptions);
    SelectMenuOption();
}