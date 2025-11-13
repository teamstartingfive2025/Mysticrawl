#include "Lockable.h"
#include <functional>
#include <vector>

bool Lockable::isLocked() const {
    for (const function<bool()>& lockStatusFunctionSuccess : lockStatusFunctions) {
        if (!lockStatusFunctionSuccess()) {
            return true;
        }
    }
    return false;
}