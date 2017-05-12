#include "DataController.h"
#include "Rule.h"
#include "Constants.h"
#include "User.h"
#include "Queue.h"
#include "Predicate.h"
#include "NaryPredicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Term.h"
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
    std::shared_ptr<Term> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Term> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Term> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    std::shared_ptr<ConjunctionPredicate> bin(new ConjunctionPredicate());
    bin->add(t1);
    bin->add(t2);
    std::shared_ptr<DisjunctionPredicate> bin2(new DisjunctionPredicate());
    bin2->add(bin);
    bin2->add(t3);
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
    std::shared_ptr<Term> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Term> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::shared_ptr<Term> t3(new Term(Field::WEIGHT, Sign::NOTEQ, 70));
    std::shared_ptr<ConjunctionPredicate> bin(new ConjunctionPredicate(t1, t2));
    std::shared_ptr<DisjunctionPredicate> bin2(new DisjunctionPredicate());
    bin2->add(bin);
    bin2->add(t3);
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
TEST(DataController_test, Add_user_simple) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    dc.add_user(0, 2, "Ivan", "Ivanov", 10, 192, 70, 'F');
} 
TEST(DataController_test, Add_user_ptr) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    std::unique_ptr<User> jack(new User(2, "Jack", "Kindred", 10, 192, 78, 'F'));
    dc.add_user(0, jack);
} 

TEST(DataController_test, Update_room) {
    DataController dc;
    std::shared_ptr<Term> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Term> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::unique_ptr<Rule> rule(new Rule(t1, t2));
    dc.add_rule(rule);
    std::vector<std::string> serv;
    serv.push_back("Dental");
    dc.add_room(0, "Peter", "Jackson", serv);
    std::unique_ptr<User> ivan(new User(1, "Ivan", "Ivanov", 10, 192, 70, 'F'));
    std::unique_ptr<User> peter(new User(2, "Peter", "Petroff", 10, 191, 69, 'M'));
    dc.add_user(0, ivan);
    dc.add_user(0, peter);
    dc.update_room(0);
    auto &q = dc.get_queue(0);
    ASSERT_EQ((*(q.begin()))->user->get_uid(), 2);
} 

TEST(DataController_test, Get_queue_test) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    auto &q = dc.get_queue(0);
    ASSERT_EQ(q.size(), 0);
    std::unique_ptr<User> jack(new User(2, "Jack", "Kindred", 10, 192, 78, 'F'));
    dc.add_user(0, jack);
    ASSERT_EQ(q.size(), 1);
} 