#pragma once
#include <string>
#include <random>
using namespace std;

class Player; // forward decl

class Enemy {
public:
    Enemy(string n, string t, int hp = 5);

    const std::string& getName() const;
    int getHealth() const;
    bool isAlive() const;

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

private:
    string name;
	string introText = "";
    int health;

    // random engine for decisions
    std::mt19937 rng;
};