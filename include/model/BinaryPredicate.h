#pragma once
#include <memory>
#include "Predicate.h"
class User;

class BinaryPredicate: public Predicate {
    std::shared_ptr<Predicate> left, right;
    bool (*eval_function)(bool, bool);
public:
    BinaryPredicate(std::shared_ptr<Predicate> &, std::shared_ptr<Predicate> &, bool (*)(bool, bool)); //constructs new Binary Predicate with eval_function
    bool eval(User &);
};