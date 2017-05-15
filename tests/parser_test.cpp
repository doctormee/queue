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

TEST(Parser_test, Default_constructor) {
    Parser p{};
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, String_constructor) {
    std::string inp = "11";
    std::string expected = "11";
    Parser p(inp);
    ASSERT_THROW(p.parse(), ParseException);
    ASSERT_EQ(inp, expected);
}

TEST(Parser_test, C_string_constructor) {
    const char *a = "11";
    Parser p{a};
    ASSERT_THROW(p.parse(), ParseException);
    ASSERT_STREQ(a, "11");
}

TEST(Parser_test, Input) {
    Parser p{};
    std::string inp = "";
    p.input(inp);
    ASSERT_THROW(p.parse(), ParseException);
    inp = "ALL ";
    p.input(inp);
    ASSERT_NO_THROW(p.parse());
}

TEST(Parser_test, Empty) {
    Parser p("");
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Empty_parenthesis1) {
    Parser p("()");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis1) {
    Parser p("(ALL))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis2) {
    Parser p("(ALL");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Bad_parenthesis3) {
    Parser p("ALL(");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Empty_parenthesis2) {
    Parser p("ALL()");
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, One_term_no_par) {
    Parser p("age >= 19");
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
    Parser p("(age >= 19)");
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
    Parser p("(((age >= 19)))");
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

TEST(Parser_test,Term_gender) {
    Parser p("(((gender = F)))");
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'F');
        Evaluator eval(&ivan);
        ASSERT_TRUE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}

TEST(Parser_test, Term_bad_field) {
    Parser p("(((ags < 19)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign1) {
    Parser p("(((age == 19)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign2) {
    Parser p("(((age <> 19)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_sign3) {
    Parser p("(((age x 19)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_value) {
    Parser p("(((age < -12020202)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_gender) {
    Parser p("(((gendrr = M)))");
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Term_bad_gender_sign) {
    Parser p("(((gender < 2)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_gender_value) {
    Parser p("(((gender = !F)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_weight) {
    Parser p("(((weighh = 2)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Term_bad_height) {
    Parser p("(((heighh = 2)))");
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Term_bad_ALL) {
    Parser p("(((AlL)))");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Conjunction_bad) {
    Parser p("age >= 19 & ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Conjunction_double) {
    Parser p("age >= 19 && ALL ");
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Conjunction_good) {
    Parser p("(age >= 19) & ALL");
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
    Parser p("age < 20 & ALL & gender = M");
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
    Parser p("age >= 19 | ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Disjunction_double) {
    Parser p("age >= 19 || ALL ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Disjunction_good) {
    Parser p("(weight > 19) | ALL");
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
    Parser p("age <= 12 | height = 100 | gender != M");
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
    Parser p("age >= 19 -> ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Implication_bad2) {
    Parser p("age >= 19 --> ALL ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Implication_good) {
    Parser p("age >= 19 -> ALL");
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
    Parser p("age >= 19 -> ALL -> gender = M");
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
    Parser p("age >= 19 ! ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Negation_bad2) {
    Parser p("!age >= 19 ! ALL! ");
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Negation_good) {
    Parser p("!(age != 19)");
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
    Parser p("!!gender = M");
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

TEST(Parser_test, Priority_check1) {
    Parser p("ALL | ALL & gender != M");
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

TEST(Parser_test, Priority_check2) {
    Parser p("( ALL | ALL ) & gender != M");
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_FALSE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Priority_check3) {
    Parser p("ALL | age != 19  -> gender != M");
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_FALSE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Priority_check4) {
    Parser p("  ALL | (age != 19 -> gender != M)");
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
TEST(Parser_test, Priority_check5) {
    Parser p("! ALL & age >= 19");
    try {
        std::shared_ptr<Predicate> pred(p.parse());
        User ivan(0, "Ivan", "Ivanov", 19, 100, 100, 'M');
        Evaluator eval(&ivan);
        ASSERT_FALSE((pred->accept(eval), eval.get_answer()));
    }
    catch (...) {
        FAIL();
    }
}
TEST(Parser_test, Priority_check6) {
    Parser p("! !(ALL & age = 19)");
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