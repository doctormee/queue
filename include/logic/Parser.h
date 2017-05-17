#pragma once
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
class Predicate;
class ConjunctionPredicate;
class DisjunctionPredicate;
class NegationPredicate;
class Term;
class ImplicationPredicate;
class Parser {
    int token;
    std::stringstream inp;
    void get_token();
    std::string get_string();
    Sign eqnoteq();
    char genvalue();
    int value();
    Sign sign();
    Field field();
    std::shared_ptr<Predicate> term();
    std::shared_ptr<Predicate> par();
    std::shared_ptr<Predicate> neg();
    std::shared_ptr<Predicate> conj();
    std::shared_ptr<Predicate> disj();
    std::shared_ptr<Predicate> imp();
public:
    Parser() = default;
    Parser(const std::string &);
    void input(const std::string &);
    std::shared_ptr<Predicate> parse();
}; 