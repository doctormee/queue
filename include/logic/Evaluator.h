#pragma once
#include "Visitor.h"
#include <memory>
class User;
class BinaryPredicate;
class Term;
class Rule;
class Evaluator: public Visitor {
    bool answer;
    User *user;
public:
    Evaluator();
    Evaluator(User *);
    void visit(Term &) override;
    void visit(BinaryPredicate &) override;
    bool get_answer() const;
    void set_user(User *);
};