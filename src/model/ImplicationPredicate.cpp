#include "ImplicationPredicate.h"
#include "Visitor.h"

void ImplicationPredicate::accept(Visitor &visitor) override {
    visitor.visit(*this);
}
