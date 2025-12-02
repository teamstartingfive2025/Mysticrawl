#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "Interactable.h"
using namespace std;

// Mechanism base class for buttons and levers
// - Cannot be picked up (like items), only interacted with
// - Calls a function when used (unlock door, reveal item, etc.)

class SimpleMechanism {
private:
    string name;                     // what it's called
    bool isLever;                         // true = lever, false = button
    bool state;                           // current state (for lever only)
    function<void(bool)> onUse;      // function to call when used
    bool sticky;                    // lever that can be pulled down but not back up
    string stuckMessage = "";

public:
    // Constructor
    SimpleMechanism(const string& name, bool leverType,
        function<void(bool)> action);
    SimpleMechanism(const std::string& name, //overloaded constructor for sticky levers
        function<void(bool)> action, string stuckMessage);

    // Use the mechanism (press or toggle)
    void use();

    // Description text for display
    string getDescription() const;

	// Get current state (for locking mechanisms)
    bool getState() const { return state; }
};