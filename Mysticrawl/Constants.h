#pragma once
#include <string>
#include <array>
using namespace std;

namespace Constants {
	namespace UI {
		//Game Title and Expressions
		const string GAME_TITLE = "Mysticrawl";
		const string WELCOME_MESSAGE = "Welcome to " + GAME_TITLE + "!";

		//Coloring
		const string ESCAPE_CODE = "\033[";
		const string SELECTION_COLOR = ESCAPE_CODE + "1;31m"; // Bold Red text
		const string COLOR_RESET = ESCAPE_CODE + "0m"; // Resets text formatting

		//User Prompts
		const string SELECT_KEY_TEXT = "Enter";
		const int SELECT_KEY_CODE = 13;	// ASCII code for Enter key
		const string NAVIGATE_TEXT = "Use the arrow keys to navigate the menu.";
		const string CONTINUE_TEXT = "Press " + SELECT_KEY_TEXT + " to make a selection...";

		//Menu Options
		const int MENU_OPTION_DIMENSIONS = 2; // 2D menu
		const int INITIAL_MENU_OPTION_INDEX = 0; // Start at the first option
		const int VALUE_UNSET = -1;
		const enum FOCUSED_INDEX_DIMENSION { ROW, COL };
		const enum MENU_COMPONENTS { LABEL, ACTION };
		const string FOCUSED_INDEX_PRETEXT = SELECTION_COLOR; // Bold Red text
		const int MENU_OPTION_PADDING_TABS = 2;
		const string FOCUSED_INDEX_POSTTEXT = COLOR_RESET; // Resets text formatting
		const array<int, MENU_OPTION_DIMENSIONS> DEFAULT_FOCUSED_INDEX = { INITIAL_MENU_OPTION_INDEX, INITIAL_MENU_OPTION_INDEX };

		//Menu Navigation
		const int UP_KEY_CODE = 72;    // ASCII code for Up Arrow
		const int DOWN_KEY_CODE = 80;  // ASCII code for Down Arrow
		const int LEFT_KEY_CODE = 75;  // ASCII code for Left Arrow
		const int RIGHT_KEY_CODE = 77; // ASCII code for Right Arrow

		//Menu Styling
		const int TAB_SIZE = 8;
		const int MENU_ITEMS_PER_ROW = 2;
		const string MENU_VERTICAL_BORDER = "|";
		const string MENU_HORIZONTAL_BORDER = "=";

		const array<int, MENU_OPTION_DIMENSIONS> UP_KEY_MODIFIER = { -1, 0 };
		const array<int, MENU_OPTION_DIMENSIONS> DOWN_KEY_MODIFIER = { 1, 0 };
		const array<int, MENU_OPTION_DIMENSIONS> LEFT_KEY_MODIFIER = { 0, -1 };
		const array<int, MENU_OPTION_DIMENSIONS> RIGHT_KEY_MODIFIER = { 0, 1 };
		
	}

	namespace Story {
		const string BACKSTORY = R"(
In a world where magic and mystery intertwine, you find yourself trapped in an ancient dungeon.
Its walls echo with the whispers of forgotten souls. The air is thick with enchantment, 
and every shadow seems to conceal a lurking danger. To escape, you must gather spellbooks, wands,
and other magical trinkets to navigate this labyrinthine filled with treacherous creatures and cunning puzzles.
)";

		// Antagonist introduction
		const string ANTAGONIST_INTRO = R"(
Beware Lord Malachar, the Cursed Warden of the Abyss. Once a noble guardian of the old sanctum, he
was twisted by forbidden magic and now seeks to bind the living to his will. He rules the deep passages,
collecting the souls of those who wander too far, and will stop at nothing to keep his domain unchallenged.
)";
	}

	namespace Gameplay {
		const bool DOOR_LOCKED = true;
	}
}