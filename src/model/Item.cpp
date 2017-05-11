#include "Queue.h"
#include <memory>
#include "User.h"
Queue::Item::Item(std::unique_ptr<User> user_): user(std::move(user_)), priority(0) {}
void Queue::Item::set_priority(int priority_) {
    priority = priority_;
}