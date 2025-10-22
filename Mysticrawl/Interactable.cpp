#include "Interactable.h"
#include "UI.h"

void Interactable::SelectMenuOption() {
    menu.MakeSelection();
}

void Interactable::RefreshSelectionMenu(vector< tuple<string, function<void()>> > unformattedOptions) {
	menu.SetFormattedOptions(unformattedOptions);
}