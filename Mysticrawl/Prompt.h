#pragma once

#include <sstream>
#include <iostream>

using namespace std;

/**
 * Singleton class to capture prompt text output.
 * This class redirects cout to an internal buffer to record,
 * so long as the menu is actively not being displayed.
 */
class Prompt {
private:
	string text;
	streambuf* originalCoutBuffer = cout.rdbuf(); // Store cout original buffer
	ostringstream promptTextBuffer;
	Prompt() { StartRecordingText(); }

public:
	Prompt(const Prompt&) = delete; // Disable copy constructor
	static Prompt& GetInstance(); // Singleton access method

	void StartRecordingText(); // Redirect cout to internal buffer
	void StopRecordingText(); // Restore original cout buffer

	string GetText() const { return text; } // Get captured prompt text
};
