#include "Enemy.h"
#include "Player.h"
#include "Random.h"
#include "Input.h"
#include <string>
using namespace std;

Enemy::Enemy(string n, string t, int hp) : name(n), introText(t), health(hp) {}

Enemy::Enemy(string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt) : name(n), introText(t), health(hp), blockChance(bc), damageMin(dMin), damageMax(dMax), blockExitChance(bec), attackChance(att), idleChance(idle), tauntChance(tnt) {
    specialChance = 0;
    specialInt = 0;
}

Enemy::Enemy(function <void(Enemy*, Player& target)> sp, string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt, int spc, int spint)
    : name(n), introText(t), health(hp), blockChance(bc), damageMin(dMin), damageMax(dMax), blockExitChance(bec), attackChance(att), idleChance(idle), tauntChance(tnt), special(sp), specialChance(spc), specialInt(spint) {
}

Enemy::Enemy(function <void(Enemy*, Player& target)> sp, string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt, int spc, int spint, function <void(Enemy* self, Player& target)> ef)
    : name(n), introText(t), health(hp), blockChance(bc), damageMin(dMin), damageMax(dMax), blockExitChance(bec), attackChance(att), idleChance(idle), tauntChance(tnt), special(sp), specialChance(spc), specialInt(spint), encounterFunction(ef) {
}

const string& Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
bool Enemy::isAlive() const { return health > 0; }

void Enemy::takeDamage(int amount) {
	if (amount < 0) return;

    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::block() {
    return Random::GetInstance().randInt(0, 99) < blockChance;
}

void Enemy::action(Player& target) {
    int choice = Random::GetInstance().randInt(1, 100);

    if (choice > (100 - idleChance)) //chance to idle
    {
        cout << endl << name << " idles!\n";
    }
    else if (choice > (100 - idleChance - tauntChance)) //chance to taunt
    {
        tauntMultiplier += 0.5;
        cout << endl << name << " taunts! Attack strength multiplier increased to " << (int)(tauntMultiplier * 100) << " % \n";
    }
    else if (!target.isDefending())
    {
        if (choice > (100 - idleChance - tauntChance - attackChance)) //chance to attack
        {
            int damage = attack(target);
        }
        else if (choice > (100 - attackChance - idleChance - tauntChance - specialChance)) //chance to use special attack
        {
            special(this, target);
        }
    }
    else
    {
        cout << "\nYou defended against the " << name << "'s attack.\n";
    }
}

/*
 * For automated test, DON't call this method, need initialized player, but player requires initialized rooms, which are buried in the main game loop function
 *   Note: player object is not accessible, nor are the rooms accessible outside the main game loop function - need to refactor for test automation
 */

int Enemy::attack(Player& target) {
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
}  // END of method to be EXCLUDED from test automation

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