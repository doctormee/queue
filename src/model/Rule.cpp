#include "Rule.h"
#include <stdexcept>

/*class Rule {
    Field field1, field2;
    Sign sign1, sign2;
    int value1, value2;
public:
    Rule(Field, Sign, int, Field, Sign, int);
    Field get_field(int);
    Sign get_sign(int);
    int get_value(int);
}; */
Rule::Rule(Field field1_, Sign sign1_, int value1_, Field field2_, Sign sign2_, int value2_): field1(field1_), field2(field2_), sign1(sign1_), sign2(sign2_), value1(value1_), value2(value2_) {};
Field Rule::get_field(int i) const{
    switch (i) {
        case 1: {
            return field1;
        }
        case 2: {
            return field2;
        }
        default: {
            std::out_of_range ex("Out of range! Rule has only two expressions that can be evaluated!");
            throw ex;
        }
    }
}
Sign Rule::get_sign(int i) const{
    switch (i) {
        case 1: {
            return sign1;
        }
        case 2: {
            return sign2;
        }
        default: {
            std::out_of_range ex("Out of range! Rule has only two expressions that can be evaluated!");
            throw ex;
        }
    }
}
int Rule::get_value(int i) const {
    switch (i) {
        case 1: {
            return value1;
        }
        case 2: {
            return value2;
        }
        default: {
            std::out_of_range ex("Out of range! Rule has only two expressions that can be evaluated!");
            throw ex;
        }
    }
}
