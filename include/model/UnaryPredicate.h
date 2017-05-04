#pragma once
#include <memory>
#include "Predicate.h"
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
};