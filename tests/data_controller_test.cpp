#include "DataController.h"
#include "Predicate.h"
#include "NaryPredicate.h"
#include "ConjunctionPredicate.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Term.h"
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
        std::string expected = "Нет комнаты с таким номером!";
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
        std::string expected = "Нет такого правила";
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
    ASSERT_THROW(dc.add_user(10, 2, "Ivan", "Ivanov", 10, 192, 70, 'F'), std::out_of_range);
    
} 
TEST(DataController_test, Add_user_ptr) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    std::unique_ptr<User> jack(new User(2, "Jack", "Kindred", 10, 192, 78, 'F'));
    dc.add_user(0, jack);
    auto &q = dc.get_queue(0);
    ASSERT_EQ(q.size(), 1);
    try {
        dc.add_user(1, jack);
        FAIL();
    }
    catch (...) {
        //ok
    }
} 
TEST(DataController_test, Delete_user) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    std::unique_ptr<User> jack(new User(2, "Jack", "Kindred", 10, 192, 78, 'F'));
    dc.add_user(0, jack);
    ASSERT_THROW(dc.delete_user(1, 2), std::out_of_range);
    dc.delete_user(0, 2);
    auto &q = dc.get_queue(0);
    ASSERT_EQ(q.size(), 0);
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
    ASSERT_THROW(dc.update_room(1), std::out_of_range);
} 
TEST(DataController_test, Room_size) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("Dental");
    dc.add_room(0, "Peter", "Jackson", serv);
    std::unique_ptr<User> ivan(new User(1, "Ivan", "Ivanov", 10, 192, 70, 'F'));
    std::unique_ptr<User> peter(new User(2, "Peter", "Petroff", 10, 191, 69, 'M'));
    dc.add_user(0, ivan);
    dc.add_user(0, peter);
    ASSERT_EQ(dc.room_size(0), 2);
    ASSERT_THROW(dc.room_size(1), std::out_of_range);
} 
TEST(DataController_test, Update_All) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("Dental");
    dc.add_room(0, "Peter", "Jackson", serv);
    dc.add_room(1, "John", "Snow", serv);
    std::shared_ptr<Term> t1(new Term(Field::HEIGHT, Sign::MORE, 190));
    std::shared_ptr<Term> t2(new Term(Field::GENDER, Sign::EQ, 'F'));
    std::unique_ptr<Rule> rule(new Rule(t1, t2));
    dc.add_rule(rule);
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
    try {
        dc.get_queue(1);
        FAIL();
    }
    catch (...)
    {
        //ok
    }
} 
TEST(DataController_test, Get_specialist_test) {
    DataController dc;
    std::vector<std::string> serv;
    serv.push_back("One");
    serv.push_back("Two");
    dc.add_room(0, "Ivan", "Ivanov", serv);
    auto &s = dc.get_specialist(0);
    ASSERT_EQ(s.size(), 2);
    ASSERT_STREQ(s.get_service(0).c_str(), "One");
    ASSERT_STREQ(s.get_service(1).c_str(), "Two");
    ASSERT_THROW(dc.get_specialist(1), std::out_of_range);
    
} 