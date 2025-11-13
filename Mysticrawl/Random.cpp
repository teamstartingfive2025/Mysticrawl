#include "Random.h"
#include <random>

using namespace std;

// Get the singleton instance of Random
Random& Random::GetInstance() {
	static Random instance;
	return instance;
}

int Random::randInt(int lowerBound, int upperBound) {
	uniform_int_distribution<int> range(lowerBound, upperBound);
	return range(randomNumberGenerator);
}