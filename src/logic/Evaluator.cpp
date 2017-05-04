#include "Evaluator.h"
/*#pragma once
#include "Visitor.h"
#include <memory>
class User;
class BinaryPredicate;
class Term;
class Evaluator: public Visitor {
    bool answer;
    User* user;
public:
    void visit(Term &);
    void visit(BinaryPredicate &);
    bool answer() const;
    void set_user();
}*/
#include "User.h"
#include "Predicate.h"
#include "BinaryPredicate.h"
#include "UnaryPredicate.h"
#include "Term.h"
#include "Constants.h"
#include <memory>

Evaluator::Evaluator(): answer(false), user(nullptr) {}
Evaluator::Evaluator(User *user_): answer(false), user(user_) {}


void Evaluator::set_user(User *inp) {
    user = inp;
}

bool Evaluator::get_answer() const {
    return answer;
}

void Evaluator::visit(Term &term) {
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
void Evaluator::visit(BinaryPredicate &binary) {
    std::shared_ptr<Predicate> left = binary.get_left();
    std::shared_ptr<Predicate> right = binary.get_right();
    bool (*eval)(bool, bool) = binary.get_eval_function();
    Evaluator temp(user);
    bool first_answer;
    left->accept(temp);
    first_answer = temp.get_answer();
    right->accept(temp);
    answer = eval( first_answer, temp.get_answer());
}
void Evaluator::visit(UnaryPredicate &unary) {
    std::shared_ptr<Predicate> predicate = unary.get_predicate();
    bool (*eval)(bool) = unary.get_eval_function();
    Evaluator temp(user);
    answer = eval( (predicate->accept(temp), temp.get_answer()) );
}

