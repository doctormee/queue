#pragma once
#include <stdexcept>
class ParseException: public std::runtime_error {
public:
    ParseException(const char *msg);
};