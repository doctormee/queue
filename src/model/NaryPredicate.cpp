/*
#pragma once
#include <memory>
#include "Predicate.h"
class Visitor;
class NaryPredicate: public Predicate {
    std::shared_ptr<Predicate> left;
    std::shared_ptr<Predicate> right;
public:
    std::shared_ptr<Predicate> get_left();
    std::shared_ptr<Predicate> get_right();
};
*/
#include "NaryPredicate.h"
void NaryPredicate::add(std::shared_ptr<Predicate> f) { 
    if (!f) {
        throw std::logic_error("Null pointer is added");
    }
    operands.push_back(f);
}
std::vector<std::shared_ptr<Predicate>>::const_iterator NaryPredicate::begin() const {
    return operands.cbegin();
}
std::vector<std::shared_ptr<Predicate>>::const_iterator NaryPredicate::end() const {
    return operands.cend();
}