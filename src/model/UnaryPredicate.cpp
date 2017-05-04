/*#pragma once
#include <memory>
#include "Predicate.h"
class User;
class Visitor;
class UnaryPredicate: public Predicate {
    typedef bool (*UnaryLogicalFunction)(bool);
    std::shared_ptr<Predicate> predicate;
    UnaryLogicalFunction eval_function;
public:
    UnaryPredicate(std::shared_ptr<Predicate> &, UnaryLogicalFunction); //constructs new Unary Predicate with eval_function
    void accept(Visitor &) override;
    std::shared_ptr<Predicate> get_predicate();
    UnaryLogicalFunction get_eval_function();
}; */
#include "UnaryPredicate.h"
#include "Visitor.h"
UnaryPredicate::UnaryPredicate(std::shared_ptr<Predicate> &predicate_, UnaryPredicate::UnaryLogicalFunction input_function): predicate(predicate_), eval_function(input_function) {}

void UnaryPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
std::shared_ptr<Predicate> UnaryPredicate::get_predicate() {
    return predicate;
}

UnaryPredicate::UnaryLogicalFunction UnaryPredicate::get_eval_function() {
    return eval_function;
}

