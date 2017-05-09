#include "DataController.h"
#include "Rule.h"
#include "Constants.h"
#include "User.h"
#include "Queue.h"
#include "Predicate.h"
#include "BinaryPredicate.h"
#include "Term.h"
#include "Functions.h"
#include "Specialist.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>

TEST(DataController_test, Add_room) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
}

TEST(DataController_test, Deleting_room) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    try {
        dc.delete_room(1);
    }
    catch(std::exception &ex) {
        std::string actual = ex.what();
        std::string expected = "No room with such room id!";
        ASSERT_EQ(actual, expected);
    }
    dc.delete_room(0);
}

TEST(DataController_test, Add_and_delete_rule) {
    DataController dc;
    std::shared_ptr<Predicate> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Predicate> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Predicate> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    std::shared_ptr<Predicate> bin(new BinaryPredicate(t1, t2, logical_and));
    std::shared_ptr<Predicate> bin2(new BinaryPredicate(bin, t3, logical_or));
    std::unique_ptr<Rule> rule(new Rule(bin, bin2));
    dc.add_rule(rule);
    ASSERT_EQ(rule, nullptr);
    try {
        dc.delete_rule(2);
    }
    catch(std::exception &ex) {
        std::string actual = ex.what();
        std::string expected = "No such rule!";
        ASSERT_EQ(actual, expected);
    }
    dc.delete_rule(1);
}
TEST(DataController_test, Matching_rules_test) {
    DataController dc;
    std::shared_ptr<Predicate> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Predicate> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Predicate> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    std::shared_ptr<Predicate> bin(new BinaryPredicate(t1, t2, logical_and));
    std::shared_ptr<Predicate> bin2(new BinaryPredicate(bin, t3, logical_or));
    std::unique_ptr<Rule> rule(new Rule(bin, bin2));
    dc.add_rule(rule);
    std::unique_ptr<Rule> rule1(new Rule(t1, t3));
    dc.add_rule(rule1);
    User ivan(2, "Ivan", "Ivanov", 10, 192, 70, 'F');
    User peter(2, "Peter", "Petroff", 10, 191, 69, 'M');
    ASSERT_EQ(dc.matching_rules(ivan, peter), 2);
    User jack(2, "Jack", "Kindred", 10, 192, 78, 'F');
    ASSERT_EQ(dc.matching_rules(peter, jack), 1);
}