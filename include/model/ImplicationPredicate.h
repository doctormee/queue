#pragma once
#include <memory>
#include "BinaryPredicate.h"
class Visitor;
class ImplicationPredicate: public BinaryPredicate {
public:
    void accept(Visitor &) override;
};