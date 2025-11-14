#pragma once
#include "Item.h"
#include "Lockable.h"
#include "Interactable.h"
#include <vector>
#include <string>

class Container : public Lockable, Interactable {
private:
	vector<shared_ptr<Item>> items;
	string name;

public:
	Container(string name, vector<shared_ptr<Item>> items = {}, vector<function<bool()>> lockStatusFunctions = {})
		: Lockable(lockStatusFunctions), Interactable(), name(name), items(items) {}

	const vector<shared_ptr<Item>>& getItems() const { return items; }
	vector<shared_ptr<Item>>& getItems() { return items; }

	void removeItem(const shared_ptr<Item>& item);
	void openContainerSelection();
	string getName() const { return name; }
};