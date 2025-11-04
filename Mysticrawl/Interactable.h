#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "SelectionMenu.h"

class SelectionMenu;

/**
 * Base class for any interactable object in the game.
 * Contains a refreshable selection menu for user interactions.
 */
class Interactable {
private:
    SelectionMenu menu;
public:
    Interactable() {};
    void SelectMenuOption();
	void RefreshSelectionMenu(vector< tuple<string, function<void()>> > unformattedOptions);
};