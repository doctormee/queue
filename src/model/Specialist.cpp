#include <Specialist.h>
#include <stdexcept>

Specialist::Specialist() {
    name = "John";
    surname = "Appleseed";
    services.clear();
}

Specialist::Specialist(std::string name_, std::string surname_) {
    name = name_;
    surname = surname_;
    services.clear();
}

std::string Specialist::get_service(int i) {
    if (i >= services.size()) {
        std::out_of_range ex("Index out of range");
        throw ex;
    }
    return services[i];
}

std::string Specialist::get_name() const {
    return name;
}
std::string Specialist::get_surname() const {
    return surname;
}
void Specialist::add_service(std::string service) {
    services.push_back(service);
}
