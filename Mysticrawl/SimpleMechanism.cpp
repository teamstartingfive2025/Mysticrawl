#include "SimpleMechanism.h"

// Constructor
SimpleMechanism::SimpleMechanism(const std::string& name, bool leverType,
    function<void(bool)> action):
    name(name),           // Store the mechanism’s display name
    isLever(leverType),   // True = lever, False = button
    state(false),         // Start with default state (lever up)
    onUse(action),
    sticky (false) {}      // Store the function that runs when used

SimpleMechanism::SimpleMechanism(const std::string& name, //overloaded constructor for sticky levers
    function<void(bool)> action, string stuckMessage) :
    name(name),           // Store the mechanism’s display name
    state(false),         // Start with default state (lever up)
    onUse(action),      // Store the function that runs when used
    sticky(sticky),
    stuckMessage(stuckMessage) {}


// use()
// Handles what happens when the player interacts with this mechanism.
// If it’s a lever, it toggles up/down each time.
// If it’s a button, it just runs once and plays a message.

void SimpleMechanism::use() {
    if (isLever) {
        if (sticky && state) { //down sticky levers do nothing
            cout << stuckMessage << endl;
            return;
        }

        // Flip the lever’s state
        state = !state;

        // Print a simple message describing the change
        cout << "You pull the " << name << " ";

        if (state) {
            cout << "down";
        }
        else {
            cout << "up";
        }

        cout << ".\n";


        // Run the lever’s action with its current state
        // (true = down, false = up)
        onUse(state);
    }
    else {
        // For buttons, we don’t change state — just trigger the event once
        cout << "You press the " << name
            << ". A distant clank echoes...\n";

        // Call the assigned function 
        onUse(true);
    }
}


// getDescription()
// Returns a short description for display in the room.
string SimpleMechanism::getDescription() const {
    string description = name + " ";

    if (isLever) {
        if (state) {
            description += "(down)";
        }
        else {
            description += "(up)";
        }
    }
    else {
        description;
    }

    return description;
}
