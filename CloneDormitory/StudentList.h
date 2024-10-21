#pragma once
#include "ArrowsUsage.h"
#include "StudentManager.h"
#include "Database.h"
#include "StudentSearchException.h"

struct StudentPlace {
	int floor;
	int block;
	int number;
};

bool checkForOriginality(std::vector<Floor>& floors, const StudentResident& newStudent);

void addStudent(std::vector<Floor>& floors, const StudentResident& newStudent, Database& dtb);

void printAllStudents(std::vector<Floor>& floors);

bool doesStudentMatch(const StudentResident& student, std::string_view surname,
	std::string_view name, std::string_view patronym,
	std::string_view phoneNumber);

std::vector<StudentPlace> findStudentInBlock(const std::vector<StudentResident>& residents,
	const std::string& surname, const std::string& name,
	const std::string& patronym, const std::string& phoneNumber,
	int floorIndex, int blockIndex);

StudentPlace searchStudent(std::vector<Floor>& floors);

void printStudentBySnp(std::vector<Floor>& floors, const StudentPlace& place);

void deleteStudent(const StudentPlace& place, std::vector<Floor>& floors, Database& dtb);

void updateStudentInfo(const StudentPlace& Place, std::vector<Floor>& floors, Database& dtb);

void removeAllStudents(std::vector<Floor>& floors, Database& dtb);

void printDebtorList(std::vector<Floor>& floors);

void sortFloors(std::vector<Floor>& floors);