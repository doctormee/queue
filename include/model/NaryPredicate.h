#pragma once
#include <memory>
#include <vector>
#include "Predicate.h"
class Visitor;
class NaryPredicate: public Predicate {
    std::vector<std::shared_ptr<Predicate>> operands;
public:
    void add(std::shared_ptr<Predicate>);
    decltype(operands.cbegin()) begin() const;
    decltype(operands.cend()) end() const;
};