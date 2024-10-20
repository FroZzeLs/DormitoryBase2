#pragma once
#include <sqlite3.h>
#include "StudentResident.h"
#include "FloorManager.h"
#include "BlockManager.h"
#include "Floor.h"
#include "DatabaseException.h"

class Database {
private:
    sqlite3* db;
    std::string dbName;

public:
    explicit Database(const std::string& dbName);
    Database(const Database& other);
    ~Database();

    std::string getDbName() const;
    void deleteStudentFromDb(const StudentResident& student);
    void addStudentToDb(const StudentResident& student);
    sqlite3*& getDb();
    void createTables();
    void loadFromDatabase(std::vector<Floor>& floors);
    void clearDatabase();
    Database& operator=(const Database& other);
};