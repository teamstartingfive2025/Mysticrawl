#include "pch.h"
#include "CppUnitTest.h"

#include "../Mysticrawl/Weapons.h"
#include "../Mysticrawl/Item.h"
#include "../Mysticrawl/Interactable.h"
#include "../Mysticrawl/SelectionMenu.h"
#include "../Mysticrawl/Constants.h"
#include "../Mysticrawl/Prompt.h"
#include "../Mysticrawl/Input.h"
#include "../Mysticrawl/Room.h"

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
			Weapon sword = Weapon("sword", 8, "Sword's description");

			Assert::AreEqual("sword", sword.getName().c_str());
			Assert::AreEqual("Sword's description", sword.getWeaponDescription().c_str());
			Logger::WriteMessage("Verified we can create a sword & the name returned equals what we created, next verify power is correct\n");
			Assert::AreEqual(8, sword.getWeaponPower());

			// create a second weapon with a large power, verify it also works
			Weapon merlinsWand = Weapon("Merlin's Wand", -5, "Wand's description");
			Assert::AreEqual("Wand's description", merlinsWand.getWeaponDescription().c_str());
			Assert::AreEqual("Merlin's Wand", merlinsWand.getName().c_str());
			Assert::AreEqual(-5, merlinsWand.getWeaponPower());

			// change the name of our weapon
			sword.setName("Bigger Sword");
			Assert::AreEqual("Bigger Sword", sword.getName().c_str());
			Assert::AreEqual(8, sword.getWeaponPower());
		}

		TEST_METHOD(CreateRoomWithAStaff) {
			Logger::WriteMessage("Create a room with a staff\n");
			Room spawnRoom(
				"Spawn Room",
				"You awake in a dimly lit dungeon cell, confused and dazed. \n"
				"The fiery light of a torch flickers against the dark, cold walls. \n"
				"The room is barren except for a sole flowerpot resting beside a pile of stones in the corner. \n"
				"A large iron-clad door stands to the east, bearing a large lock on the handle.\n",
				{ make_shared<Item>("Torch") },
				{ make_shared<Weapon>("Staff", 5, "Staff' description")}
			);
			// vector<shared_ptr<Item>>& getItems() { return items; }
			// vector<shared_ptr<Item>>& getHiddenItems() { return hiddenItems; }
			// for (const auto& item : currentRoom->getItems())
			vector<shared_ptr<Item>> visibleItems = spawnRoom.getItems();
			vector<shared_ptr<Item>> hiddenItems = spawnRoom.getHiddenItems();
			for (const auto& itr : spawnRoom.getItems()) {
				Logger::WriteMessage(itr->getName().c_str());
				Logger::WriteMessage("\n");
			}
			Logger::WriteMessage("Printing Hidden items\n");
			for (const auto& itr : spawnRoom.getHiddenItems()) {
				Logger::WriteMessage(itr->getName().c_str());
				Logger::WriteMessage("\n");
			}
		}
	};
}
