#include "pch.h"
#include "CppUnitTest.h"
#include "../Mysticrawl/Weapons.h"
#include "../Mysticrawl/Item.h"
#include "../Mysticrawl/Interactable.h"
#include "../Mysticrawl/SelectionMenu.h"
#include "../Mysticrawl/Constants.h"
#include "../Mysticrawl/Prompt.h"
#include "../Mysticrawl/Input.h"

#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MysticCrawlAutomatedTestProject
{
	TEST_CLASS(MysticCrawlAutomatedTestProject)
	{
	public:

		TEST_METHOD(HelloMysticCrawl)
		{
			Logger::WriteMessage("Hello from Weapons Test\n");
		}

		// Testing the sword methods - including the inherited methods from Item
		TEST_METHOD(CreateAWeapon) {
			Logger::WriteMessage("Create a sword\n");
			Weapon sword = Weapon("sword", 8);

			Assert::AreEqual("sword", sword.getName().c_str());
			Logger::WriteMessage("Verified we can create a sword & the name returned equals what we created, next verify power is correct\n");
			Assert::AreEqual(8, sword.getWeaponPower());

			// create a second weapon with a large power, verify it also works
			Weapon merlinsWand = Weapon("Merlin's Wand", -5);
			Assert::AreEqual("Merlin's Wand", merlinsWand.getName().c_str());
			Assert::AreEqual(-5, merlinsWand.getWeaponPower());

			// change the name of our weapon
			sword.setName("Bigger Sword");
			Assert::AreEqual("Bigger Sword", sword.getName().c_str());
			Assert::AreEqual(8, sword.getWeaponPower());
		}
	};
}
