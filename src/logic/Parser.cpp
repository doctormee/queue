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
    
    return Sign(0);
}
char Parser::genvalue() {
    
    return 0;
}
int Parser::value() {
    
    return 0;
}
Sign Parser::sign() {
    
    return Sign(0);
}
Field Parser::field() {
    
    return Field(0);
}
std::shared_ptr<Predicate> Parser::term() {
    if (t == 'A') {
        if (gs() != "LL") {
            throw ParseException("Некорректный ввод!");
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
