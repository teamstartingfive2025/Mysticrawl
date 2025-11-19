#include "pch.h"
#include "CppUnitTest.h"
#include "../Mysticrawl/Player.h"
#include "../Mysticrawl/Room.h"
#include "../Mysticrawl/Item.h"
#include "../Mysticrawl/Random.h"
#include "../Mysticrawl/Enemy.h"
// #include "../Mysticrawl/EnemyTemplates.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MysticCrawlAutomatedTestProject
{
	TEST_CLASS(EnemyTestClass)
	{
	public:
		string logString;
		std::unique_ptr<Room> testRoom;
		std::unique_ptr<Player> testPlayer;

		TEST_CLASS_INITIALIZE(_Setup_EnemyTestClass) {
			// this method is run once for the PlayerTest class
			//    intentionally blank (other than the log message) - nothing to initialize at this time
			Logger::WriteMessage("Player Test class initialized\n");
		}
		TEST_METHOD_INITIALIZE(_Setup_EnemyTest_Methods) {
			// this method is run at the start of each test case
			Logger::WriteMessage("Player Test case initialized\n");
			// Room constructor definition - needed for instantiating a player
			// Room(string name, string description, vector<shared_ptr<Item>> items = {}, vector<shared_ptr<Item>> hiddenItems = {});
			testRoom = std::make_unique<Room>("test room", "Test lab containing the remnants of players past");
			//     Player constructor definition (Room* currentRoom, string name, int health)
			testPlayer = std::make_unique<Player>(testRoom.get(), "dMasterL10", 999);
		}
		TEST_METHOD(HelloMysticCrawlEnemyTest)
		{
			Logger::WriteMessage("Hello from Enemy Test class\n");

		}

		// First create a basic enemy & verify (name, intro text & health)
		TEST_METHOD(BasicEnemyCreationTest) {
			Logger::WriteMessage("Creating the simplest enemy - name, intro text & health\n");
			string trollText = "Troll";
			string trollIntro = "A green slimy thing";
			int trollHP = 10;
			Enemy troll(trollText, trollIntro, trollHP);
			Assert::AreEqual(trollText, troll.getName());
			Assert::AreEqual(trollHP, troll.getHealth());
			Logger::WriteMessage("\tTroll tests passed\n");
			//  assuming enemies are alive at creation?  Not described anywhere - code indicates life = health > 0
			Assert::IsTrue(troll.isAlive());
		}  // end enemy creation tests

		TEST_METHOD(BlockAndOtherSimpleTests) {
			Logger::WriteMessage("Creating a simple enemy & checking block & other functionality\n");
			string ogreText = "Ogre";
			string ogreIntro = "A gray scaly thing";
			int ogreHP = 10;
			Enemy ogre(ogreText, ogreIntro, ogreHP);   // ogre created
			Logger::WriteMessage("Testing block() for a couple of ogres\n");
			//  not described - on creation of a more complex enemy (2nd constructor), block attribute set (int)
			//  behavior - (int) is the probability an action (e.g. attack) will be blocked
			//    notes: constructor does not validate the argument entered - so could be outside [0-99]
			//    initialized to zero, never blocked 
			for (int itr = 0; itr < 10; itr++) {
				Assert::IsFalse(ogre.block(), L"Blocked unexpectedly, given block % is zero");  // should never block, since block % initialized to zero
			}
			// create a second ogre
			// 
			// constructor - Enemy(string n, string t, int hp, int bc, int dMin, int dMax, int bec, int att, int idle, int tnt);
			int ogre2BlockPercent = 100;
			int ogre2MinDamage = 1;
			int ogre2MaxDamage = 100;  // a lot more than the initial HP
			int ogre2BlockedExitPercent = 90;
			int ogre2AttackPercent = 70;
			int ogre2IdlePercent = 0;
			int ogre2TauntPercent = 10;
			Enemy ogreV2("OgreV2", ogreIntro, ogreHP, ogre2BlockPercent, ogre2MinDamage, ogre2MaxDamage,
				ogre2BlockedExitPercent, ogre2AttackPercent, ogre2IdlePercent, ogre2TauntPercent);
			Assert::IsTrue(ogreV2.block(), L"Not blocked, should always block with 100%");  // should never block, since block % initialized to zero
			Enemy ogreV3("OgreV3", ogreIntro, ogreHP, 300, ogre2MinDamage, ogre2MaxDamage,
				ogre2BlockedExitPercent, ogre2AttackPercent, ogre2IdlePercent, ogre2TauntPercent);
			Assert::IsTrue(ogreV3.block(), L"Not blocked, should always block with 300%");  // not validated, but should always block
			Enemy ogreV4("OgreV4", ogreIntro, ogreHP, -999, ogre2MinDamage, ogre2MaxDamage,
				ogre2BlockedExitPercent, ogre2AttackPercent, ogre2IdlePercent, ogre2TauntPercent);
			Assert::IsFalse(ogreV4.block(), L"Blocked, negative %, should never block");  // not validated, negative %, but should work like 0%
			
			// checking blocked attack & exit % - uniform distribution - compute std dev & fail if outside std dev
			int sampleSize = 20;
			int ba = 50;  int blockedAttacks = 0;
			int be = 90;  int blockedExits = 0;
			Enemy ogreV5("OgreV5", ogreIntro, ogreHP, ba, ogre2MinDamage, ogre2MaxDamage,
				be, ogre2AttackPercent, ogre2IdlePercent, ogre2TauntPercent);
			for (int itr = 0; itr < sampleSize; itr++) {   // standard deviation = (100^2/12)^0.5 = 28.87
				if (ogreV5.block() == true) blockedAttacks++;
				if (ogreV5.isBlockingExit() == true) blockedExits++;
			}
			// compute lower & upper bounds expected & compare to actual
			logString = "configured Block % = " + to_string(ba) + "\tActual Blocks: " + to_string(blockedAttacks) +
				"\tSamples: " + to_string(sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			if (((blockedAttacks*100)/sampleSize < ba - 28) || ((blockedAttacks*100)/sampleSize > ba + 28)) {
				Assert::Fail(L"Blocked attacks outside expected range");
			}
			logString = "configured Exit Block % = " + to_string(be) + "\tActual Exit Blocks: " + to_string(blockedExits) +
				"\tSamples: " + to_string(sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			if (((blockedExits*100) / sampleSize < be - 28) || ((blockedExits*100) / sampleSize > be + 28)) {
				Assert::Fail(L"Blocked Exits outside expected range");
			}
		}  // end block tests

		// model for action logic
		// 
		TEST_METHOD(ActionModel) {
			Logger::WriteMessage("run a model for the action logic in Enemy.cpp\n");
			int attacks = 0;  int attackPct = 10;
			int idles = 0;    int idlePct = 40;
			int taunts = 0;   int tauntPct = 40;
			int specials = 0; int specialPct = 40;
			int sampleSize = 100;
			int choice;
			for (int itr = 0; itr < sampleSize; itr++) {
				choice = Random::GetInstance().randInt(1, 100);
				if (choice > 100 - attackPct) attacks++;
				else if (choice > 100 - attackPct - idlePct) idles++;
				else if (choice > 100 - attackPct - idlePct - tauntPct) taunts++;
				else if (choice > 100 - attackPct - idlePct - tauntPct - specialPct) specials++;
			}
			logString = "\t\tSample size = " + to_string(sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			logString = "Target attack % = " + to_string(attackPct) + "\tActual % = " + to_string(attacks * 100 / sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			logString = "Target idle % = " + to_string(idlePct) + "\tActual % = " + to_string(idles * 100 / sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			logString = "Target taunt % = " + to_string(tauntPct) + "\tActual % = " + to_string(taunts * 100 / sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
			logString = "Target special % = " + to_string(specialPct) + "\tActual % = " + to_string(specials * 100 / sampleSize) + "\n";
			Logger::WriteMessage(logString.c_str());
		}  // end action logic model

	};
}
