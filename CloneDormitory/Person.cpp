#include "Person.h"

Person::Person(const std::string& surname, const std::string& name, const std::string& patronym, int age, const std::string& phoneNumber)
    : surname(surname), name(name), patronym(patronym), phoneNumber(phoneNumber), age(age) {}
