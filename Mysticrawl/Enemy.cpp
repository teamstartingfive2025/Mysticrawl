#include "Enemy.h"
#include "Player.h"
#include <chrono>
#include <random>
#include <string>
using namespace std;

Enemy::Enemy(string n, string t, int hp) : name(n), introText(t), health(hp) {
    // seed RNG with time-based seed
    rng.seed((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
}

const string& Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
bool Enemy::isAlive() const { return health > 0; }

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::block() {
    uniform_int_distribution<int> d(0, 99);
    // 20% chance to block for this enemy type (arbitrary)
    return d(rng) < 20;
}

int Enemy::attack(Player& target) {
    // For a rat: small bite damage 1-3
    uniform_int_distribution<int> dmgDist(1, 3);
    int damage = dmgDist(rng);

    // Apply damage to player
    target.applyDamage(damage);

    return damage;
}

bool Enemy::hostilityTrigger() {
    // 60% chance to be hostile on spawn
    uniform_int_distribution<int> d(0, 99);
    return d(rng) < 60;
}

void Enemy::DisplayIntroText() {
    cout << introText << endl;
}