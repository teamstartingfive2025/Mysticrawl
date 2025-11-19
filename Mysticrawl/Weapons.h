#pragma once
#include <string>

enum class WeaponType
{
    Sword,
    Staff
};

class Weapon
{
public:
    Weapon(WeaponType type, int power);

    WeaponType getType() const;
    int getPower() const;
    std::string getName() const;

private:
    WeaponType type_;
    int power_;
};
