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

/*
TEST(Predicate_test, Binary_construction_and) {
    std::unique_ptr<Predicate> pred(new BinaryPredicate()) 
}*/