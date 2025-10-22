#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "UI.h"

class SelectionMenu;

class Interactable {
private:
    SelectionMenu menu;
public:
    Interactable() {};
    void SelectMenuOption();
	void RefreshSelectionMenu(vector< tuple<string, function<void()>> > unformattedOptions);
};