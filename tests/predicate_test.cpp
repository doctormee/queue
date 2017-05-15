#include "Predicate.h"
#include "NaryPredicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "gtest/gtest.h"
#include "Constants.h"
#include "User.h"
#include "Term.h"
#include "Evaluator.h"
#include <memory>


TEST(Term_test, Test_constructor) {
    std::unique_ptr<Predicate> pred(new Term{Field::AGE, Sign::EQ, 10});
}
TEST(Term_test, Test_getters) {
    std::unique_ptr<Term> pred(new Term{Field::AGE, Sign::EQ, 10});
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
    vect.push_back(Term(Field(1), Sign::MOREEQ, 10));
    vect.push_back(Term(Field::ALL, Sign(10), -3));
    vect.push_back(Term(Field::AGE, Sign(10), -3));
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    Evaluator eval;
    eval.set_user(&ivan);
    ASSERT_FALSE(((vect.end() - 1)->accept(eval), eval.get_answer()));
    vect.pop_back();
    for (auto &i:vect) {
        ASSERT_TRUE((i.accept(eval), eval.get_answer()));
    }
} 
TEST(Binary_Predicate_Test, Binary_constructor_add_and_eval) {
    std::shared_ptr<Predicate> t1(new Term{Field::HEIGHT, Sign::MORE, 190});
    std::shared_ptr<Predicate> t2(new Term{Field::GENDER, Sign::EQ, 'F'});
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    ConjunctionPredicate bin;
    bin.add(t1);
    bin.add(t2);
    Evaluator eval(&ivan);
    ASSERT_TRUE((bin.accept(eval), eval.get_answer()));
}
TEST(Binary_Predicate_Test, Complex_Binary) {
    std::shared_ptr<Term> t1(new Term{Field::HEIGHT, Sign::MORE, 190});
    std::shared_ptr<Term> t2(new Term{Field::GENDER, Sign::EQ, 'F'});
    std::shared_ptr<Term> t3(new Term{Field::WEIGHT, Sign::NOTEQ, 71});
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<ConjunctionPredicate> bin(new ConjunctionPredicate{});
    bin->add(t1);
    bin->add(t2);
    std::shared_ptr<ConjunctionPredicate> bin2(new ConjunctionPredicate{});
    bin2->add(bin);
    bin2->add(t3);
    Evaluator eval(&ivan);
    ASSERT_TRUE((bin2->accept(eval), eval.get_answer()));
}
TEST(Binary_Predicate_Test, OR_Binary) {
    std::shared_ptr<Term> t1(new Term{Field::HEIGHT, Sign::MORE, 190});
    std::shared_ptr<Term> t2(new Term{Field::GENDER, Sign::EQ, 'F'});
    std::shared_ptr<Term> t3(new Term{Field::WEIGHT, Sign::NOTEQ, 71});
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<ConjunctionPredicate> bin(new ConjunctionPredicate{t1, t2});
    std::shared_ptr<DisjunctionPredicate> bin2(new DisjunctionPredicate{});
    bin2->add(bin);
    bin2->add(t3);
    Evaluator eval(&ivan);
    ASSERT_TRUE((bin2->accept(eval), eval.get_answer()));
} 
TEST(Binary_Predicate_Test, IF_Binary) {
    std::shared_ptr<Term> t1(new Term{Field::HEIGHT, Sign::MORE, 190});
    std::shared_ptr<Term> t2(new Term{Field::GENDER, Sign::EQ, 'M'});
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<ImplicationPredicate> imp1(new ImplicationPredicate{t1, t2});
    std::shared_ptr<ImplicationPredicate> imp2(new ImplicationPredicate{t2, t1});
    std::shared_ptr<ConjunctionPredicate> con(new ConjunctionPredicate{imp1, imp2});
    std::shared_ptr<DisjunctionPredicate> dis(new DisjunctionPredicate{imp1, imp2});
    std::shared_ptr<ImplicationPredicate> imp11(new ImplicationPredicate{t1, t1});
    std::shared_ptr<ImplicationPredicate> imp22(new ImplicationPredicate{t2, t2});
    Evaluator eval(&ivan);
    ASSERT_FALSE((con->accept(eval), eval.get_answer()));
    ASSERT_TRUE((dis->accept(eval), eval.get_answer()));
    ASSERT_TRUE((imp11->accept(eval), eval.get_answer()));
    ASSERT_TRUE((imp22->accept(eval), eval.get_answer()));
} 

TEST(Unary_test, Unary_Construction_and_Eval) {
    std::shared_ptr<Term> pred(new Term{Field::AGE, Sign::EQ, 10});
    NegationPredicate neg(pred);
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    Evaluator eval(&ivan);
    ASSERT_FALSE((neg.accept(eval), eval.get_answer()));
}


TEST(Unary_test, Complex_Unary) {
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    std::shared_ptr<Term> t1(new Term{Field::HEIGHT, Sign::MORE, 190});
    std::shared_ptr<Term> t2(new Term{Field::GENDER, Sign::EQ, 'F'});
    std::shared_ptr<Term> t3(new Term{Field::WEIGHT, Sign::NOTEQ, 70});
    std::shared_ptr<ConjunctionPredicate> bin(new ConjunctionPredicate{});
    bin->add(t1);
    bin->add(t2);
    std::shared_ptr<DisjunctionPredicate> bin2(new DisjunctionPredicate{});
    bin2->add(bin);
    bin2->add(t3);
    NegationPredicate neg(bin2);
    Evaluator eval(&ivan);
    ASSERT_FALSE((neg.accept(eval), eval.get_answer()));
    std::shared_ptr<Term> t4(new Term{Field::WEIGHT, Sign::MOREEQ, 80});
    neg = NegationPredicate{t4};
    ASSERT_TRUE((neg.accept(eval), eval.get_answer()));
}