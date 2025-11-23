#include <string>
#include "Item.h"
#include "Interactable.h"

class Weapon : public Item, public Interactable
{
    public:
        explicit Weapon(string weaponName, int power = 5);
        // from items - 
        // - keep this one - Item(const string name) : name(name) {}
        // add a new constructor (name, power)
        //virtual string getName() const { return name; }
        //void setName(string name) { this->name = name; }
        //virtual void use(Player* player) { cout << "Nothing happened.\\n"; return; }
        //bool isConsumable() const { return consumable; }
    
        //Weapon(const std::string& name, int power, const std::string& description)
        //    : Item(name), power_(power), description_(description)
        //{
        //}

        //WeaponType type() const noexcept;
        int getWeaponPower() const;

        // Returns a random hit value based on power
        int attackRoll() const;

    private:
        //WeaponType type_;
        int power_;
};


inline Weapon MakeSword(int power = 8) {
    
    return Weapon("Sword", power);
}

inline Weapon MakeStaff(int power = 5) {

    return Weapon("Staff", power);
}
