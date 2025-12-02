#include "Weapons.h"

using std::string;

// Constructor with name, power & description
Weapon::Weapon(const string& name, int power, const string& description)
    : Item(name), Interactable(), power_(power), description_(description){}



