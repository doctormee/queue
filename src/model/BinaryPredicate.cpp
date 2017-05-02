/*
#pragma once
#include <memory>
class Predicate;

class BinaryPredicate: public Predicate {
    std::shared_ptr<Predicate> left, right;
    bool (*eval_function)();
public:
    BinaryPredicate(std::shared_ptr<Predicate> &&, std::shared_ptr<Predicate> &&, bool (*)()); //constructs new Binary Predicate with eval_function

};
*/
#include "BinaryPredicate.h"

BinaryPredicate::BinaryPredicate(std::shared_ptr<Predicate> &&l, std::shared_ptr<Predicate> &&r, bool (*func)(bool, bool)): left(l), right(r), eval_function(func){} //constructs new Binary Predicate with eval_function

bool BinaryPredicate::eval(User &user) {
    return eval_function(left->eval(user), right->eval(user));
}
