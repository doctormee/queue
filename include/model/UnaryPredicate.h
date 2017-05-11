#pragma once
#include <memory>
#include "Predicate.h"
class Visitor;
class UnaryPredicate: public Predicate {
    std::shared_ptr<Predicate> predicate;
public:
    UnaryPredicate(std::shared_ptr<Predicate> &); //constructs new Unary Predicate
    std::shared_ptr<Predicate> get_predicate();
};