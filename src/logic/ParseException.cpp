#include "ParseException.h"
ParseException::ParseException(const char *msg)
    : std::runtime_error(msg)
{
    
}
