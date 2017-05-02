#include "Rule.h"
#include "Constants.h"
#include "gtest/gtest.h"
#include "Predicate.h"
#include "BinaryPredicate.h"
#include "Term.h"
#include "User.h"
#include "Functions.h"
/*
#pragma once
#include "Constants.h"
#include <memory>
class Predicate;
class User;
class Rule {
    std::shared_ptr<Predicate> first, second;
public:
    Rule(std::shared_ptr<Predicate> &, std::shared_ptr<Predicate> &);
    bool evaluate_first(User &);
    bool evaluate_second(User &);
};

*/
TEST(Rule_test, Rule_Init) {
    std::shared_ptr<Predicate> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Predicate> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Predicate> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    std::shared_ptr<Predicate> bin(new BinaryPredicate(t1, t2, logical_and));
    std::shared_ptr<Predicate> bin2(new BinaryPredicate(bin, t3, logical_or));
    Rule rule(bin, bin2);
}

TEST(Rule_test, Rule_Evaluate) {
    std::shared_ptr<Predicate> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Predicate> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Predicate> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<Predicate> bin(new BinaryPredicate(t1, t2, logical_and));
    std::shared_ptr<Predicate> bin2(new BinaryPredicate(bin, t3, logical_or));
    Rule rule(bin, bin2);
    ASSERT_TRUE(rule.evaluate_first(ivan));
    ASSERT_TRUE(rule.evaluate_second(ivan));
}
