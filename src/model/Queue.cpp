#include <Queue.h>
Queue::Item::Item(std::shared_ptr<User> user_): user(user_), priority(0) {}
