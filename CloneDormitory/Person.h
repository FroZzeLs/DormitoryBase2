#pragma once
#include <string>

class Person {
protected:
    std::string surname;
    std::string name;
    std::string patronym;
    std::string phoneNumber;
    int age;
public:
    Person(const std::string& surname, const std::string& name, const std::string& patronym, int age, const std::string& phoneNumber);
    virtual void inputPersonInfo() = 0;
};