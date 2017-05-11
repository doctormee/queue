#pragma once
#include <memory>
#include "Predicate.h"
class Visitor;
class NegationPredicate: public Predicate {
    std::shared_ptr<Predicate> pred;
public:
    NegationPredicate() = default;
    NegationPredicate(std::shared_ptr<Predicate>);
    Predicate &predicate() const;
    void accept(Visitor &) override;
};