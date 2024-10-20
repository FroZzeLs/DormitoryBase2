#include "BlockManager.h"

int getOrAddBlock(sqlite3* db, int blockNumber) {
    sqlite3_stmt* stmt;

    // Prepare and execute the SELECT statement.
    if (const char* selectBlockSQL = R"(
            SELECT id FROM Blocks WHERE blockNumber = ?;
        )"; sqlite3_prepare_v2(db, selectBlockSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_int(stmt, 1, blockNumber);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return id;
    }
    sqlite3_finalize(stmt);

    // Prepare and execute the INSERT statement.
    if (const char* insertBlockSQL = R"(
            INSERT OR IGNORE INTO Blocks (blockNumber, floorId, residentCount)
            VALUES (?, ?, 0);
        )"; sqlite3_prepare_v2(db, insertBlockSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    int floorNumber = blockNumber / 100;
    int floorId = getOrAddFloor(db, floorNumber);

    sqlite3_bind_int(stmt, 1, blockNumber);
    sqlite3_bind_int(stmt, 2, floorId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int blockId = sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return blockId;
}