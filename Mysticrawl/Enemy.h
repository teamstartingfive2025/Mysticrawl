#pragma once
#include <string>
#include <random>
using namespace std;

class Player;
class Dungeon;  
class Enemy {
public:
    Enemy(string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt);

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
    double tauntMultiplier = 1;

    // random engine for decisions
    std::mt19937 rng;
};