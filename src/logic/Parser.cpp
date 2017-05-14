#include "Parser.h"
#include "Predicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "Term.h"
#include "ImplicationPredicate.h"
#include "Constants.h"
#include "ParseException.h"
void Parser::gt() {
    do {
        t = inp.get();
    } 
    while ( isspace(t));
}
std::string Parser::gs() {
    std::string ret;
    std::getline(inp, ret, ' ');
    return ret;
}
Sign Parser::eqnoteq() {
    if (t == '=') {
        gt();
        return Sign::EQ;
    }
    if (t == '!') {
        gt();
        if (t == '=') {
            gt();
            return Sign::NOTEQ;
        }
    }
    throw ParseException("Некорректный ввод!");
}
char Parser::genvalue() {
    if ((t == 'M') || (t == 'F')) {
        char ret = t;
        gt();
        return ret;
    }
    else {
        throw ParseException("Некорректный ввод!");
    }
}
int Parser::value() {
    std::string val;
    val.clear();
    while ((t >= '0') && (t <= '9')) {
        val += std::to_string(t);
        gt();
    }
    int ret;
    try {
        ret = std::stoi(val);
        return ret;
    }
    catch (...) {
        throw ParseException("Некорректный ввод!");
    }
}
Sign Parser::sign() {
    if (t == '>') {
        gt();
        if (t == '=') {
            gt();
            return Sign::MOREEQ;
        }
        return Sign::MORE;
    }
    else if (t == '<') {
        gt();
        if (t == '=') {
            gt();
            return Sign::LESSEQ;
        }
        return Sign::LESS;
    }
    else {
        return eqnoteq();
    }
}
Field Parser::field() {
    if (t == 'h') {
        if (gs() == "eight") {
            gt();
            return Field::HEIGHT;
        }
    }
    else if (t == 'w') {
        if (gs() == "eight") {
            gt();
            return Field::WEIGHT;
        } 
    }
    else if (t == 'a') {
        if (gs() == "ge") {
            gt();
            return Field::HEIGHT;
        }
    }
    throw ParseException("Некорректный ввод!");
}
std::shared_ptr<Predicate> Parser::term() {
    if (t == 'A') {
        if (gs() != "LL") {
            throw ParseException("Некорректный ввод!");
        }
        std::shared_ptr<Term> ret(new Term());
        gt();
        return ret;
    }
    else {
        if (t == 'g') {
            if (gs() != "ender") {
                throw ParseException("Некорректный ввод!");
            }
            gt();
            Sign s = eqnoteq();
            int val = genvalue();
            std::shared_ptr<Term> ret(new Term(Field::GENDER, s, val));
            return ret;
        }
        else {
            Field f = field();
            Sign s = sign();
            int val = value();
            std::shared_ptr<Term> ret(new Term(f, s, val));
            return ret;
        }
    }
}
std::shared_ptr<Predicate> Parser::par() {
    if (t != '(') {
        return term();
    }
    else {
        gt();
        auto ret = imp();
        if (t != ')') {
            throw ParseException("Некорректный ввод!");
        }
        gt();
        return ret;
    }
}
std::shared_ptr<Predicate> Parser::neg() {
    if (t == '!') { 
        gt();
        std::shared_ptr<NegationPredicate> ret(new NegationPredicate(neg()));
        return ret;
    }
    auto ret = par();
    return ret;
}
std::shared_ptr<Predicate> Parser::conj() {
    auto tmp = neg();
    if (t == '&') {
        std::shared_ptr<ConjunctionPredicate> ret(new ConjunctionPredicate());
        ret->add(tmp);
        while (t == '&') {
            gt();
            ret->add(conj());
        }
        return ret;
    }
    else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::disj() {
    auto tmp = conj();
    if (t == '|') {
        std::shared_ptr<DisjunctionPredicate> ret(new DisjunctionPredicate());
        ret->add(tmp);
        while (t == '|') {
            gt();
            ret->add(disj());
        }
        return ret;
    }
    else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::imp() {
    auto tmp = disj();
    if (t == '-') {
        gt();
        if (t == '>') {
            std::shared_ptr<ImplicationPredicate> ret(new ImplicationPredicate());
            ret->add(tmp);
            while (t == '-') {
                gt();
                if (t == '>') {
                    gt();
                    ret->add(imp());
                }
                else {
                    throw ParseException("Некорректный ввод!"); 
                }
            }
            return ret;
        }
        else {
            throw ParseException("Некорректный ввод!"); 
        }
    }
    else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::parse() {
    gt();
    auto ret = imp();
    if (!inp.eof()) {
        throw ParseException("Некорректный ввод!");
    }
    return ret;    
}
Parser::Parser(std::stringstream &src): inp(src) {}
