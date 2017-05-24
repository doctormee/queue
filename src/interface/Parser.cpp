#include "Parser.h"
#include "Predicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "Term.h"
#include "ImplicationPredicate.h"
#include "Constants.h"
#include "ParseException.h"

Parser::Parser(const std::string &buf) {
    inp.str(buf);
}
void Parser::get_token() {
    do {
        token = inp.get();
    } 
    while ( isspace(token));
}
std::string Parser::get_string() {
    std::string ret;
    std::getline(inp, ret, ' ');
    return ret;
}
Sign Parser::eqnoteq() {
    if (token == '=') {
        get_token();
        return Sign::EQ;
    }
    if (token == '!') {
        get_token();
        if (token == '=') {
            get_token();
            return Sign::NOTEQ;
        }
    }
    throw ParseException("Некорректный ввод!");
}
char Parser::genvalue() {
    if ((token == 'M') || (token == 'F')) {
        char ret = token;
        get_token();
        return ret;
    } else {
        throw ParseException("Некорректный ввод!");
    }
}
int Parser::value() {
    std::string val;
    val.clear();
    while ((token >= '0') && (token <= '9')) {
        val += token;
        get_token();
    }
    int ret;
    try {
        ret = std::stoi(val);
        return ret;
    } catch (...) {
        throw ParseException("Некорректный ввод!");
    }
}
Sign Parser::sign() {
    if (token == '>') {
        get_token();
        if (token == '=') {
            get_token();
            return Sign::MOREEQ;
        }
        return Sign::MORE;
    } else if (token == '<') {
        get_token();
        if (token == '=') {
            get_token();
            return Sign::LESSEQ;
        }
        return Sign::LESS;
    } else {
        return eqnoteq();
    }
}
Field Parser::field() {
    if (token == 'h') {
        if (get_string() == "eight") {
            get_token();
            return Field::HEIGHT;
        }
    } else if (token == 'w') {
        if (get_string() == "eight") {
            get_token();
            return Field::WEIGHT;
        } 
    } else if (token == 'a') {
        if (get_string() == "ge") {
            get_token();
            return Field::AGE;
        }
    }
    throw ParseException("Некорректный ввод!");
}
std::shared_ptr<Predicate> Parser::term() {
    if (token == 'A') {
        if (get_string() == "LL") {
            std::shared_ptr<Term> ret{new Term{}};
            get_token();
            return ret; 
        } } else {
        if (token == 'g') {
            if (get_string() == "ender") {
                get_token();
                Sign s = eqnoteq();
                int val = genvalue();
                std::shared_ptr<Term> ret{new Term{Field::GENDER, s, val}};
                return ret;
            } } else {
            Field f = field();
            Sign s = sign();
            int val = value();
            std::shared_ptr<Term> ret{new Term{f, s, val}};
            return ret;
        }
    }
    throw ParseException("Некорректный ввод!");
}
std::shared_ptr<Predicate> Parser::par() {
    if (token != '(') {
        return term();
    } else {
        get_token();
        auto ret = imp();
        if (token == ')') {
            get_token();
            return ret;
        } else {
            throw ParseException("Некорректный ввод!");
        }
    }
}
std::shared_ptr<Predicate> Parser::neg() {
    if (token == '!') { 
        get_token();
        std::shared_ptr<NegationPredicate> ret(new NegationPredicate{neg()});
        return ret;
    }
    auto ret = par();
    return ret;
}
std::shared_ptr<Predicate> Parser::conj() {
    auto tmp = neg();
    if (token == '&') {
        std::shared_ptr<ConjunctionPredicate> ret{new ConjunctionPredicate{}};
        ret->add(tmp);
        while (token == '&') {
            get_token();
            ret->add(conj());
        }
        return ret;
    } else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::disj() {
    auto tmp = conj();
    if (token == '|') {
        std::shared_ptr<DisjunctionPredicate> ret{new DisjunctionPredicate{}};
        ret->add(tmp);
        while (token == '|') {
            get_token();
            ret->add(disj());
        }
        return ret;
    } else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::imp() {
    auto tmp = disj();
    if (token == '-') {
        get_token();
        if (token == '>') {
            std::shared_ptr<ImplicationPredicate> ret{new ImplicationPredicate{}};
            ret->add(tmp);
            get_token();
            ret->add(imp());
            return ret;
        } else {
            throw ParseException("Некорректный ввод!"); 
        }
    } else {
        return tmp;
    }
}
std::shared_ptr<Predicate> Parser::parse() {
    get_token();
    auto ret = imp();
    if (!inp.eof()) {
        throw ParseException("Некорректный ввод!");
    }
    return ret;
}
void Parser::input(const std::string &buf) {
    inp.str(buf);
    inp.clear();
}