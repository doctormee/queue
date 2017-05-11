#include "ImplicationPredicate.h"
#include "Visitor.h"

void ImplicationPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
