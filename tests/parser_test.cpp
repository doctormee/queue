#include "Parser.h"
#include "gtest/gtest.h"
#include "Evaluator.h"
#include "ParseException.h"
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
    ASSERT_NO_THROW(p.parse());
}
TEST(Parser_test, One_term_par) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(age >= 19)";
    ASSERT_NO_THROW(p.parse());
}

TEST(Parser_test, One_term_many_par) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(((age >= 19)))";
    ASSERT_NO_THROW(p.parse());
}
TEST(Parser_test, Conjunction_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 & ";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Conjunction_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(age >= 19) & ALL";
    ASSERT_NO_THROW(p.parse());
}
TEST(Parser_test, Conjunction_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 & ALL & gender < 'M'";
    ASSERT_THROW(p.parse(), ParseException);
}
TEST(Parser_test, Disjunction_bad) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 | ";
    ASSERT_THROW(p.parse(), ParseException);
}

TEST(Parser_test, Disjunction_good) {
    std::stringstream inp;
    Parser p(inp);
    inp << "(age >= 19) | ALL";
    ASSERT_NO_THROW(p.parse());
}
TEST(Parser_test, Disjunction_long) {
    std::stringstream inp;
    Parser p(inp);
    inp << "age >= 19 | ALL | gender < 'M'";
    ASSERT_THROW(p.parse(), ParseException);
}