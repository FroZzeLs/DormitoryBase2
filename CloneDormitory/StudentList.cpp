#include "StudentList.h"

bool checkForOriginality(std::vector<Floor> floors, const StudentResident& newStudent) {
    for (int i = 0; i < floors.size(); i++) {
        if (floors[i].blocks.empty())
            continue;

        for (int j = 0; j < floors[i].blocks.size(); j++) {
            auto residents = floors[i].blocks[j].getResidents();
            if (residents.empty())
                continue;

            for (int k = 0; k < residents.size(); k++) {
                if (residents[k] == newStudent)
                    return false;
            }
        }
    }
    return true;
}

void addStudent(std::vector<Floor>& floors, const StudentResident& newStudent, Database& dtb) {
    if (checkForOriginality(floors, newStudent)) {
        int floorIndex = newStudent.getBlockNumber() / 100 - 1;
        int blockOnFloorIndex = newStudent.getBlockNumber() % 100;
        floors[floorIndex].addResidentToBlock(blockOnFloorIndex, newStudent);
        dtb.addStudentToDb(newStudent);
    }
    else
        std::cout << "Данный студент уже имеется в базе." << std::endl;
}

void printAllStudents(std::vector<Floor>& floors) {
    int i = 0;
    int lastNotEmptyFloor = 0;
    while (i != -1) {
        system("cls");
        bool hasStudents = false;

        for (auto& block : floors[i].getBlocks()) {
            if (!block.getResidents().empty()) {
                hasStudents = true;
                break;
            }
        }

        if (!hasStudents) {
            if (i < floors.size() - 1) {
                i++;
            }
            else {
                std::cout << "Студенты в базе закончились.\nНажмите <- для перехода к предыдущему этажу, либо Enter для возвращения в меню.";
                handleKeyPress(i, floors.size() - 1, lastNotEmptyFloor);
            }
            continue;
        }

        std::cout << "Этаж " << floors[i].getFloorNumber() << ":" << std::endl;
        floors[i].printBlocksInfo();

        if (i == 0) {
            std::cout << "Нажмите -> для перехода к следующему этажу, либо Enter для возвращения в меню." << std::endl;
        }
        else if (i == floors.size() - 1) {
            std::cout << "Нажмите <- для перехода к предыдущему этажу, либо Enter для возвращения в меню." << std::endl;
        }
        else {
            std::cout << "Нажмите <- для перехода к предыдущему этажу, -> для перехода к следующему этажу, либо Enter для возвращения в меню." << std::endl;
        }
        lastNotEmptyFloor = i;
        handleKeyPress(i, floors.size() - 1, lastNotEmptyFloor);
    }
    system("cls");
}

StudentPlace searchStudent(std::vector<Floor>& floors) {
    std::string surname, name, patronym, phoneNumber;
    int blockNumber = -1, floorNumber = -1;

    std::cout << "Введите фамилию (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, surname);

    std::cout << "Введите имя (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, name);

    std::cout << "Введите отчество (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, patronym);

    std::cout << "Введите номер телефона (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, phoneNumber);

    std::string input;
    std::cout << "Введите номер блока (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, input);
    if (!input.empty()) blockNumber = std::stoi(input);

    std::cout << "Введите номер этажа (или нажмите Enter, чтобы пропустить): ";
    std::getline(std::cin, input);
    if (!input.empty()) floorNumber = std::stoi(input);

    std::vector<StudentResident> foundStudents;
    std::vector<StudentPlace> foundPlaces;

    for (int i = 0; i < floors.size(); ++i) {
        if (floors[i].getBlocks().empty())
            continue;
        for (int j = 0; j < floors[i].getBlocks().size(); ++j) {
            if (floors[i].getBlocks()[j].getResidents().empty())
                continue;
            std::vector<StudentResident> residents = floors[i].getBlocks()[j].getResidents();
            for (int k = 0; k < residents.size(); k++) {
                bool match = true;

                if (!surname.empty() && residents[k].getSurname() != surname) {
                    match = false;
                }
                if (!name.empty() && residents[k].getName() != name) {
                    match = false;
                }
                if (!patronym.empty() && residents[k].getPatronym() != patronym) {
                    match = false;
                }
                if (!phoneNumber.empty() && residents[k].getPhoneNumber() != phoneNumber) {
                    match = false;
                }

                if (match) {
                    foundStudents.push_back(residents[k]);
                    StudentPlace founded;
                    founded.floor = i, founded.block = j, founded.number = k;
                    foundPlaces.push_back(founded);
                }
            }
        }
    }

    if (foundStudents.empty()) {
        std::cout << "Студенты с заданными параметрами не найдены.\n";
        StudentPlace noStudent;
        noStudent.floor = -1, noStudent.block = -1, noStudent.number = -1;
        throw std::runtime_error("No students found");
        return noStudent;
    }

    if (foundStudents.size() == 1) {
        return foundPlaces[0];
    }

    std::cout << "Найдено несколько студентов:\n";
    for (int i = 0; i < foundStudents.size(); ++i) {
        std::cout << i + 1 << ". " << foundStudents[i].getSurname() << " " << foundStudents[i].getName() << " "
            << foundStudents[i].getPatronym() << ", Блок: " << foundStudents[i].getBlockNumber() << "\n";
    }

    std::cout << "Выберите студента по номеру: ";
    int choice;
    choice = inputInteger();
    return foundPlaces[choice - 1];

    std::cout << "Неверный выбор.\n";
    throw std::runtime_error("Invalid choice");
}

void printStudentBySnp(std::vector<Floor>& floors, const StudentPlace& place) {
    if (place.floor != -1) {
        floors[place.floor].getBlocks()[place.block].getResidents()[place.number].printInfo(2);
    }
}

void updateStudentInfo(const StudentPlace& place, std::vector<Floor>& floors, Database& dtb) {
    if (place.floor == -1) {
        return;
    }

    std::cout << "Изменение информации о студенте:" << std::endl;
    auto& updatedStudent = floors[place.floor].getBlocks()[place.block].getResidents()[place.number];
    StudentResident oldInfo(updatedStudent.getSurname(), updatedStudent.getName(), updatedStudent.getPatronym(), updatedStudent.getAge(), 
        updatedStudent.getPhoneNumber(), updatedStudent.getBlockNumber(), updatedStudent.getStudActive(), updatedStudent.getOpt());
    updatedStudent.inputInfo();
    updateStudentInDb(dtb.getDb(), oldInfo, updatedStudent);
    return;
}

void deleteStudent(const StudentPlace& place, std::vector<Floor>& floors, Database& dtb) {
    if (place.floor == -1) {
        return;
    }
    auto& residents = floors[place.floor].getBlocks()[place.block].getResidents();
    dtb.deleteStudentFromDb(residents[place.number]);
    residents.erase(residents.begin() + place.number);
    floors[place.floor].getBlocks()[place.block].setResidentCount(floors[place.floor].getBlocks()[place.block].getResidentCount() - 1);
}

void removeAllStudents(std::vector<Floor>& floors, Database& dtb) {
    for (int i = 0; i < floors.size(); i++) {
        for (int j = 0; j < floors[i].getBlocks().size(); j++)
            floors[i].getBlocks()[j].getResidents().clear();
        floors[i].getBlocks().clear();
    }
    std::vector<Floor> newFloors(16);
    floors = newFloors;
    dtb.clearDatabase();
    std::cout << "Все студенты удалены!" << std::endl;
}

void printDebtorList(std::vector<Floor> floors) {
    std::vector<StudentResident> debtors;
    for (int i = 0; i < floors.size(); i++) {
        if (floors[i].getBlocks().empty())
            continue;
        for (int j = 0; j < floors[i].getBlocks().size(); j++) {
            if (floors[i].getBlocks()[j].getResidents().empty())
                continue;
            for (int k = 0; k < floors[i].getBlocks()[j].getResidents().size(); k++) {
                if (floors[i].getBlocks()[j].getResidents()[k].getDebtor())
                    debtors.push_back(floors[i].getBlocks()[j].getResidents()[k]);
            }
        }
    }
    if (debtors.empty()) {
        std::cout << "Должников нет!" << std::endl;
        return;
    }
    std::cout << "Должники ОПТ:" << std::endl;
    for (int i = 0; i < debtors.size(); i++) {
        debtors[i].printInfo(2);
    }
}