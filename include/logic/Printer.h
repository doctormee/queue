#pragma once
#include "Visitor.h"
#include <iostream>
class Rule;
class ConjunctionPredicate;
class Term;
class DisjunctionPredicate;
class NegationPredicate;
class ImplicationPredicate;
class Specialist;
class Printer: public Visitor {
    std::ostream &out;
public:
    Printer(std::ostream &);
    void visit(const Term &) override;
    void visit(const ConjunctionPredicate &) override;
    void visit(const DisjunctionPredicate &) override;
    void visit(const NegationPredicate &) override;
    void visit(const ImplicationPredicate &) override;
    void visit(const Specialist &) override;
};