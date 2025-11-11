#include "Enemy.h"
#include "Player.h"
#include "Random.h"
#include <string>
using namespace std;

const string& Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
bool Enemy::isAlive() const { return health > 0; }

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::block() {
    // 20% chance to block for this enemy type (arbitrary)
    return Random::GetInstance().randInt(0, 99) < 20;
}

int Enemy::attack(Player& target) {
    // For a rat: small bite damage 1-3
    int damage = Random::GetInstance().randInt(1, 3);

    // Apply damage to player
    target.takeDamage(damage);

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

void Enemy::DisplayIntroText() {
    cout << introText << endl;
}