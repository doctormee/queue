#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class ImplicationPredicate: public NaryPredicate {
public:
    ImplicationPredicate() = default;
    ImplicationPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>);
    void accept(Visitor &) override;
};