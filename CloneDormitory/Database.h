#pragma once
#include <sqlite3.h>
#include "StudentResident.h"
#include "FloorManager.h"
#include "BlockManager.h"
#include "Floor.h"

class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& dbName); 
    ~Database();

    void deleteStudentFromDb(const StudentResident& student);
    void addStudentToDb(const StudentResident& student);
    sqlite3*& getDb();
    void createTables();
    void loadFromDatabase(std::vector<Floor>& floors);
    void clearDatabase();
};