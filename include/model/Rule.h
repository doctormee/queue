#ifndef RULE_H
#define RULE_H 
#include "Constants.h"

class Rule {
    Field field1, field2;
    Sign sign1, sign2;
    int value1, value2;
public:
    Rule(Field, Sign, int, Field, Sign, int);
    Field get_field(int);
    Sign get_sign(int);
    int get_value(int);
};
#endif
