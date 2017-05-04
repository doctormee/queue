#pragma once
class Rule;
class BinaryPredicate;
class Term;
class Visitor {
public:
    virtual void visit(Term &) = 0;
    virtual void visit(BinaryPredicate &) = 0;
};