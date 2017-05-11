#include "ConjunctionPredicate.h"
#include "Visitor.h"

void ConjunctionPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
