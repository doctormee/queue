#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class ConjunctionPredicate: public NaryPredicate {
public:
    ConjunctionPredicate() = default;
    ConjunctionPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>);
    void accept(Visitor &) override;
};