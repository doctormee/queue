#include "User.h"

User::User(int uid_) {
    uid = uid_;
    name = "John";
    surname = "Appleseed";
    age = 21;
    height = 180;
    weight = 80;
    gender = 'M';
}

User::User(int uid_, std::string name_, std::string surname_, int age_, int height_, int weight_, char gender_) {
    uid = uid_;
    name = name_;
    surname = surname_;
    age = age_;
    height = height_;
    weight = weight_;
    gender = gender_;
};

std::string User::get_name() const {
    return name;
}

std::string User::get_surname() const {
    return surname;
}

int User::get_age() const {
    return age;
}

int User::get_height() const {
    return height;
}

int User::get_weight() const {
    return weight;
}

char User::get_gender() const {
    return gender;
}

int User::get_uid() const {
    return uid;
}