#pragma once
class Rule;
class ConjunctionPredicate;
class Term;
class DisjunctionPredicate;
class NegationPredicate;
class ImplicationPredicate;
class Specialist;
class Visitor {
public:
    virtual void visit(const Term &) = 0;
    virtual void visit(const ConjunctionPredicate &) = 0;
    virtual void visit(const DisjunctionPredicate &) = 0;
    virtual void visit(const NegationPredicate &) = 0;
    virtual void visit(const ImplicationPredicate &) = 0;
    virtual void visit(const Specialist &) = 0;
};