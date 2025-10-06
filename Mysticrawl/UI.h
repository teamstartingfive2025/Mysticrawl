#pragma once
#include "UI.h"
#include "Constants.h"
#include "Input.h"
#include <vector>
#include <array>
#include <functional>
#include <tuple>
#include <iostream>

using namespace std;

class SelectionMenu {
private:
    vector<vector< tuple<string, function<void()>> >> options;
    array<int, Constants::UI::MENU_OPTION_DIMENSIONS> focusedIndex;
    array<int, Constants::UI::MENU_OPTION_DIMENSIONS> selectionIndex;

    void DisplayOptions();
    void ApplyKeyModifier(const array<int, Constants::UI::MENU_OPTION_DIMENSIONS> modifier);

public:
    SelectionMenu(const vector<vector< tuple<string, function<void()>> >>& opts);

    bool MakeSelection();
};