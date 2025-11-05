#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "Interactable.h"

// Mechanism base class for buttons and levers
// - Cannot be picked up (like items), only interacted with
// - Calls a function when used (unlock door, reveal item, etc.)

class SimpleMechanism {
private:
    std::string name;                     // what it's called
    bool isLever;                         // true = lever, false = button
    bool state;                           // current state (for lever only)
    std::function<void(bool)> onUse;      // function to call when used

public:
    // Constructor
    SimpleMechanism(const std::string& name, bool leverType,
        std::function<void(bool)> action);

    // Use the mechanism (press or toggle)
    void use();

    // Description text for display
    std::string getDescription() const;
};