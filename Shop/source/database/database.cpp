#include "./database/database.hpp"

sqlite3* OpenDatabase() {
    std::string db_name = "shop.db";

    sqlite3* db;
    int exit = sqlite3_open(db_name.c_str(), &db); // �������� ���� ������

    if (exit) {
        std::cerr << "������ �������� ���� ������: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    return db;
}