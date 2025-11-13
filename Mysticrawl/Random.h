#pragma once
#include "Random.h"
#include <random>
#include <chrono>

using namespace std;

class Random {
private:
	mt19937 randomNumberGenerator;
	void seedRandomNumberGenerator() { 
		randomNumberGenerator.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
	};

public:
	Random() { seedRandomNumberGenerator(); }
	Random(const Random&) = delete; // Disable copy constructor
	static Random& GetInstance(); // Singleton access method
	int randInt(int upperBound, int lowerBound);
};