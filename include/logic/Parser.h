#pragma once
/* enum Field: int {
    ALL, AGE, HEIGHT, WEIGHT, GENDER
};
enum Sign: int {
    LESS, LESSEQ, EQ, MOREEQ, MORE, NOTEQ
};
     IMP = DISJ {'->' IMP}
 
     DISJ = CONJ {'|' DISJ} 
 
     CONJ = NEG {'&' CONJ}
 
     NEG = {'!'}PAR
 
     PAR = '('DISJ')' | TERM
 
     TERM = FIELD SIGN VALUE | 'gender' EQNOTEQ GENVALUE| ALL
 
     FIELD = 'height' | 'weight' | 'age'
 
     SIGN = '>' | '>=' | '<' | '<=' | EQNOTEQ
 
     VALUE = {'0'}{1..9} 
 
     GENVALUE = 'M' | 'F'
 
     EQNOTEQ = '=' | '!=' 
         */
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
    int t;
    std::stringstream &inp;
    void gt();
    std::string gs();
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
    Parser(std::stringstream &);
    std::shared_ptr<Predicate> parse();
}; 