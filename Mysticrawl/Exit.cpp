#include "Exit.h"

#include <stdio.h>

// Check if the exit is locked by evaluating all lock status functions
bool Exit::isLocked() const {
    for (const function<bool()>& lockStatusFunctionSuccess : lockStatusFunctions) {
        if (!lockStatusFunctionSuccess()) {
            return true;
        }
    }
    return false;
}