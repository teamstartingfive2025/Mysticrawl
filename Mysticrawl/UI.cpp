#include "UI.h"
#include "Constants.h"
#include "Input.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include <functional>
#include <tuple>

using namespace std;

SelectionMenu::SelectionMenu(const vector<vector< tuple<string, function<void()>> >>& opts) : options(opts) {}

void SelectionMenu::DisplayOptions() {
	for(int row = Constants::UI::INITIAL_MENU_OPTION_INDEX; row < options.size(); row++) {
		for(int col = Constants::UI::INITIAL_MENU_OPTION_INDEX; col < options[row].size(); col++) {
			if(row == focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW] && col == focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL]) {
				cout	<< Constants::UI::FOCUSED_INDEX_PRETEXT
						<< get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col])
						<< Constants::UI::FOCUSED_INDEX_POSTTEXT << "\t";
			}
			else {
				cout << get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col]) << "\t";
			}
		}

		cout << endl;
	}
}

void SelectionMenu::ApplyKeyModifier(const array<int, Constants::UI::MENU_OPTION_DIMENSIONS> modifier) {
	int focusedRowFinal = focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW] + modifier[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW];
	int focusedColFinal = focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL] + modifier[Constants::UI::FOCUSED_INDEX_DIMENSION::COL];

	if(focusedRowFinal < 0 || focusedRowFinal >= options.size()) {
		return;
	}

	if(focusedColFinal < 0 || focusedColFinal >= options[focusedRowFinal].size()) {
		return;
	}

	focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW] = focusedRowFinal;
	focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL] = focusedColFinal;
}

bool SelectionMenu::MakeSelection() {
	DisplayOptions();

	char input = getInstantaneousCharInput();
	int inputCode = (int)input;

	system("cls");

	int selectedRow;
	int selectedCol;

	switch(inputCode) {
		case Constants::UI::UP_KEY_CODE:
			ApplyKeyModifier(Constants::UI::UP_KEY_MODIFIER);
			return false;
		case Constants::UI::DOWN_KEY_CODE:
			ApplyKeyModifier(Constants::UI::DOWN_KEY_MODIFIER);
			return false;
		case Constants::UI::LEFT_KEY_CODE:
			ApplyKeyModifier(Constants::UI::LEFT_KEY_MODIFIER);
			return false;
		case Constants::UI::RIGHT_KEY_CODE:
			ApplyKeyModifier(Constants::UI::RIGHT_KEY_MODIFIER);
			return false;
		case Constants::UI::SELECT_KEY_CODE:
			selectionIndex = focusedIndex;
			selectedRow = selectionIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW];
			selectedCol = selectionIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL];

			// Execute the associated action
			get<Constants::UI::MENU_COMPONENTS::ACTION>(options[selectedRow][selectedCol])();

			return true;
		default:
			return false;
	}
}