#include "ConjunctionPredicate.h"
#include "Visitor.h"

ConjunctionPredicate::ConjunctionPredicate(std::shared_ptr<Predicate> left, std::shared_ptr<Predicate> right) {
    add(left);
    add(right);
}

void ConjunctionPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
