#include "Weapons.h"
#include "Random.h"
#include <random>
#include <chrono>
#include <string>
#include <algorithm> 

using namespace GameItems;

Weapon::Weapon(WeaponType t, int p) : type_(t), power_(std::max(0, p)), equipped_(false) {}

WeaponType Weapon::type() const noexcept 
{
    return type_;
}

std::string Weapon::name() const 
{
    return (type_ == WeaponType::Sword) ? "Sword" : "Staff";
}

std::string Weapon::description() const
{
    if (type_ == WeaponType::Sword)
    {
        return "A sword suited for physical strikes.";
    }

    else
    {
        return "A staff that channels immense force.";
    }
}

int Weapon::power() const noexcept 
{
    return power_;
}

bool Weapon::isEquipped() const noexcept 
{
    return equipped_;
}

void Weapon::equip() noexcept 
{
    equipped_ = true;
}

void Weapon::unequip() noexcept 
{
    equipped_ = false;
}

void Weapon::setPower(int p) noexcept 
{
    power_ = std::max(0, p);
}

int Weapon::attackRoll() const 
{
    if (type_ == WeaponType::Sword) 
        return Random::GetInstance().randInt(std::max(1, power_ - 1), power_ + 3);
    else 
        return Random::GetInstance().randInt(std::max(1, power_ - 2), power_ + 2);
}
