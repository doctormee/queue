#pragma once
#include "Constants.h"
#include <memory>
class Predicate;
class User;
class Rule {
    std::shared_ptr<Predicate> first, second;
public:
    Rule(std::shared_ptr<Predicate> &&, std::shared_ptr<Predicate> &&);
    bool evaluate_first(User &);
    bool evaluate_second(User &);
};
