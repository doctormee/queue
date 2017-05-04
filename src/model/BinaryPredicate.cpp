/*
#pragma once
#include <memory>
#include "Predicate.h"
class User;

class BinaryPredicate: public Predicate {
    typedef bool (*BinaryLogicalFunction)(bool, bool);
    std::shared_ptr<Predicate> left, right;
    BinaryLogicalFunction eval_function;
public:
    BinaryPredicate(std::shared_ptr<Predicate> &, std::shared_ptr<Predicate> &, BinaryLogicalFunction); //constructs new Binary Predicate with eval_function
    void accept(Visitor &) override;
    std::shared_ptr<Predicate> left();
    std::shared_ptr<Predicate> right();
    BinaryLogicalFunction eval_function();
};
*/
#include "BinaryPredicate.h"
#include "Functions.h"
#include "Visitor.h"
BinaryPredicate::BinaryPredicate(std::shared_ptr<Predicate> &left_, std::shared_ptr<Predicate> &right_, BinaryLogicalFunction func): left(left_), right(right_), eval_function(func){} //constructs new Binary Predicate with eval_function
/*
bool BinaryPredicate::eval(User &user) {
    return eval_function(left->eval(user), right->eval(user));
}
*/
void BinaryPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
std::shared_ptr<Predicate> BinaryPredicate::get_left() {
    return left;
}
std::shared_ptr<Predicate> BinaryPredicate::get_right() {
    return right;
}

BinaryPredicate::BinaryLogicalFunction BinaryPredicate::get_eval_function() {
    return eval_function;
}