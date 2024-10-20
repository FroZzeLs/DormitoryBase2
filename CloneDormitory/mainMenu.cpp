#include "mainMenu.h"

void addNewStudents(std::vector<Floor>& floors, Database& dtb)
{
    std::cout << "������� ������ ��������:" << std::endl;
    int newStudent = 0;
    do {
        StudentResident buffer("", "", "", -1, "", -1, -1, -1);
        buffer.inputInfo();
        addStudent(floors, buffer, dtb);
        std::cout << "�� ������� ���������� ���������� ���������?\n������� 1, ���� ��, 0 - ���� ���:";
        std::cin >> newStudent;
        std::cin.ignore();
    } while (newStudent != 0);
    std::cout << "\n������ ������� ���������!" << std::endl;
}