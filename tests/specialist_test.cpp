#include "User.h"
#include "gtest/gtest.h"
#include "Specialist.h"
#include "Evaluator.h"
#include <vector>
#include <stdexcept>
#include <string>

TEST(Specialist_Test, Spec_init) {
    Specialist spec1;
    Specialist spec2("Ivan", "Ivanov");
    std::unique_ptr<Specialist> spec3{new Specialist{}};
}
TEST(Specialist_Test, Default_getters) {
    Specialist spec1;
    ASSERT_EQ(spec1.get_name(), "John");
    ASSERT_NE(spec1.get_surname(), "John");
}
TEST(Specialist_Test, Constructed_getters) {
    Specialist spec1("Ivan", "John");
    ASSERT_EQ(spec1.get_name(), "Ivan");
    ASSERT_EQ(spec1.get_surname(), "John");
}
TEST(Specialist_Test, Services) {
    Specialist spec1;
    spec1.add_service("Dentist");
    ASSERT_EQ(spec1.get_service(0), "Dentist" );
    ASSERT_THROW(spec1.get_service(1), std::out_of_range);
    spec1.add_service("Vet");
    for (auto i = 0; i < spec1.size(); ++i) {
        std::string tmp;
        ASSERT_NO_THROW(tmp = spec1.get_service(i));
        ASSERT_NE(tmp, "");
    }
}

TEST(Specialist_Test, Trying_to_evaluate) {
    Specialist spec1;
    Evaluator eval;
    ASSERT_THROW(spec1.accept(eval), std::logic_error);
}