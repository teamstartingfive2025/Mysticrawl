#pragma once

#include <string>
using namespace std;

class Item {
private:
	string name;
public:
	Item(const string name) : name(name) {}
	virtual string getName() const { return name; }
};