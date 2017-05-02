#include "Predicate.h"
#include "BinaryPredicate.h"
#include "gtest/gtest.h"
#include "Functions.h"
#include "Constants.h"
#include "User.h"
#include "Term.h"
#include <memory>

TEST(Term_test, Test_constructor) {
    std::unique_ptr<Predicate> pred(new Term(Field::AGE, Sign::EQ, 10));
}
TEST(Term_test, Test_getters) {
    std::unique_ptr<Term> pred(new Term(Field::AGE, Sign::EQ, 10));
    ASSERT_EQ(pred->get_value(), 10);
    ASSERT_EQ(pred->get_sign(), Sign::EQ);
    ASSERT_EQ(pred->get_field(), Field::AGE);
}
TEST(Term_test, Test_Evaluation) {
    std::vector<Term> vect;
    vect.push_back(Term(Field::HEIGHT, Sign::MORE, 190));
    vect.push_back(Term(Field::WEIGHT, Sign::LESSEQ, 70));
    vect.push_back(Term(Field::AGE, Sign::NOTEQ, 11));
    vect.push_back(Term(Field::GENDER, Sign::EQ, 'F'));
    vect.push_back(Term());
    vect.push_back(Term(Field::HEIGHT, Sign::LESS, 193));
    vect.push_back(Term(Field::AGE, Sign::MOREEQ, 10));
    vect.push_back(Term(Field::ALL, Sign(10), -3));
    vect.push_back(Term(Field::AGE, Sign(10), -3));
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    ASSERT_FALSE((vect.end() - 1)->eval(ivan));
    vect.pop_back();
    for (auto &i:vect) {
        ASSERT_TRUE(i.eval(ivan));
    }
}
TEST(Binary_Predicate_Test)
/*
TEST(Predicate_test, Binary_construction_and) {
    std::unique_ptr<Predicate> pred(new BinaryPredicate()) 
}*/