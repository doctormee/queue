#pragma once
#include "Constants.h"
#include <memory>
class Predicate;
class User;
class Visitor;
class Rule {
    std::shared_ptr<Predicate> first, second;
public:
    Rule(std::shared_ptr<Predicate> &, std::shared_ptr<Predicate> &);
    std::shared_ptr<Predicate> get_first() const;
    std::shared_ptr<Predicate> get_second() const;
};
