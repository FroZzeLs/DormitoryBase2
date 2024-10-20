#pragma once
#include "ArrowsUsage.h"
#include "StudentManager.h"
#include "Database.h"

struct StudentPlace {
	int floor;
	int block;
	int number;
};

bool checkForOriginality(std::vector<Floor> floors, const StudentResident& newStudent);

void addStudent(std::vector<Floor>& floors, const StudentResident& newStudent, Database& dtb);

void printAllStudents(std::vector<Floor>& floors);

StudentPlace searchStudent(std::vector<Floor>& floors);

void printStudentBySnp(std::vector<Floor>& floors, const StudentPlace& place);

void deleteStudent(const StudentPlace& place, std::vector<Floor>& floors, Database& dtb);

void updateStudentInfo(const StudentPlace& Place, std::vector<Floor>& floors, Database& dtb);

void removeAllStudents(std::vector<Floor>& floors, Database& dtb);

void printDebtorList(std::vector<Floor> floors);
