#pragma once
#include <string>
#include <random>

class Player; // forward decl

class Enemy {
public:
    enum class Type { Rat };

    Enemy(Type t = Type::Rat, int hp = 5);

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

private:
    Type type;
    std::string name;
    int health;

    // random engine for decisions
    std::mt19937 rng;
};