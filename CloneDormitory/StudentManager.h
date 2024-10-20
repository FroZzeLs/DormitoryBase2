#pragma once
#include "Database.h"

void updateStudentInDb(sqlite3*& db, const StudentResident& oldInfo, const StudentResident& newInfo);