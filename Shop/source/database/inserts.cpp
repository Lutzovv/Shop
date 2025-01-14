#include "database/inserts.hpp"


bool InsertUser(const std::string& login, const std::string& password) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "INSERT INTO users (login, password) VALUES (?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при вставке данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool InsertNewProduct(const std::string& product_name, float product_price) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "INSERT INTO product_list (name, price) VALUES (?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, product_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, product_price);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при вставке данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool InsertProductInBasket(const std::string& login,
    const std::string& product_name,
    int count, float total_price) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "INSERT INTO basket (user_login, product_name, product_count, total_price) VALUES (?, ?, ?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, count);
    sqlite3_bind_double(stmt, 4, total_price);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при вставке данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool InsertDiscount(float discount, const std::string& type) {
    if (type == "") {
        type == "all";
    }

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "INSERT INTO discounts (type, discount) VALUES (?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, static_cast<double>(discount));

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при вставке данных: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}