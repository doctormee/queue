#include "Queue.h"
#include "User.h"
#include <algorithm>
void Queue::push(std::unique_ptr<User> &user_) {
    std::unique_ptr<Item> tmp{new Item{user_}};
    container.push_back(std::move(tmp));
}

void Queue::remove(int uid) {
    for (auto i = container.begin(); i != container.end(); ++i) {
        if (((*i)->user->get_uid()) == uid) {
            container.erase(i);
            break;
        }
    }
}

bool Queue::queue_less(
    const std::unique_ptr<Item> &left, 
    const std::unique_ptr<Item> &right)
{
    return (left->priority > right->priority);
}

void Queue::sort() {
    std::sort(container.begin(), container.end(), Queue::queue_less);
}

std::vector<std::unique_ptr<Queue::Item>>::iterator Queue::begin() {
    return container.begin();
}
std::vector<std::unique_ptr<Queue::Item>>::iterator Queue::end() {
    return container.end();
}

int Queue::size() {
    return container.size();
}

User &Queue::get_user(int uid) {
    for (auto i = container.begin(); i != container.end(); ++i) {
        if (((*i)->user->get_uid()) == uid) {
            return *((*i)->user);
        }
    }
    throw std::out_of_range("No such User!");
}
