#include "StudentManager.h"

void updateStudentInDb(sqlite3*& db, const StudentResident& oldInfo, const StudentResident& newInfo) {
    const char* sql = R"(
            UPDATE Students
            SET surname = ?, name = ?, patronym = ?, phoneNumber = ?, age = ?, blockNumber = ?, studActive = ?, opt = ?
            WHERE surname = ? AND name = ? AND patronym = ?;
        )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newInfo.getSurname().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, newInfo.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, newInfo.getPatronym().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, newInfo.getPhoneNumber().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, newInfo.getAge());
    sqlite3_bind_int(stmt, 6, newInfo.getBlockNumber());
    sqlite3_bind_int(stmt, 7, newInfo.getStudActive());
    sqlite3_bind_int(stmt, 8, newInfo.getOpt());
    sqlite3_bind_text(stmt, 9, oldInfo.getSurname().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, oldInfo.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 11, oldInfo.getPatronym().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка обновления данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

}
