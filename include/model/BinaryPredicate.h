#pragma once
#include <memory>
#include "Predicate.h"
class User;
class Visitor;
class BinaryPredicate: public Predicate {
    typedef bool (*BinaryLogicalFunction)(bool, bool);
    std::shared_ptr<Predicate> left;
    std::shared_ptr<Predicate> right;
    BinaryLogicalFunction eval_function;
public:
    BinaryPredicate(std::shared_ptr<Predicate> &, std::shared_ptr<Predicate> &, BinaryLogicalFunction); //constructs new Binary Predicate with eval_function
    void accept(Visitor &) override;
    std::shared_ptr<Predicate> get_left();
    std::shared_ptr<Predicate> get_right();
    BinaryLogicalFunction get_eval_function();
};