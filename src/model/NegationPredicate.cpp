#include "NegationPredicate.h"
#include "Visitor.h"
#include <stdexcept>

void NegationPredicate::accept(Visitor &visitor) {
    visitor.visit(*this);
}


Predicate &NegationPredicate::predicate() const {
    return *pred;
}
NegationPredicate::NegationPredicate(std::shared_ptr<Predicate> src)
    : pred{src}
{ 
    if (!pred) {
        throw std::logic_error("Empty predicate (i.e. nullptr) is added");
    }
}