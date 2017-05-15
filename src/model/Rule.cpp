#include "Rule.h"
#include <stdexcept>
#include "Predicate.h"
#include "Visitor.h"
Rule::Rule(std::shared_ptr<Predicate> first_, std::shared_ptr<Predicate> second_)
    : first{first_}, second{second_}
{
} 

std::shared_ptr<Predicate> Rule::get_first() const {
    return first;
}
std::shared_ptr<Predicate> Rule::get_second() const {
    return second;
}


