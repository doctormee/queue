#pragma once
#include "Constants.h"
class Predicate;
class User;

class Term: public Predicate {
    Field field;
    Sign sign;
    int value;
public:
    Term();
    Term(Field, Sign, int);
    Field get_field() const;
    Sign get_sign() const;
    int get_value() const;
    void accept(Visitor &) override;
};