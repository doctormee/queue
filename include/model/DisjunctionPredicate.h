#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class DisjunctionPredicate: public NaryPredicate {
public:
    DisjunctionPredicate() = default;
    DisjunctionPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>);
    void accept(Visitor &) override;
};