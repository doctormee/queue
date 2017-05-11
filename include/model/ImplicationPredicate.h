#pragma once
#include <memory>
#include "NaryPredicate.h"
class Visitor;
class ImplicationPredicate: public NaryPredicate {
public:
    void accept(Visitor &) override;
};