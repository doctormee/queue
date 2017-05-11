#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class DisjunctionPredicate: public NaryPredicate {
public:
    void accept(Visitor &) override;
};