#include "Prompt.h"
#include <sstream>
#include <iostream>

using namespace std;

// Get the singleton instance of Prompt
Prompt& Prompt::GetInstance() {
	static Prompt instance;
	return instance;
}

// Start recording text output to internal buffer
void Prompt::StartRecordingText() {
	cout.rdbuf(promptTextBuffer.rdbuf());
	promptTextBuffer.str("");
}

// Stop recording text output and restore original buffer
void Prompt::StopRecordingText() {
	text = promptTextBuffer.str();
	cout.rdbuf(originalCoutBuffer);
}