#include "database/delete.hpp"


bool DeleteUser(const std::string& login) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM users WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool DeleteProduct(const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM product_list WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool RemoveProductFromBasket(const std::string& login, const std::string& product_name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM basket WHERE (login, name) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product_name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool DeleteDiscount(int id) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM discounts WHERE id = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}