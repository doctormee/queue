#pragma once
class User;
class Visitor;
class Visitable {
public:
    virtual void accept(Visitor &) = 0;
};