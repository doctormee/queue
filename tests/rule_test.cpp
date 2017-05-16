#include "Rule.h"
#include "Constants.h"
#include "gtest/gtest.h"
#include "Predicate.h"
#include "NaryPredicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Term.h"
#include "User.h"
#include "Evaluator.h"
TEST(Rule_test, Rule_Init) {
    std::shared_ptr<Term> t1{new Term{Field::HEIGHT, Sign::MORE, 190}};
    std::shared_ptr<Term> t2{new Term{Field::GENDER, Sign::EQ, 'F'}};
    std::shared_ptr<Term> t3{new Term{Field::WEIGHT, Sign::NOTEQ, 70}};
    std::shared_ptr<ConjunctionPredicate> bin{new ConjunctionPredicate{}};
    bin->add(t1);
    bin->add(t2);
    std::shared_ptr<DisjunctionPredicate> bin2{new DisjunctionPredicate{}};
    bin2->add(bin);
    bin2->add(t3);
    Rule rule(bin, bin2);
}

TEST(Rule_test, Rule_Evaluate) {
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<Term> t1{new Term{Field::HEIGHT, Sign::MORE, 190}};
    std::shared_ptr<Term> t2{new Term{Field::GENDER, Sign::EQ, 'F'}};
    std::shared_ptr<Term> t3{new Term{Field::WEIGHT, Sign::NOTEQ, 70}};
    std::shared_ptr<ConjunctionPredicate> bin{new ConjunctionPredicate{}};
    bin->add(t1);
    bin->add(t2);
    std::shared_ptr<DisjunctionPredicate> bin2{new DisjunctionPredicate{}};
    bin2->add(bin);
    bin2->add(t3);
    Rule rule(bin, bin2);
    Evaluator eval;
    eval.set_user(&ivan);
    t1->accept(eval);
    ASSERT_TRUE(eval.get_answer());
    ASSERT_TRUE((rule.get_first()->accept(eval), eval.get_answer()));
    rule.get_second()->accept(eval);
    ASSERT_TRUE(eval.get_answer());
    User john(0);
    ASSERT_LE(john.get_height(), 190);
    eval.set_user(&john);
    t1->accept(eval);
    ASSERT_FALSE(eval.get_answer());
}
