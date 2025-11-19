#include "Weapons.h"

Weapon::Weapon(WeaponType type, int power)
    : type_(type), power_(power)
{
}

WeaponType Weapon::getType() const
{
    return type_;
}

int Weapon::getPower() const
{
    return power_;
}

std::string Weapon::getName() const
{
    switch (type_)
    {
    case WeaponType::Sword: return "Sword";
    case WeaponType::Staff: return "Staff";
    }
    return "Unknown Weapon";
}

