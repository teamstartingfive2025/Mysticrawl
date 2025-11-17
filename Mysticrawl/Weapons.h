#pragma once
#include <string>

namespace GameItems {

    enum class WeaponType 
    {
        Sword, Staff 
    };

    class Weapon
    {
    public:
        Weapon(WeaponType type, int power);
        WeaponType getType()const;
        int getPower() const;
        string getName() const;

    private:
        WeaponType type_;
        int power_;
    };
