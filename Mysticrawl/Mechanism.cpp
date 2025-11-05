#include "Mechanism.h"

// Constructor
SimpleMechanism::SimpleMechanism(const std::string& name, bool leverType,
    std::function<void(bool)> action)
    : name(name),           // Store the mechanism’s display name
    isLever(leverType),   // True = lever, False = button
    state(false),         // Start with default state (lever up)
    onUse(action) {}      // Store the function that runs when used


// ------------------------------------------------------------
// use()
// ------------------------------------------------------------
// Handles what happens when the player interacts with this mechanism.
// If it’s a lever, it toggles up/down each time.
// If it’s a button, it just runs once and plays a message.
// ------------------------------------------------------------
void SimpleMechanism::use() {
    if (isLever) {
        // Flip the lever’s state
        state = !state;

        // Print a simple message describing the change
        std::cout << "You pull the " << name << " "
            << (state ? "down" : "up") << ".\n";

        // Run the lever’s action with its current state
        // (true = down, false = up)
        onUse(state);
    }
    else {
        // For buttons, we don’t change state — just trigger the event once
        std::cout << "You press the " << name
            << ". A distant clank echoes...\n";

        // Call the assigned function (pass true to indicate activation)
        onUse(true);
    }
}


// ------------------------------------------------------------
// getDescription()
// ------------------------------------------------------------
// Returns a short description for display in the room.
// This is what the player sees when they “look” or “investigate.”
// ------------------------------------------------------------
std::string SimpleMechanism::getDescription() const {
    if (isLever)
        return name + " (" + (state ? "down" : "up") + ")";
    return name + " (button)";
}
