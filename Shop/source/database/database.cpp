#include "./database/database.hpp"

sqlite3* OpenDatabase() {
    std::string db_name = "shop.db";

    sqlite3* db;
    int exit = sqlite3_open(db_name.c_str(), &db); // Открытие базы данных

    if (exit) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    return db;
}