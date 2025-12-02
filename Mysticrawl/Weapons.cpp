#include <string>
#include "Weapons.h"
#include "Item.h"

using namespace std;

Weapon::Weapon(string name, int power, string description): Item(name), Interactable(), power_(power), description_(description) {} 



int Weapon::getWeaponPower() const
{
    return power_;
}



