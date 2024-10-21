#include "Database.h"

Database::Database(const std::string& dbName) : dbName(dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::Database(const Database& other) {
    if (sqlite3_open(other.getDbName().c_str(), &db) != SQLITE_OK) {
        throw DatabaseException("Не удалось открыть базу данных в конструкторе копирования");
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

std::string Database::getDbName() const {
    return dbName;
}

sqlite3*& Database::getDb() {
    return db;
}

void Database::createTables() {
    const char* createFloorsTable = R"(
            CREATE TABLE IF NOT EXISTS Floors (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                floorNumber INTEGER UNIQUE,
                mentor TEXT
            );
        )";

    const char* createBlocksTable = R"(
            CREATE TABLE IF NOT EXISTS Blocks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                blockNumber INTEGER UNIQUE,
                floorId INTEGER,
                residentCount INTEGER DEFAULT 0,
                FOREIGN KEY(floorId) REFERENCES Floors(id)
            );
        )";

    const char* createStudentsTable = R"(
            CREATE TABLE IF NOT EXISTS Students (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                blockId INTEGER,
                surname TEXT,
                name TEXT,
                patronym TEXT,
                phoneNumber TEXT UNIQUE,
                age INTEGER,
                blockNumber INTEGER,
                studActive INTEGER,
                opt INTEGER,
                FOREIGN KEY(blockId) REFERENCES Blocks(id)
            );
        )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createFloorsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы Floors: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, createBlocksTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы Blocks: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, createStudentsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы Students: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::clearDatabase() {
    const char* clearDataSQL = "DELETE FROM Floors; DELETE FROM Blocks; DELETE FROM Students;";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, clearDataSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка очистки БД: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::loadFromDatabase(std::vector<Floor>& floors) {
    sqlite3_stmt* stmt = nullptr;

    if (const char* selectFloorsSQL = R"(
        SELECT floorNumber, mentor FROM Floors;
    )"; sqlite3_prepare_v2(db, selectFloorsSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса Floors: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int floorNumber = sqlite3_column_int(stmt, 0);
        std::string mentor = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        int floorIndex = floorNumber - 1;

        if (floorIndex >= 0 && floorIndex < floors.size()) {
            floors[floorIndex].setFloorNumber(floorNumber);
            floors[floorIndex].setMentor(mentor);
        }

        int floorId = getOrAddFloor(db, floorNumber);

        const char* selectBlocksSQL = R"(
            SELECT blockNumber FROM Blocks WHERE floorId = ?;
        )";

        sqlite3_stmt* blockStmt = nullptr;
        if (sqlite3_prepare_v2(db, selectBlocksSQL, -1, &blockStmt, nullptr) != SQLITE_OK) {
            std::cerr << "Ошибка подготовки запроса Blocks: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return;
        }

        sqlite3_bind_int(blockStmt, 1, floorId);

        while (sqlite3_step(blockStmt) == SQLITE_ROW) {
            int blockNumber = sqlite3_column_int(blockStmt, 0);
            int blockIndex = blockNumber - 1;

            if (blockIndex >= 0) {
                if (blockIndex >= floors[floorIndex].blocks.size()) {
                    floors[floorIndex].blocks.resize(blockIndex + 1);
                }
                floors[floorIndex].blocks[blockIndex].setBlockNumber(blockNumber);
            }

            int blockId = getOrAddBlock(db, blockNumber);

            const char* selectStudentsSQL = R"(
                SELECT surname, name, patronym, phoneNumber, age, blockNumber, studActive, opt FROM Students WHERE blockId = ?;
            )";

            sqlite3_stmt* studentStmt = nullptr;
            if (sqlite3_prepare_v2(db, selectStudentsSQL, -1, &studentStmt, nullptr) != SQLITE_OK) {
                std::cerr << "Ошибка подготовки запроса Students: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(blockStmt);
                sqlite3_finalize(stmt);
                return;
            }

            sqlite3_bind_int(studentStmt, 1, blockId);

            while (sqlite3_step(studentStmt) == SQLITE_ROW) {
                std::string surname = reinterpret_cast<const char*>(sqlite3_column_text(studentStmt, 0));
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(studentStmt, 1));
                std::string patronym = reinterpret_cast<const char*>(sqlite3_column_text(studentStmt, 2));
                std::string phoneNumber = reinterpret_cast<const char*>(sqlite3_column_text(studentStmt, 3));
                int age = sqlite3_column_int(studentStmt, 4);
                int storedBlockNumber = sqlite3_column_int(studentStmt, 5);
                int studActive = sqlite3_column_int(studentStmt, 6);
                int opt = sqlite3_column_int(studentStmt, 7);

                StudentResident buffer(surname, name, patronym, age, phoneNumber, storedBlockNumber, studActive, opt);
                floors[floorIndex].blocks[blockIndex].addResident(buffer);
            }
            sqlite3_finalize(studentStmt);
        }
        sqlite3_finalize(blockStmt);
    }
    sqlite3_finalize(stmt);
}

void Database::addStudentToDb(const StudentResident& student) {
    const char* insertStudentSQL = R"(
            INSERT OR REPLACE INTO Students (blockId, surname, name, patronym, phoneNumber, age, blockNumber, studActive, opt)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);
        )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, insertStudentSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    int blockId = getOrAddBlock(db, student.getBlockNumber());

    sqlite3_bind_int(stmt, 1, blockId);
    sqlite3_bind_text(stmt, 2, student.getSurname().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, student.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, student.getPatronym().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, student.getPhoneNumber().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, student.getAge());
    sqlite3_bind_int(stmt, 7, student.getBlockNumber());
    sqlite3_bind_int(stmt, 8, student.getStudActive());
    sqlite3_bind_int(stmt, 9, student.getOpt());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);

    insertStudentSQL = R"(
           UPDATE Blocks SET  residentCount = residentCount + 1 WHERE blockNumber = ?;
        )";

    if (sqlite3_prepare_v2(db, insertStudentSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, student.getBlockNumber());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка обновления данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

}


void Database::deleteStudentFromDb(const StudentResident& student) {
    sqlite3_stmt* stmt;

    const char* deleteStudentSQL = R"(
        DELETE FROM Students
        WHERE blockId = ? AND surname = ? AND name = ? AND patronym = ? AND phoneNumber = ?;
    )";

    if (sqlite3_prepare_v2(db, deleteStudentSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, getOrAddBlock(db, student.getBlockNumber()));
    sqlite3_bind_text(stmt, 2, student.getSurname().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, student.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, student.getPatronym().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, student.getPhoneNumber().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    deleteStudentSQL = R"(
            UPDATE Blocks
            SET residentCount = residentCount - 1 WHERE blockNumber = ?;
        )";

    if (sqlite3_prepare_v2(db, deleteStudentSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, student.getBlockNumber());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка обновления данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

}

Database& Database::operator=(const Database& other) {
    if (this != &other) {
        if (db) {
            sqlite3_close(db);
        }

        dbName = other.dbName;
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            throw DatabaseException("Не удалось открыть базу данных в операторе копирования");
        }
    }
    return *this;
}