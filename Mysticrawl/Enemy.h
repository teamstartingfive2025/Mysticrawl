#pragma once
#include <string>
#include <functional>
#include <random>
using namespace std;

class Player;
class Enemy {
public:
    Enemy(string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt);
    Enemy(function <void(Enemy*, Player& target)> sp, string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt, int spc, int spint); //overloaded constructor for enemies with special abilities
    Enemy(function <void(Enemy*, Player& target)> sp, string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt, int spc, int spint, function <void(Enemy* self, Player& target)> ef); //overloaded constructor for enemies with special abilities

    const std::string& getName() const;
    int getHealth() const;
    bool isAlive() const;

    //Decide what action to take when hostile
    void action(Player& target);

    // Attack the player. Returns damage dealt.
    int attack(Player& target);

    // Optionally block (not used in this simple rat example)
    bool block();

    // Apply damage to this enemy
    void takeDamage(int amount);

    // Whether this enemy will be hostile on spawn (chance-based)
    bool hostilityTrigger();

    // Display introductory text when enemy appears
    void DisplayIntroText();

    // Checks if the enemy is blocking an exit
    bool isBlockingExit();

    // Changes the chances of choosing each action
    void resetProbabilities(int attack, int idle, int taunt, int special);

    int getSpecialInt() { return specialInt; }

    void setSpecialInt(int x) { specialInt = x; }

    double getTauntMultiplier() { return tauntMultiplier; }

    void setTauntMultiplier(double t) { tauntMultiplier = t; }

    function <void(Enemy* self, Player& target)> getEncounterFunction() { return encounterFunction; }

    void setEncounterFunction(function<void(Enemy* self, Player& target)> func) { encounterFunction = func; }

private:
    string name;
    string introText = "";
    int health;
    int blockChance;
    int damageMin;
    int damageMax;
    int blockExitChance;
    int attackChance;
    int idleChance;
    int tauntChance;
    int specialChance;
    int specialInt; //integer used for special attacks across turns
    double tauntMultiplier = 1;
    function<void(Enemy*, Player& target)> special;
	function<void(Enemy* self, Player& player)> encounterFunction;
};