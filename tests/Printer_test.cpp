#include "Printer.h"
#include "gtest/gtest.h"
#include "Constants.h"
#include "Specialist.h"
#include "Rule.h"
#include "ConjunctionPredicate.h"
#include "Term.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Specialist.h"
#include <vector>
#include <stdexcept>
#include <string>



TEST(Printer_Test, Specialist) {
    Printer p{};
    Specialist spec{"Ivan",  "Ivanov"};
    ASSERT_THROW(spec.accept(p), std::logic_error);
    spec.add_service("Dentist");
    spec.add_service("Therapist");
    std::string expected = "Ivan Ivanov Dentist Therapist\n";
    ASSERT_NO_THROW(spec.accept(p));
    ASSERT_EQ(p.str(), expected);
}
TEST(Printer_Test, Flush_test) {
    Printer p{};
    Specialist spec{"Ivan",  "Ivanov"};
    spec.add_service("Dentist");
    spec.add_service("Therapist");
    std::string expected = "";
    spec.accept(p);
    p.flush();
    ASSERT_EQ(p.str(), expected);
}
TEST(Printer_Test, Term) {
    Printer p{};
    Term term{Field::AGE, Sign::EQ, 10};
    ASSERT_NO_THROW(term.accept(p));
    std::string expected = "age = 10";
    ASSERT_EQ(p.str(), expected);
    p.flush();
    Term term1{Field::ALL, Sign::EQ, 10};
    ASSERT_NO_THROW(term1.accept(p));
    expected = "ALL ";
    ASSERT_EQ(p.str(), expected);
    p.flush();
    Term term2{Field::HEIGHT, Sign::NOTEQ, 120};
    ASSERT_NO_THROW(term2.accept(p));
    expected = "height != 120";
    ASSERT_EQ(p.str(), expected);
}