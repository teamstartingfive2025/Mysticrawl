#include <iostream>
#include <tuple>
#include <functional>
#include "Constants.h"
#include "UI.h"
using namespace std;

void displayTitleScreen() {
	SelectionMenu menu({
		{
			{"Enter Dungeon", [](){ /*Enter Dungeon*/; }},
		},
		{
			{"Exit Game", [](){ exit(0); }},
		},
	});

	while(true) {
		cout << Constants::UI::WELCOME_MESSAGE << endl;
		cout << Constants::Story::BACKSTORY << endl;

		cout << Constants::UI::NAVIGATE_TEXT << endl;
		cout << Constants::UI::CONTINUE_TEXT << "\n\n";

		menu.MakeSelection();
	}
}

int main()
{
	displayTitleScreen();
    return 0;
}