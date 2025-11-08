#pragma once
#include "Enemy.h"

class Enemy;

extern Enemy RatTemplate = Enemy("Rat", "A rat suddenly appears! I hope it doesn't have rabies...\n", 
	5, //hit points
	20,//block chance (%)
	1, //min damage
	3, //max damage
	40 //block exit chance (%)
);
