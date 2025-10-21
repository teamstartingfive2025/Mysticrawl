#include <iostream>
#include <tuple>
#include <functional>
#include "Constants.h"
#include "UI.h"
#include "Dungeon.h"   // Include our new dungeon system
using namespace std;

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