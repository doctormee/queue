#pragma once
class Rule;
class BinaryPredicate;
class Term;
class UnaryPredicate;
class Visitor {
public:
    virtual void visit(Term &) = 0;
    virtual void visit(BinaryPredicate &) = 0;
    virtual void visit(UnaryPredicate &) = 0;
};