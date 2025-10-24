#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Interactable.h"
#include "Player.h"

// The Fight class handles all combat-related player actions.
// For this story, we’re only implementing the player's basic attack.
class Fight : public Interactable {
public:
	// Displays a simple fight menu and allows the player to attack an enemy.
	// Parameters:
		//player: reference to the player object (attacker)
	Fight() {}
	void fightMenu(Player& player); 
};