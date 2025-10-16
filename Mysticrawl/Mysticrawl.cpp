#include <iostream>
#include <tuple>
#include <functional>
#include "Constants.h"
#include "UI.h"
#include "Dungeon.h"   // Include our new dungeon system
using namespace std;

void displayLoreScreen() {
    system("cls");
    cout << Constants::Story::BACKSTORY << "\n\n";
    cout << Constants::Story::ANTAGONIST_INTRO << "\n\n";
    cout << "Press Enter to return to the main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayTitleScreen() {
    // Title screen menu setup
    SelectionMenu menu({
    {
        {"Enter Dungeon", []() { StartDungeon(); }},
    },
    {
        {"View Lore", []() { displayLoreScreen(); }},
    },
    {
        {"Exit Game", []() { exit(0); }},
    },
        });



    while (true) {
		system("cls");
        cout << Constants::UI::WELCOME_MESSAGE << endl;
        cout << Constants::Story::BACKSTORY << endl;
        cout << Constants::UI::NAVIGATE_TEXT << endl;
        cout << Constants::UI::CONTINUE_TEXT << "\n\n";
        menu.MakeSelection();
    }
}

int main() {
    displayTitleScreen();
    return 0;
}