#include "pch.h"
#include "CppUnitTest.h"
#include "../Mysticrawl/Player.h"
#include "../Mysticrawl/Room.h"
// #include "../Mysticrawl/Enemy.h"
// #include "../Mysticrawl/EnemyTemplates.h"

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
			logString = "Room Name: " + testPlayer->getPlayerName() + "\Max health: " + std::to_string(testPlayer->getMaxHealth()) + "\n";
			Logger::WriteMessage(logString.c_str());
		}
	};
}