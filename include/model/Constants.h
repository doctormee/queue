#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace Field {
    enum Field: int {
    ALL, AGE, HEIGHT, WEIGHT, GENDER
    };
}
namespace Sign {
    enum Sign: int {
        LESS, LESSEQ, EQ, MOREEQ, MORE, NOTEQ
    };
}
#endif