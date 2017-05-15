#include "DisjunctionPredicate.h"
#include "Visitor.h"

DisjunctionPredicate::DisjunctionPredicate(
    std::shared_ptr<Predicate> left, 
    std::shared_ptr<Predicate> right)
{
    add(left);
    add(right);
}
void DisjunctionPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
