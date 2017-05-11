/*
#pragma once
#include <memory>
#include "Predicate.h"
class Visitor;
class BinaryPredicate: public Predicate {
    std::shared_ptr<Predicate> left;
    std::shared_ptr<Predicate> right;
public:
    std::shared_ptr<Predicate> get_left();
    std::shared_ptr<Predicate> get_right();
};
*/
#include "BinaryPredicate.h"

std::shared_ptr<Predicate> BinaryPredicate::get_left() {
    return left;
}
std::shared_ptr<Predicate> BinaryPredicate::get_right() {
    return right;
}
