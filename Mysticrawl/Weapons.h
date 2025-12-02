#pragma once
#include <string>
#include "Item.h"
#include "Interactable.h"

// Weapons class (child of Item & Interactable)
class Weapon : public Item, public Interactable
{
public:
    // New constructor with name, power & description
    Weapon(const std::string& name, int power, const std::string& description);


    // New method - getWeaponPower
    int getWeaponPower() const noexcept
    {
        return power_;
    }

    // New method - getWeaponDescription
    std::string getWeaponDescription() const
    {
        return description_;
    }



private:
    int power_;
    std::string description_;
};

