#include <User.h>
#include <iostream>
#include <vector>
#include <memory>
#include <Specialist.h>
#include <Queue.h>
#include "Rule.h"
#include "Constants.h"

int main() {
    Rule* r = new Rule(Field::AGE, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    for (auto i = 1; i <= 2; ++i) {
        std::cout << r->get_field(i) << " " << r->get_sign(i) << " " << r->get_value(i) << " " << std::endl;
    }
    delete r;
    try {
        std::cout << r->get_field(3) << " " << r->get_sign(3) << " " << r->get_value(3) << " " << std::endl;
    }
    catch (...) {
        return 0;
    }
    return 0;
}