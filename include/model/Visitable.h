#pragma once
class Visitor;
class Visitable {
public:
    virtual void accept(Visitor &) = 0;
};