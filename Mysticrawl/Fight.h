#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Interactable.h"
#include "Player.h"
#include <random>
#include <chrono>

// The Fight class handles all combat-related player actions.
// For this story, we’re only implementing the player's basic attack.
class Fight : public Interactable {
public:
	// Displays a simple fight menu and allows the player to attack an enemy.
	// Parameters:
		//player: reference to the player object (attacker)
	Fight() {}
	void fightMenu(Player& player);
	// Run attempt methods (Story: "Flee from battle")
	void AttemptRun(Player& player, Enemy& enemy, bool& battleEnded);
	bool CalculateRunChance();
	void HandleRunOutcome(bool success, Player& player, Enemy& enemy, bool& battleEnded);

};