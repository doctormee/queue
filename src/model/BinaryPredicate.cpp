/*
#pragma once
#include <memory>
#include "Predicate.h"
class User;

class BinaryPredicate: public Predicate {
    std::shared_ptr<Predicate> left, right;
    bool (*eval_function)(bool, bool);
public:
    BinaryPredicate(std::shared_ptr<Predicate> &&, std::shared_ptr<Predicate> &&, bool (*)(bool, bool)); //constructs new Binary Predicate with eval_function
    bool eval(User &);
};
*/
#include "BinaryPredicate.h"
#include "Functions.h"
BinaryPredicate::BinaryPredicate(std::shared_ptr<Predicate> &left_, std::shared_ptr<Predicate> &right_, bool (*func)(bool, bool)): left(left_), right(right_), eval_function(func){} //constructs new Binary Predicate with eval_function

bool BinaryPredicate::eval(User &user) {
    return eval_function(left->eval(user), right->eval(user));
}
