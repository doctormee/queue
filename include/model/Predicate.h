#pragma once
class User;
class Predicate {
public:
    virtual bool eval(User &) = 0;
};