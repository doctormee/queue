#include "Rule.h"

/*class Rule {
    Field field1, field2;
    Sign sign1, sign2;
    int value1, value2;
public:
    Rule(Field, Sign, int, Field, Sign, int);
    bool operator() (User &user1, User& user2);
    Field get_field(int);
    Sign get_sign(int);
    int get_value(int);
}; */

Rule::Rule(Field field1_, Sign sign1_, int value1_, Field field2_, Sign sign2_, int value2_): field1(field1_), field2(field2_), sign1(sign1_), sign2(sign2_), value1(value1_), value2(value2_) {};