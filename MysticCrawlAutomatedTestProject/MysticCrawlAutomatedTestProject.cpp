#include "pch.h"
#include "CppUnitTest.h"

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
	};
}
