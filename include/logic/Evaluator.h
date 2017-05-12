#pragma once
#include "Visitor.h"
#include <memory>
class User;
class BinaryPredicate;
class UnaryPredicate;
class Term;
class Rule;
class Specialist;
class Evaluator: public Visitor {
    bool answer;
    User *user;
public:
    Evaluator();
    Evaluator(User *);
    void visit(const Term &) override;
    void visit(const ConjunctionPredicate &) override;
    void visit(const DisjunctionPredicate &) override;
    void visit(const NegationPredicate &) override;
    void visit(const ImplicationPredicate &) override;
    void visit(const Specialist &) override;
    bool get_answer() const;
    void set_user(User *);
};