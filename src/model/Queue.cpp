#include <Queue.h>

Queue::Item::Item( std::shared_ptr<user> user_): user(user_), priority(0) {}