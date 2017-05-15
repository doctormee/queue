/*Term(Field, Sign, int);
bool eval(); */
#include "Predicate.h"
#include "Term.h"
#include "Constants.h"
#include "User.h"
#include "Visitor.h"
Term::Term(Field field_, Sign sign_, int value_): field{field_}, sign{sign_}, value{value_} {}
Term::Term(): field{Field::ALL}, sign{Sign::EQ}, value{0} {}
/*
bool Term::eval(User &user) {
    int u_value;
    switch (field) {
        case Field::ALL: {
            return true;
        }
        case Field::AGE: {
            u_value = user.age();
            break;
        }
        case Field::HEIGHT: {
            u_value = user.height();
            break;
        }
        case Field::WEIGHT: {
            u_value = user.weight();
            break;
        }
        case Field::GENDER: {
            u_value = user.gender();
            break;
        }
        default: {
            return false;
        }
    }
    switch (sign) {
        case Sign::LESS: {
            return (u_value < value);
        }
        case Sign::LESSEQ: {
            return (u_value <= value);
        }
        case Sign::EQ: {
            return (u_value == value);
        }
        case Sign::MOREEQ: {
            return (u_value >= value);
        }
        case Sign::MORE: {
            return (u_value > value);
        }
        case Sign::NOTEQ: {
            return (u_value != value);
        }
        default: {
            return false;
        }
    }
}
*/
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