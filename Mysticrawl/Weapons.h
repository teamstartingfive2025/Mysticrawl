#pragma once
#include <string>
#include "Item.h"
#include "Interactable.h"

using std::string;

class Weapon : public Item, public Interactable
{
public:
    Weapon(const string& name, int power, const string& description);

    int getWeaponPower() const {

        return power_;
    }

    string getWeaponDescription() const {

        return description_;
    }

private:
    int power_;
    string description_;
};


