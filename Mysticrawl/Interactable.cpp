#include "Interactable.h"
#include "SelectionMenu.h"

void Interactable::SelectMenuOption() {
    menu.MakeSelection();
}

void Interactable::RefreshSelectionMenu(vector< tuple<string, function<void()>> > unformattedOptions) {
	menu.SetFormattedOptions(unformattedOptions);
}