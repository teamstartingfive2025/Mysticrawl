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

class Prompt {
private:
    string text;
    streambuf* originalCoutBuffer = cout.rdbuf();
    ostringstream promptTextBuffer;
    Prompt() { StartRecordingText(); }

public:
    Prompt(const Prompt&) = delete;
    static Prompt& GetInstance();

    void StartRecordingText();
    void StopRecordingText();

	string GetText() const { return text; }
};

class SelectionMenu {
private:
    vector<vector< tuple<string, function<void()>> >> options;
    array<int, Constants::UI::MENU_OPTION_DIMENSIONS> focusedIndex;
    array<int, Constants::UI::MENU_OPTION_DIMENSIONS> selectionIndex;
	int longestOptionLength = Constants::UI::VALUE_UNSET;
    int maximumRowItems = Constants::UI::VALUE_UNSET;

    void DisplayOptions();
    void ApplyKeyModifier(const array<int, Constants::UI::MENU_OPTION_DIMENSIONS> modifier);
	int GetLongestOptionLength();
    int GetMaximumRowItems();

public:
    SelectionMenu();
    SelectionMenu(const vector<vector< tuple<string, function<void()>> >>& opts);

    void SetFormattedOptions(vector< tuple<string, function<void()>> >);
    void MakeSelection();
};