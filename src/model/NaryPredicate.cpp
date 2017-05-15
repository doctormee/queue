#include "NaryPredicate.h"
void NaryPredicate::add(std::shared_ptr<Predicate> f) { 
    if (!f) {
        throw std::logic_error("Empty predicate (i.e. nullptr) is added");
    }
    operands.push_back(f);
}
std::vector<std::shared_ptr<Predicate>>::const_iterator
NaryPredicate::begin() const {
    return operands.cbegin();
}
std::vector<std::shared_ptr<Predicate>>::const_iterator
NaryPredicate::end() const {
    return operands.cend();
}