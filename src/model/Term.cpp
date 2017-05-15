/*Term(Field, Sign, int);
bool eval(); */
#include "Predicate.h"
#include "Term.h"
#include "Constants.h"
#include "User.h"
#include "Visitor.h"
Term::Term(Field field_, Sign sign_, int value_)
    : field{field_}, sign{sign_}, value{value_}
{
}
Term::Term()
    : field{Field::ALL}, sign{Sign::EQ}, value{0}
{
}
void Term::accept(Visitor &visitor) {
    visitor.visit(*this);
}

Field Term::get_field() const {
    return field;
}
Sign Term::get_sign() const {
    return sign;
}
int Term::get_value() const {
    return value;
}  