#include "ImplicationPredicate.h"
#include "Visitor.h"

ImplicationPredicate::ImplicationPredicate(
    std::shared_ptr<Predicate> left, 
    std::shared_ptr<Predicate> right)
{
    add(left);
    add(right);
}
void ImplicationPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}
