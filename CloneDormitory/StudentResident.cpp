#include "StudentResident.h"

void StudentResident::inputPersonInfo() {
    std::cout << "������� ������� ��������: ";
    std::getline(std::cin, surname);

    std::cout << "������� ��� ��������: ";
    std::getline(std::cin, name);

    std::cout << "������� �������� ��������: ";
    std::getline(std::cin, patronym);

    std::cout << "������� �������: ";
    age = inputInteger();

    std::cout << "������� ����� ��������: ";
    std::getline(std::cin, phoneNumber);
}

void StudentResident::inputResidentInfo() {
    std::cout << "������� ����� �����: ";
    blockNumber = inputInteger();

    std::cout << "������� ������ �������� (0 - �� ��������, 1 - ���� ����������, 2 - ��): ";
    studActive = inputInteger();

    if (studActive != 0) {
        opt = 36;
    }
    else {
        std::cout << "������� ���������� ������������ ����� ���: ";
        opt = inputInteger();
    }

    if (opt < normOfOpt()) {
        debtor = true;
    }
    else {
        debtor = false;
    }
}

StudentResident::StudentResident(const std::string& surname, const std::string& name, const std::string& patronym, int age,
    const std::string& phoneNumber, int blockNumber, int studActive, int opt)
    : Person(surname, name, patronym, age, phoneNumber),
    Resident(blockNumber, studActive, opt) {}

StudentResident::StudentResident() : Person("", "", "", -1, ""), Resident(-1, -1, -1) {}

void StudentResident::inputInfo() {
    inputPersonInfo();
    inputResidentInfo();
}

void StudentResident::printInfo(int mode) const {
    std::cout << "\n���: " << surname << " " << name << " " << patronym << std::endl;
    if (mode == 2)
        std::cout << "����� �����: " << blockNumber << std::endl;
    std::cout << "�������: " << age << std::endl;
    std::cout << "������������ ���� ���: " << opt << std::endl;
    std::cout << "����� ��������: " << phoneNumber << std::endl;
    if (debtor) {
        std::cout << "���� ���: " << normOfOpt() - opt << std::endl;
    }
}

std::string StudentResident::getSurname() const {
    return surname;
}

std::string StudentResident::getName() const {
    return name;
}

std::string StudentResident::getPatronym() const {
    return patronym;
}

int StudentResident::getAge() const {
    return age;
}

int StudentResident::getOpt() const {
    return opt;
}

std::string StudentResident::getPhoneNumber() const {
    return phoneNumber;
}

int StudentResident::getStudActive() const {
    return studActive;
}

int StudentResident::getBlockNumber() const {
    return blockNumber;
}

bool StudentResident::getDebtor() const {
    return debtor;
}

void StudentResident::setSurname(std::string_view studentsSurname) {
    surname = studentsSurname;
}

void StudentResident::setName(std::string_view studentsName) {
    name = studentsName;
}

void StudentResident::setPatronym(std::string_view studentsPatronym) {
    patronym = studentsPatronym;
}

void StudentResident::setAge(int studentsAge) {
    age = studentsAge;
}

void StudentResident::setOpt(int studentsOpt) {
    opt = studentsOpt;
}

void StudentResident::setPhoneNumber(std::string_view studentsPhoneNumber) {
    phoneNumber = studentsPhoneNumber;
}

void StudentResident::setStudActive(int activityType) {
    studActive = activityType;
}

void StudentResident::setBlockNumber(int studentsBlock) {
    blockNumber = studentsBlock;
}

void StudentResident::setDebtor(bool isDebtor) {
    debtor = isDebtor;
}

bool StudentResident::operator==(const StudentResident& other) const {
    return surname == other.surname &&
        name == other.name &&
        patronym == other.patronym &&
        phoneNumber == other.phoneNumber &&
        age == other.age;
}
