#include <User.h>
#include <iostream>
#include <vector>
#include <memory>
#include <Specialist.h>
#include <Queue.h>
#include "Rule.h"
#include "Constants.h"

int main() {
    Rule* r = new Rule(FIELD::AGE, SIGN::LESS, 10, FIELD::AGE, SIGN::MORE, 30);
    std::cout << r->get_field(1);
    delete r;
    return 0;
}