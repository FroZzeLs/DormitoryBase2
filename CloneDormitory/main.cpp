#include "mainMenu.h"

int main() {
    system("chcp 1251");
    system("cls");
    int choice = 1;
    std::vector<Floor> floors(16);
    Database dtb("Dormitory.db");
    dtb.createTables();
    dtb.loadFromDatabase(floors);

    while (choice != 0) {
        std::cout << "Выберите действие:\n1 - Добавить студента в БД\n2 - Вывести информацию по всем студентам\n3 - Найти информацию по одному студенту\n4 - Изменить данные студента\n5 - Удалить студента\n6 - Удалить всех студентов\n7 - Вывести должников\n0 - завершить программу" << std::endl;
        choice = inputInteger();

        switch (choice) {
        case 1: {
            addNewStudents(floors, dtb);
            break;
        }

        case 2: {
            std::cout << "\nВсе студенты:" << std::endl;
            printAllStudents(floors);
            break;
        }

        case 3: {
            printStudentBySnp(floors, searchStudent(floors));
            break;
        }

        case 4: {
            updateStudentInfo(searchStudent(floors), floors, dtb);
            break;
        }

        case 5: {
            deleteStudent(searchStudent(floors), floors, dtb);
            break;
        }

        case 6:
            removeAllStudents(floors, dtb);
            break;

        case 7: {
            printDebtorList(floors);
            break;
        }

        case 0:
            return 0;

        default:
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
            break;
        }
    }
    return 0;
}
