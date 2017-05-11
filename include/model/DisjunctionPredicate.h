#pragma once
#include <memory>
#include "BinaryPredicate.h"
class Visitor;
class DisjunctionPredicate: public BinaryPredicate {
public:
    void accept(Visitor &) override;
};