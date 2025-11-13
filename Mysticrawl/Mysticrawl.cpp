#include <iostream>
#include <tuple>
#include <functional>
#include "Constants.h"
#include "Input.h"
#include "Prompt.h"
#include "Room.h"
#include "Exit.h"
#include "Potion.h"
#include "Item.h"
#include "Key.h"
#include "Fight.h"
#include "Dungeon.h"

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

        cout << Constants::UI::WELCOME_MESSAGE;
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