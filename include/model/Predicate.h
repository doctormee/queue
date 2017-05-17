#pragma once
class Visitor;
class Predicate {
public:
    virtual void accept(Visitor &) = 0;
};