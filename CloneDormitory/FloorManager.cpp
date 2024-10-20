#include "FloorManager.h"

int getOrAddFloor(sqlite3* db, int floorNumber) {
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, R"(
            SELECT id FROM Floors WHERE floorNumber = ?;
        )", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_int(stmt, 1, floorNumber);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, R"(
            INSERT OR IGNORE INTO Floors (floorNumber, mentor)
            VALUES (?, ?);
        )", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    std::string mentor;
    std::cout << "Введите ФИО воспитателя этажа " << floorNumber << ": ";
    std::getline(std::cin, mentor);

    sqlite3_bind_int(stmt, 1, floorNumber);
    sqlite3_bind_text(stmt, 2, mentor.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int floorId = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return floorId;
}