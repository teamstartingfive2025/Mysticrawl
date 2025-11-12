#include "Enemy.h"
#include "Player.h"
#include "Random.h"
#include "Input.h"
#include <string>
using namespace std;

Enemy::Enemy(string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt) : name(n), introText(t), health(hp), blockChance(bc), damageMin(dMin), damageMax(dMax), blockExitChance(bec), attackChance(att), idleChance(idle), tauntChance(tnt) {
    specialChance = 0;
    specialInt = 0;
}

Enemy::Enemy(function <void(Enemy*, Player& target)> sp, string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt, int spc, int spint)
    : name(n), introText(t), health(hp), blockChance(bc), damageMin(dMin), damageMax(dMax), blockExitChance(bec), attackChance(att), idleChance(idle), tauntChance(tnt), special(sp), specialChance(spc), specialInt(spint) {
}

const string& Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
bool Enemy::isAlive() const { return health > 0; }

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::block() {
    return Random::GetInstance().randInt(0, 99) < blockChance;
}

void Enemy::action(Player& target) {
    int choice = Random::GetInstance().randInt(1, 100);

    if (choice > (100 - attackChance)) //chance to attack
    {
        int damage = attack(target);

    }
    else if (choice > (100 - attackChance - idleChance)) //chance to idle
    {
        cout << "\nRat idles!\n";
    }
    else if (choice > (100 - attackChance - idleChance - tauntChance)) //chance to taunt
    {
        tauntMultiplier += 0.5;
        cout << "\nRat taunts!  Attack strength multiplier increased to " << (int)(tauntMultiplier * 100) << "%\n";
    }
    else if (choice > (100 - attackChance - idleChance - tauntChance - specialChance)) //chance to use special attack
    {
        special(this, target);
    }

}

int Enemy::attack(Player& target) {
    // For a rat: small bite damage 1-3
    int damage = Random::GetInstance().randInt(damageMin, damageMax);

    // Apply damage to player
    target.takeDamage(damage);
    tauntMultiplier = 1;

    string attackMessage = name + " attacked you, health decreased by " + to_string(damage);

    if (target.getHealth() <= 0) {
        WaitForEnterPrompt(attackMessage + Constants::Gameplay::GAME_OVER_TEXT);
        return damage;
    }

    cout << endl << attackMessage << endl;

    return damage;
}

bool Enemy::hostilityTrigger() {
    // 60% chance to be hostile on spawn
    return Random::GetInstance().randInt(0, 99) < 60;
}

bool Enemy::isBlockingExit() {
    // Tune as needed
    return Random::GetInstance().randInt(0, 99) < 40; // 40% success
}

void Enemy::resetProbabilities(int attack, int idle, int taunt, int special) {
    if (attack + idle + taunt + special == 100) {
        attackChance = attack;
        idleChance = idle;
        tauntChance = taunt;
        specialChance = special;
    }
}

void Enemy::DisplayIntroText() {
    cout << introText << endl;
}