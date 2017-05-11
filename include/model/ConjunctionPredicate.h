#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class ConjunctionPredicate: public NaryPredicate {
public:
    void accept(Visitor &) override;
};