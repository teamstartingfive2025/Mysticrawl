#pragma once
#include "UI.h"
#include "Constants.h"
#include "Input.h"
#include <vector>
#include <array>
#include <functional>
#include <tuple>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * Singleton class to capture prompt text output.
 * This class redirects cout to an internal buffer to record,
 * so long as the menu is actively not being displayed.
 */
class Prompt {
private:
    string text;
	streambuf* originalCoutBuffer = cout.rdbuf(); // Store cout original buffer
    ostringstream promptTextBuffer;
    Prompt() { StartRecordingText(); }

public:
	Prompt(const Prompt&) = delete; // Disable copy constructor
	static Prompt& GetInstance(); // Singleton access method

	void StartRecordingText(); // Redirect cout to internal buffer
	void StopRecordingText(); // Restore original cout buffer

	string GetText() const { return text; } // Get captured prompt text
};

/**
 * Display prompt text until the user presses Enter.
 */
void WaitForEnterPrompt(string waitForEnterPromptText);

/**
 * Displays a selection menu with options arranged in a grid.
 * The options can either be fomratted manually or set using a single vector.
 * A border is drawn around the menu, and the currently focused option is highlighted.
 * The Prompt singlton is used to capture any prompt text output while the menu is not displayed.
 */
class SelectionMenu {
private:
	vector<vector< tuple<string, function<void()>> >> options; // 2D vector of menu options (string, action)
	array<int, Constants::UI::MENU_OPTION_DIMENSIONS> focusedIndex; // Currently focused option index
	array<int, Constants::UI::MENU_OPTION_DIMENSIONS> selectionIndex; // Currently selected option index
	int longestOptionLength = Constants::UI::VALUE_UNSET; // Length of the longest option string
	int maximumRowItems = Constants::UI::VALUE_UNSET; // Maximum number of items per row

	void DisplayOptions(); // Display the menu options with borders and highlighting
	void ApplyKeyModifier(const array<int, Constants::UI::MENU_OPTION_DIMENSIONS> modifier); // Apply a key modifier to the focused index
	int GetLongestOptionLength(); // Calculate the length of the longest option string
	int GetMaximumRowItems(); // Calculate the maximum number of items per row

public:
    SelectionMenu();
    SelectionMenu(const vector<vector< tuple<string, function<void()>> >>& opts);

	void SetFormattedOptions(vector< tuple<string, function<void()>> >); // Set menu options from a single vector, formatting into a grid
	void MakeSelection(); // Display the menu and handle user input for selection
};