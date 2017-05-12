#include "Evaluator.h"
/*#pragma once
#include "Visitor.h"
#include <memory>
class User;
class NaryPredicate;
class Term;
class Evaluator: public Visitor {
    bool answer;
    User* user;
public:
    void visit(Term &);
    void visit(NaryPredicate &);
    bool answer() const;
    void set_user();
}*/
#include "User.h"
#include "Predicate.h"
#include "NaryPredicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Term.h"
#include "Constants.h"
#include <memory>
#include <vector>
#include <stdexcept>
class Specialist;

Evaluator::Evaluator(): answer(false), user(nullptr) {}
Evaluator::Evaluator(User *user_): answer(false), user(user_) {}


void Evaluator::set_user(User *inp) {
    user = inp;
}

bool Evaluator::get_answer() const {
    return answer;
}

void Evaluator::visit(const Term &term) {
    int u_value;
    Field field = term.get_field();
    Sign sign = term.get_sign();
    int value = term.get_value();
    if (field == Field::ALL) {
        answer = true;
    }
    else {
        switch (field) {
            case Field::AGE: {
                u_value = user->get_age();
                break;
            }
            case Field::HEIGHT: {
                u_value = user->get_height();
                break;
            }
            case Field::WEIGHT: {
                u_value = user->get_weight();
                break;
            }
            case Field::GENDER: {
                u_value = user->get_gender();
                break;
            }
            default: {
                answer = false;
            }
        }
        switch (sign) {
            case Sign::LESS: {
                answer = (u_value < value);
                break;
            }
            case Sign::LESSEQ: {
                answer = (u_value <= value);
                break;
            }
            case Sign::EQ: {
                answer = (u_value == value);
                break;
            }
            case Sign::MOREEQ: {
                answer = (u_value >= value);
                break;
            }
            case Sign::MORE: {
                answer = (u_value > value);
                break;
            }
            case Sign::NOTEQ: {
                answer = (u_value != value);
                break;
            }
            default: {
                answer = false;
            }
        }
    }
}

void Evaluator::visit(const ConjunctionPredicate &pred) {
    (*(pred.begin()))->accept(*this);
    bool tmp = answer;
    for (auto i = ++pred.begin(); i != pred.end(); ++i) {
        tmp = tmp && ((*i)->accept(*this), answer);
    }
    answer = tmp;
}
void Evaluator::visit(const DisjunctionPredicate &pred) {
    (*(pred.begin()))->accept(*this);
    bool tmp = answer;
    for (auto i = ++pred.begin(); i != pred.end(); ++i) {
        tmp = tmp || ((*i)->accept(*this), answer);
    }
    answer = tmp;
}
void Evaluator::visit(const NegationPredicate &pred) {
    pred.predicate().accept(*this);
    answer = !answer;
}
void Evaluator::visit(const ImplicationPredicate &pred) {
    (*(pred.begin()))->accept(*this);
    bool tmp = answer;
    for (auto i = ++pred.begin(); i != pred.end(); ++i) {
        tmp = !tmp || ((*i)->accept(*this), answer);
    }
    answer = tmp;
}

void Evaluator::visit(const Specialist &) {
    throw std::logic_error("You can not evaluate a Specialist!");
}

