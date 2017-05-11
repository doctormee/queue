#pragma once
#include <memory>
#include "BinaryPredicate.h"
class Visitor;
class ConjunctionPredicate: public BinaryPredicate {
public:
    void accept(Visitor &) override;
};