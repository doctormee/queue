#include "DisjunctionPredicate.h"
#include "Visitor.h"

void DisjunctionPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
