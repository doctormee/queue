#ifndef USER_H
#define USER_H
#include <string>
class User {
    int uid;
    std::string name, surname;
    int age, height, weight;
    char gender;
public:
    User(int);
    User(int, std::string, std::string, int, int, int, char);
    std::string get_name() const;
    std::string get_surname() const;
    int get_age() const;
    int get_height() const;
    int get_weight() const;
    char get_gender() const;
    int get_uid() const;
    //void set_uid(int);
};
#endif