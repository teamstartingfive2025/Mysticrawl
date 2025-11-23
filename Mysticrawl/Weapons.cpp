#include <string>
#include "Weapons.h"
#include "Item.h"

Weapon::Weapon(string name, int power)
    : Item(name), power_(power) {}

/*WeaponType Weapon::getType() const
{
    return type_;
}*/

int Weapon::getWeaponPower() const
{
    return power_;
}

/*std::string Weapon::getName() const
{
    switch (type_)
    {
    case WeaponType::Sword: return "Sword";
    case WeaponType::Staff: return "Staff";
    }
}*/

