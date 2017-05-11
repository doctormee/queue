#include "DisjunctionPredicate.h"
#include "Visitor.h"

void DisjunctionPredicate::accept(Visitor &visitor) override {
    visitor.visit(*this);
}
