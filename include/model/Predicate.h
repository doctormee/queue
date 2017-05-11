#pragma once
class User;
class Visitor;
class Predicate {
public:
    virtual void accept(Visitor &) = 0;
};