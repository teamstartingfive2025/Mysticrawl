#include "UI.h"
#include "Constants.h"
#include "Input.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include <functional>
#include <tuple>
#include <stdlib.h>

using namespace std;

Prompt& Prompt::GetInstance() {
	static Prompt instance;
	return instance;
}

void Prompt::StartRecordingText() {
	cout.rdbuf(promptTextBuffer.rdbuf());
	promptTextBuffer.str("");
}

void Prompt::StopRecordingText() {
	text = promptTextBuffer.str();
	cout.rdbuf(originalCoutBuffer);
}

void WaitForEnterPrompt(string waitForEnterPromptText) {
	Prompt& selectionMenuPrompt = Prompt::GetInstance();
	selectionMenuPrompt.StopRecordingText();

	system("cls");

	cout << waitForEnterPromptText;
	cout << "Press Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	selectionMenuPrompt.StartRecordingText();
}

SelectionMenu::SelectionMenu() {}
SelectionMenu::SelectionMenu(const vector<vector< tuple<string, function<void()>> >>& opts) : options(opts) {}

int SelectionMenu::GetLongestOptionLength() {
	if(longestOptionLength != Constants::UI::VALUE_UNSET) {
		return longestOptionLength;
	}

	int optionLength;
	for (int row = Constants::UI::INITIAL_MENU_OPTION_INDEX; row < options.size(); row++) {
		for (int col = Constants::UI::INITIAL_MENU_OPTION_INDEX; col < options[row].size(); col++) {
			optionLength = get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col]).length();
			if (optionLength > longestOptionLength) {
				longestOptionLength = optionLength;
			}
		}
	}

	return longestOptionLength;
}

int SelectionMenu::GetMaximumRowItems() {
	if(maximumRowItems != Constants::UI::VALUE_UNSET) {
		return maximumRowItems;
	}

	int rowItems;
	for (int row = Constants::UI::INITIAL_MENU_OPTION_INDEX; row < options.size(); row++) {
		rowItems = options[row].size();
		if(rowItems > maximumRowItems) {
			maximumRowItems = rowItems;
		}
	}

	return maximumRowItems;
}

void SelectionMenu::DisplayOptions() {
	int longestOptionLength = GetLongestOptionLength();
	double longestOptionLengthInTabs = (double)longestOptionLength / Constants::UI::TAB_SIZE;
	int optionsWidth = GetMaximumRowItems() * ceil(longestOptionLengthInTabs);
	int totalWidth = (optionsWidth + Constants::UI::MENU_OPTION_PADDING_TABS) * Constants::UI::TAB_SIZE + Constants::UI::MENU_HORIZONTAL_BORDER.length();
	string horizontalBorder = string(totalWidth, Constants::UI::MENU_HORIZONTAL_BORDER[0]);

	cout << horizontalBorder << endl;

	for(int row = Constants::UI::INITIAL_MENU_OPTION_INDEX; row < options.size(); row++) {
		cout << Constants::UI::MENU_VERTICAL_BORDER << '\t';

		for(int col = Constants::UI::INITIAL_MENU_OPTION_INDEX; col < options[row].size(); col++) {
			if(row == focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW] && col == focusedIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL]) {
				cout	<< Constants::UI::FOCUSED_INDEX_PRETEXT
						<< get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col])
						<< Constants::UI::FOCUSED_INDEX_POSTTEXT;
			}
			else {
				cout << get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col]);
			}
			
			double currentOptionLengthInTabs = get<Constants::UI::MENU_COMPONENTS::LABEL>(options[row][col]).length() / Constants::UI::TAB_SIZE;

			for (int tab = 0; tab <= floor(longestOptionLengthInTabs) - floor(currentOptionLengthInTabs); ++tab)
				cout << '\t';
		}

		cout << '\t' << Constants::UI::MENU_VERTICAL_BORDER << endl;
	}

	cout << horizontalBorder << endl;
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

void SelectionMenu::SetFormattedOptions(vector< tuple<string, function<void()>> > unformattedOptions) {
	vector<vector< tuple<string, function<void()>> >> formattedOptions;
	vector< tuple<string, function<void()>> > optionRow;

	for(int i = 0; i < unformattedOptions.size(); i++) {
		optionRow.push_back(unformattedOptions[i]);
		if((i + 1) % Constants::UI::MENU_ITEMS_PER_ROW == 0) {
			formattedOptions.push_back(optionRow);
			optionRow.clear();
		}
	}

	options = formattedOptions;
}

void SelectionMenu::MakeSelection() {
	Prompt& prompt = Prompt::GetInstance();
	prompt.StopRecordingText();

	while (true) {
		cout << prompt.GetText();

		DisplayOptions();

		char input = getInstantaneousCharInput();
		int inputCode = (int)input;

		system("cls");

		int selectedRow;
		int selectedCol;

		switch (inputCode) {
			case Constants::UI::UP_KEY_CODE:
				ApplyKeyModifier(Constants::UI::UP_KEY_MODIFIER);
				break;
			case Constants::UI::DOWN_KEY_CODE:
				ApplyKeyModifier(Constants::UI::DOWN_KEY_MODIFIER);
				break;
			case Constants::UI::LEFT_KEY_CODE:
				ApplyKeyModifier(Constants::UI::LEFT_KEY_MODIFIER);
				break;
			case Constants::UI::RIGHT_KEY_CODE:
				ApplyKeyModifier(Constants::UI::RIGHT_KEY_MODIFIER);
				break;
			case Constants::UI::SELECT_KEY_CODE:
				selectionIndex = focusedIndex;
				selectedRow = selectionIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::ROW];
				selectedCol = selectionIndex[Constants::UI::FOCUSED_INDEX_DIMENSION::COL];

				prompt.StartRecordingText();

				// Execute the associated action
				get<Constants::UI::MENU_COMPONENTS::ACTION>(options[selectedRow][selectedCol])();

				return;
		}
	}
}