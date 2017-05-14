#include "Parser.h"
#include "gtest/gtest.h"
#include "Evaluator.h"
#include "ParseException.h"
#include "User.h"
#include "Predicate.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

TEST(Parser_test, Empty) {
    std::stringstream inp;
    Parser p(inp);
    inp << "";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Empty_parenthesis1) {
    std::stringstream inp;
    Parser p(inp);
    inp << "()";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis1) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(all))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis2) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(all";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis3) {
    std::stringstream inp;
    Parser p(inp);
    inp << "all(";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Empty_parenthesis2) {
    std::stringstream inp;
    Parser p(inp);
    inp << "all()";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, One_term_no_par) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}

TEST(Parser_test, One_term_par) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(age >= 19)";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}

TEST(Parser_test, One_term_many_par) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age >= 19)))";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Term_bad_field) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((ags < 19)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign1) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age == 19)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign2) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age <> 19)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign3) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age x 19)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_value) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age < -12020202)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_gender) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((gendrr = M)))";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Term_bad_gender_sign) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((gender < 2)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_gender_value) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((gender = !F)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_weight) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((weighh = 2)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_height) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((heighh = 2)))";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Term_bad_ALL) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((AlL)))";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Conjunction_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 & ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Conjunction_double) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 && ALL ";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Conjunction_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(age >= 19) & ALL";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Conjunction_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age < 20 & ALL & gender = M";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Disjunction_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 | ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Disjunction_double) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 || ALL ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Disjunction_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(weight > 19) | ALL";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Disjunction_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age <= 12 | height = 100 | gender != M";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Implication_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 -> ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Implication_bad2) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 --> ALL ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Implication_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 -> ALL";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Implication_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 -> ALL -> gender = M";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Negation_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 ! ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Negation_bad2) {
    std::stringstream inp;
    Parser p(inp);
    inp << "!age >= 19 ! ALL! ";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Negation_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "!(age != 19)";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Negation_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "!!gender = M";
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}