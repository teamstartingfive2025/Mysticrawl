#include "Enemy.h"
#include "Rat.h"
#include "Player.h"
#include <chrono>
#include <random>
#include <string>
using namespace std;

class Player;

Rat::Rat(string n, string t, int hp) : Enemy(n, t, hp, 20, 1, 3) {}