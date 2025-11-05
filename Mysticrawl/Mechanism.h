#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "Interactable.h"

// Mechanism base class for buttons and levers
// - Cannot be picked up (like items), only interacted with
// - Calls a function when used (unlock door, reveal item, etc.)

class Mechanism : public Interactable {
protected:
    bool isLever;                          // true = lever, false = button
    bool state;                            // current state (for lever)
    std::function<void(bool)> action;      // callback for triggering environment effects

public:
    Mechanism(const std::string& name, bool leverType, std::function<void(bool)> onUse);

    // Virtual function to override in derived classes
    virtual void use() = 0;

    // Common helper functions
    bool getState() const;
    std::string getDescription() const override;
};