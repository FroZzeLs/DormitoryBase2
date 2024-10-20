#pragma once
#include <iostream>
#include <string>
#include "Resident.h"
#include "Person.h"

class StudentResident : public Person, public Resident {
public:
    StudentResident(const std::string& surname, const std::string& name, const std::string& patronym, int age,
        const std::string& phoneNumber, int blockNumber, int studActive, int opt);
    StudentResident();

    void inputPersonInfo() override;
    void inputResidentInfo() override;
    void inputInfo();
    void printInfo(int mode) const;

    std::string getSurname() const;
    std::string getName() const;
    std::string getPatronym() const;
    std::string getPhoneNumber() const;
    int getAge() const;
    int getOpt() const;
    int getStudActive() const;
    int getBlockNumber() const;
    bool getDebtor() const;

    void setSurname(std::string_view studentsSurname);
    void setName(std::string_view studentsName);
    void setPatronym(std::string_view studentsPatronym);
    void setAge(int studentsAge);
    void setOpt(int studentsOPT);
    void setPhoneNumber(std::string_view studentsPhoneNumber);
    void setStudActive(int activityType);
    void setBlockNumber(int studentsBlock);
    void setDebtor(bool isDebtor);

    bool operator==(const StudentResident& other) const;
};