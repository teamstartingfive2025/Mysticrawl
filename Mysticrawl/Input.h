#pragma once

#include <string>
using namespace std;

char getInstantaneousCharInput(); // Gets a single character input from the user without requiring Enter key press

/**
 * Display prompt text until the user presses Enter.
 */
void WaitForEnterPrompt(string waitForEnterPromptText);