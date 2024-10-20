#include "mainMenu.h"

void addNewStudents(std::vector<Floor>& floors, Database& dtb)
{
    std::cout << "Введите данные студента:" << std::endl;
    int newStudent = 0;
    do {
        StudentResident buffer("", "", "", -1, "", -1, -1, -1);
        buffer.inputInfo();
        addStudent(floors, buffer, dtb);
        std::cout << "Вы желаете продолжить добавление студентов?\nНажмите 1, если да, 0 - если нет:";
        std::cin >> newStudent;
        std::cin.ignore();
    } while (newStudent != 0);
    std::cout << "\nДанные успешно добавлены!" << std::endl;
}