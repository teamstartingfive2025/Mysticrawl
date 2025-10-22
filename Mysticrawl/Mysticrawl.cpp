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
    while (true) {
        // Title screen menu setup
        SelectionMenu menu({
            {
                {"Enter Dungeon", []() { StartDungeon(); }},
            },
            {
                {"View Lore", []() {
					WaitForEnterPrompt(Constants::Story::BACKSTORY + Constants::Story::ANTAGONIST_INTRO + "\n");
                }},
            },
            {
                {"Exit Game", []() { exit(0); }},
            },
            });

        Prompt& prompt = Prompt::GetInstance();

        cout << Constants::UI::WELCOME_MESSAGE << endl;
        cout << Constants::Story::BACKSTORY << endl;
        cout << Constants::UI::NAVIGATE_TEXT << endl;
        cout << Constants::UI::CONTINUE_TEXT << endl;

        menu.MakeSelection();
    }
}

int main() {
    displayTitleScreen();
    return 0;
}