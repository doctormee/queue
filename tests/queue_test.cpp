#include "Queue.h"
#include "gtest/gtest.h"
/*
TEST(Rule_Test, Init_Check) {
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
TEST(Rule_Test, invalid_getter_param) {
    Rule r(Field::ALL, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    try {
        r.get_field(3);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
    try {
        r.get_sign(10);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
    try {
        r.get_value(0);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
}

*/