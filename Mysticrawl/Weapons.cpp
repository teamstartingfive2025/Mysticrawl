#include "Weapons.h"
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
    static thread_local std::mt19937 rng
    {
        static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count())
    };

    if (type_ == WeaponType::Sword) 
    {
        std::uniform_int_distribution<int> d(std::max(1, power_ - 1), power_ + 3);
        return d(rng);
    }

    else 
    {
        std::uniform_int_distribution<int> d(std::max(1, power_ - 2), power_ + 2);
        return d(rng);
    }
}
