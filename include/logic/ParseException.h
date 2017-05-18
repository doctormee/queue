#pragma once
#include <stdexcept>
class ParseException: public std::runtime_error {
public:
    ~ParseException() {}
    ParseException(const char *msg);
};