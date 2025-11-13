#include "Container.h"
#include "Interactable.h"
#include <vector>

void Container::removeItem(const shared_ptr<Item>& item) {
	auto itemForRemoval = find(items.begin(), items.end(), item);
	if (itemForRemoval != items.end()) {
		items.erase(itemForRemoval);
	}
}

void Container::openContainerSelection() {
	if(items.empty()) {
		cout << "The " << name << " is empty.\n";
		return;
	}

	if(isLocked()) {
		cout << "The " << name << " is locked.\n";
		return;
	}

	vector<tuple<string, function<void()>>> itemOptions;
	for (const auto& item : items) {
		itemOptions.push_back({ item->getName(), [this, item]() { 
			cout << "You take the " << item->getName() << " from the container.\n";
			removeItem(item);
		} });
	}

	RefreshSelectionMenu(itemOptions);
	SelectMenuOption();
}