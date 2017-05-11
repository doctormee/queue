#include "ConjunctionPredicate.h"
#include "Visitor.h"

void ConjunctionPredicate::accept(Visitor &visitor) override {
    visitor.visit(*this);
}
