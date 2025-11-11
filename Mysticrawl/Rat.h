#pragma once
#include "Enemy.h"
#include "Player.h"
#include <chrono>
#include <random>
#include <string>
using namespace std;

class Player;

class Rat : public Enemy {
private:
public:
	Rat(string n, string t, int hp);
};