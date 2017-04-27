#include "Rule.h"
#include "Constants.h"
#include "gtest/gtest.h"

TEST(Rule_Tests, Init_Check) {
    Rule* r = new Rule(Field::AGE, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    delete r;
    
}
TEST(Rule_Test, getters_check) {
    Rule* r = new Rule(Field::AGE, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    for (auto i = 1; i <= 2; ++i) {
        ASSERT_EQ(r->get_field(i), Field::AGE);
        ASSERT_NE(r->get_sign(i), Sign::NOTEQ);
        ASSERT_GE(r->get_value(i), 10);
    }
}