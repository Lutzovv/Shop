#include "./database/edit.hpp"

bool TopUpBalance(const std::string& login, float amount) {

    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE users SET balance = balance + ? WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_double(stmt, 1, static_cast<double>(amount));
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewPassword(const std::string& login, const std::string& password) {

    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE users SET password = ? WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewLogin(const std::string& login, const std::string& new_login) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE users SET login = ? WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, new_login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewStatus(const std::string& login, int is_admin) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE users SET is_admin = ? WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, is_admin);
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool AddProductToStorage(const std::string& name, int count) {

    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE storage SET count = count + ? WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, count);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool RemoveProductToStorage(const std::string& name, int count) {

    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE storage SET count = count + ? WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_double(stmt, 1, count);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewProductName(const std::string& product_name, const std::string& new_product_name) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE product_list SET name = ? WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, new_product_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product_name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewProductPrice(const std::string& product_name, float price) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE product_list SET price = ? WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_double(stmt, 1, static_cast<double>(price));
    sqlite3_bind_text(stmt, 2, product_name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool SetNewProductCountInBasket(const std::string& login, const std::string& name, int count) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE basket SET count = ? WHERE (user_login, product_name) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, count);
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}


bool DeductFromBalance(const std::string& login, float amount) {

    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE users SET balance = balance - ? WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_double(stmt, 1, static_cast<double>(amount));
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при обновлении данных: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exit == SQLITE_DONE;
}