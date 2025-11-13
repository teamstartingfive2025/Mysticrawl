#include "Input.h"
#include "Prompt.h"
#include <iostream>
#include <conio.h>

char getInstantaneousCharInput() {
	char input = _getch();
	return input;
}

// Utility function to wait for user to press Enter
void WaitForEnterPrompt(string waitForEnterPromptText) {
	Prompt& selectionMenuPrompt = Prompt::GetInstance();
	selectionMenuPrompt.StopRecordingText();

	system("cls");

	cout << waitForEnterPromptText;
	cout << "Press Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	selectionMenuPrompt.StartRecordingText();
}