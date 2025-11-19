#include "pch.h"
#include "CppUnitTest.h"
#include "../Mysticrawl/Player.h"
#include "../Mysticrawl/Room.h"
#include "../Mysticrawl/Item.h"
// #include "../Mysticrawl/Enemy.h"
// #include "../Mysticrawl/EnemyTemplates.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MysticCrawlAutomatedTestProject
{
	TEST_CLASS(PlayerTestClass)
	{
	public:
		string logString;
		std::unique_ptr<Room> testRoom;
		std::unique_ptr<Player> testPlayer;

		TEST_CLASS_INITIALIZE(_Setup_PlayerTestClass){
			// this method is run once for the PlayerTest class
			//    intentionally blank (other than the log message) - nothing to initialize at this time
			Logger::WriteMessage("Player Test class initialized\n");
		}
		TEST_METHOD_INITIALIZE(_Setup_PlayerTest_Methods) {
			// this method is run at the start of each test case
			Logger::WriteMessage("Player Test case initialized\n");
			// Room constructor definition - needed for instantiating a player
			// Room(string name, string description, vector<shared_ptr<Item>> items = {}, vector<shared_ptr<Item>> hiddenItems = {});
			testRoom = std::make_unique<Room>("test room", "Test lab containing the remnants of players past");
			//     Player constructor definition (Room* currentRoom, string name, int health)
			testPlayer = std::make_unique<Player>(testRoom.get(), "dMasterL10", 999);
		}


		TEST_METHOD(HelloMysticCrawl)
		{
			Logger::WriteMessage("Hello from Player Test class\n");

		}

		// demo the initialization method correctly creates the testRoom, can add asserts to make these valid test cases
		TEST_METHOD(VerifyTestRoomCreated) {
			Logger::WriteMessage("Showing results of test room in the test case initializer\n");
			logString = "Room Name: " + testRoom->getName() + "\tRoom description: " + testRoom->getDescription() + "\n";
			Logger::WriteMessage(logString.c_str());
		}

		// demo the initialization method correctly creates the test Player, can add asserts to make these valid test cases
		TEST_METHOD(VerifyPlayerCreated) {
			Logger::WriteMessage("Showing results of player creation test method\n");
			logString = "Room Name: " + testPlayer->getPlayerName() + "\tMax health: " + std::to_string(testPlayer->getMaxHealth()) + "\n";
			Logger::WriteMessage(logString.c_str());
		}

		// create test items, add them to our test room & then,
		//   have our player pickup the items, which should remove them from the remove
		TEST_METHOD(CreateSomeItems) {
			Logger::WriteMessage("Create a couple of items & show their names\n");
			auto pot = std::make_shared<Item> ("mexican grown");
			auto hash = std::make_shared<Item> ("hashish");
			auto bong = std::make_shared < Item> ("a bong");
			logString = "pot " + pot->getName() + "\thash " + hash->getName() + "\tbong " + bong->getName() + "\n";
			Logger::WriteMessage(logString.c_str());

			// now add the items to our room
			testRoom->addItem(pot);
			testRoom->addItem(hash);
			testRoom->addItem(bong);

			// retrieve the items from the room, note - there appears no way to delete an item from the room
			vector<shared_ptr<Item>> testRoomItems = testRoom->getItems();
			logString = "items in our test room: ";
			for (auto& item : testRoomItems) {
				logString += item->getName() + "\t";
			}
			logString += "\n";
			Logger::WriteMessage(logString.c_str());

			// simple player inventory test
			//   pick up items & verify the player now has them, and the room is now empty
			//   note - the player pickup() method uses an interactive menu to pickup each item, which doesn't work for unit testing
			//     so we added a new method to pickup the items without user interaction
			Assert::IsTrue(testPlayer->inventoryEmpty());
			int numItemsPickedUp = testPlayer->pickupImmediately();   // picks up items from the current room - which should be our test room
			logString = "Player picked up " + std::to_string(numItemsPickedUp) + " items\n";
			Logger::WriteMessage(logString.c_str());
			Assert::IsTrue(testPlayer->hasItem(hash));
			Assert::IsFalse(testPlayer->inventoryEmpty());   // inventory should no longer be empty
			  // also verify the room no longer has the three items
			Assert::IsTrue(testRoom->getItems().empty());
		}
	};
}