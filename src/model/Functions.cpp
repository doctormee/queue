#include "Functions.h"

bool logical_and(bool left, bool right) {
    return (left && right);
}
bool logical_or(bool left, bool right) {
    return (left || right);
}
bool logical_not(bool pred) {
    return !pred;
}