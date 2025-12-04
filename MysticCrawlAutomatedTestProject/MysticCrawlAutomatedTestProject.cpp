#include "pch.h"
#include "CppUnitTest.h"

#include "../Mysticrawl/Random.h"
#include "../Mysticrawl/Input.h"
#include "../Mysticrawl/Key.h"
#include "../Mysticrawl/Prompt.h"
#include "../Mysticrawl/Interactable.h"
#include "../Mysticrawl/SimpleMechanism.h"
#include "../Mysticrawl/Exit.h"
#include "../Mysticrawl/Room.h"
#include "../Mysticrawl/Player.h"
#include "../Mysticrawl/Enemy.h"
#include "../Mysticrawl/EnemyTemplates.h"
#include "../Mysticrawl/SelectionMenu.h"
#include "../Mysticrawl/Lockable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MysticCrawlAutomatedTestProject
{
	TEST_CLASS(MysticCrawlAutomatedTestProject)
	{
	public:
		
		TEST_METHOD(HelloMysticCrawl)
		{
			Logger::WriteMessage("Hello from MysticCrawlAutomatedTestProject\n");
		}

		/* Test Enemy Class Functionality */
		TEST_METHOD(CreateEnemyAndVerifyNameHP)
		{
			Logger::WriteMessage("Creating a dog rat and verifying constructor works as intended\n");
			std::string enemy = "DogRat";
			std::string enemyDescription = "A rat that is as big as a dog!";
			int initialHP = 10;
			Enemy dogRat(enemy, enemyDescription, initialHP);
			Assert::AreEqual(dogRat.getName(), enemy, L"constructor name doesn't match getName()");
			Assert::AreEqual(dogRat.getHealth(), initialHP, L"constructor HP doesn't match getHealth()");
			// can't verify initial text since this is a cout only, not returned
		}
		TEST_METHOD(VerifyDamageCalcs)  // should yield uniform distribution of 1-3
		{
			Logger::WriteMessage("Creating a NYC rat and verifying damage calc and enemy death works as expected\n");
			std::string enemy = "NYCRat";
			std::string enemyDescription = "A rat that is scavanges pizza slices!";
			int initialHP = 10;
			Enemy NYCRat(enemy, enemyDescription, initialHP);

			// verify health declines by the expected amount, note damage parameter is "unlimited" (ie not capped)
			int newHP = initialHP;
			string outputMessage;
			for (int damage = 0; damage <= 5; damage++) {

				NYCRat.takeDamage(damage);  // apply damage to rat
				newHP = newHP - damage;

				if (newHP < 0) // if health goes below zero, should be capped at zero
					newHP = 0;

				outputMessage = "Applied damage " + std::to_string(damage) + " returned health " + std::to_string(NYCRat.getHealth()) + "\n";
				Logger::WriteMessage(outputMessage.c_str());
				Assert::AreEqual(NYCRat.getHealth(), newHP, L"new enemy health not equal to prior enemy health - new damage");
			}
		}

		TEST_METHOD(VerifyNegativeDamage)
		{
			Logger::WriteMessage("Creating a NYC rat and verifying damage calc and enemy death works as expected\n");
			std::string enemy = "NYCRat";
			std::string enemyDescription = "A rat that is scavanges pizza slices!";
			int initialHP = 10;
			Enemy NYCRat(enemy, enemyDescription, initialHP);

			// verify health cannot be increased by applying negative damage modifier
			int newHP = initialHP;
			string outputMessage;
			for (int damage = -5; damage <= 0; damage++) {

				NYCRat.takeDamage(damage);  // apply damage to rat

				outputMessage = "Applied damage " + std::to_string(damage) + " returned health " + std::to_string(NYCRat.getHealth()) + "\n";
				Logger::WriteMessage(outputMessage.c_str());
				Assert::AreEqual(NYCRat.getHealth(), initialHP, L"negative/zero enemy health is equal to prior enemy health");
			}
		}
	};
}

/*
Starting 5 Enemy Class
// Enemy constructor, args string enemy name, string related text pertinent to enemy & hp - default is 5)
// initializes random seed based on current time (note - the random # generation appears to be a direct lift from the web/AI)
// Requires: enemy.cpp, pulls in chrono, random (for random # generation) & string libraries
Enemy(string n, string t, int hp = 5);

// getters 
//  getName - returns enemy name (config in constructor)
//  getHealth - returns current value of health (int - could be anything, no checks)
//  isAlive - true if enemy is alive (health value > 0), false if "dead" (health value !> 0)
const std::string& getName() const;
int getHealth() const;
bool isAlive() const;

// *** Can't test in automated test at this time, problems with creating a player ***
// Attack the player. Returns damage to be dealt to the player, LV - actual damage must be applied by caller
// attack is a uniformally random amount - currently 1-3 hps, based on mt19937 seed initialized in constructor
int attack(Player& target);

// Optionally block (not used in this simple rat example)
// hardcodes 20% chance of blocking (generates random # 0-99, checks if value < 20)
bool block();

// Apply damage to this enemy
// calculates damage to enemy, and applies the damage
// returns enemy health, but if < 0, returns 0 (net: health in range (0,initial hp-1))
void takeDamage(int amount);

// Whether this enemy will be hostile on spawn (chance-based)
// hardcodes 60% chance of attacking (generates random # 0-99, checks if value < 60)
bool hostilityTrigger();

// Display introductory text when enemy appears (LV defined in constructor)
void DisplayIntroText();
*/