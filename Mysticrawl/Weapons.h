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
        explicit Weapon(WeaponType type, int power = 5);

        WeaponType type()       const noexcept;
        std::string name()       const;        // "Sword" or "Staff"
        std::string description() const;       // short text about the weapon
        int power()      const noexcept;
        bool isEquipped() const noexcept;

        // User interactions
        void equip()   noexcept;   // mark as equipped
        void unequip() noexcept;   // mark as unequipped
        void setPower(int p) noexcept;

        // Returns a random hit value based on power
        int attackRoll() const;

        private:
        WeaponType type_;
        int        power_;
        bool       equipped_;
    };

    inline Weapon MakeSword(int power = 8) 
    {
        return Weapon(WeaponType::Sword, power);
    }
    inline Weapon MakeStaff(int power = 5) 
    {
        return Weapon(WeaponType::Staff, power); 
    }

}  


