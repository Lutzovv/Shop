#include "./database/requests.hpp"

bool IsUserExists(const std::string& login) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT COUNT(*) FROM users WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in SQL: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}


bool IsPasswordTrue(const std::string& login, const std::string& password) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT COUNT(*) FROM users WHERE (login, password) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}


bool CheckIsAdmin(const std::string& login) {
    sqlite3* db = OpenDatabase();
    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT is_admin FROM users WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    bool is_admin = false;
    if (exit == SQLITE_ROW) {
        is_admin = sqlite3_column_int(stmt, 0) == 1;
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return is_admin;
}













float GetBalance(const std::string& login) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return 0;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT balance FROM users WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);

    float balance{};

    if (exit == SQLITE_ROW) {
        balance = static_cast<float>(sqlite3_column_double(stmt, 0));
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return balance;
}


std::vector<Product> GetAllProducts() {
    std::vector<Product> products;
    sqlite3* db = OpenDatabase();
    if (!db) {
        return products;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM product_list;";
    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return products;
    }

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        Product product;
        product.id = sqlite3_column_int(stmt, 0);

        const unsigned char* name = sqlite3_column_text(stmt, 1);
        if (name) {
            product.name = reinterpret_cast<const char*>(name);
        }

        product.price = static_cast<float>(sqlite3_column_double(stmt, 2));
        products.push_back(product);
    }

    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return products;
}


bool GetProduct(const std::string& name) {
    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT COUNT(*) FROM product_list WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}


std::vector<Products> GetProductsCatalog() {

    std::vector<Products> products;

    sqlite3* db = OpenDatabase();

    if (!db) {
        return products;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT p.id, p.name, p.price, s.count FROM products p JOIN storage s ON p.id = s.id;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return products;
    }

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        Products product;
        product.id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        if (name) {
            product.name = reinterpret_cast<const char*>(name);
        }
        product.price = static_cast<float>(sqlite3_column_double(stmt, 2));
        product.count = static_cast<int>(sqlite3_column_double(stmt, 3));

        products.push_back(product);
    }

    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return products;
}


std::string IsProductExists(int id) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return "";
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT name FROM product_list WHERE id = ?;";


    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return "";
    }

    sqlite3_bind_int(stmt, 1, id);

    exit = sqlite3_step(stmt);
    std::string product_name;
    if (exit == SQLITE_ROW) {
        product_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return product_name;
}


float GetProductPrice(const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return 0;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT price FROM product_list WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    float product_price{};

    if (exit == SQLITE_ROW) {
        product_price = static_cast<float>(sqlite3_column_double(stmt, 0));
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return product_price;
}

int GetProductCount(const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return 0;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT count FROM storage WHERE name = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    int product_count{};

    if (exit == SQLITE_ROW) {
        product_count = sqlite3_column_int(stmt, 0);
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return product_count;
}


std::vector<Products> GetBasketList(const std::string& login) {

    std::vector<Products> products;

    sqlite3* db = OpenDatabase();

    if (!db) {
        return products;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM basket WHERE login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return products;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        Products product;
        product.id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        if (name) {
            product.name = reinterpret_cast<const char*>(name);
        }
        product.price = static_cast<float>(sqlite3_column_double(stmt, 2));
        product.count = static_cast<int>(sqlite3_column_double(stmt, 3));

        products.push_back(product);
    }

    if (exit != SQLITE_DONE) {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return products;
}


bool GetProductFromBasket(const std::string& login, const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT COUNT(*) FROM basket WHERE (user_login, product_name) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}


float GetProductPriceFromBasket(const std::string& login, const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return 0;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT price FROM basket WHERE (user_login, product_name) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
    float product_price{};

    if (exit == SQLITE_ROW) {
        product_price = static_cast<float>(sqlite3_column_double(stmt, 0));
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return product_price;
}


int GetProductCountFromBasket(const std::string& login, const std::string& name) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return 0;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT count FROM basket WHERE (user_login, product_name) = (?, ?);";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
    int product_count{};

    if (exit == SQLITE_ROW) {
        product_count = sqlite3_column_int(stmt, 0);
    }
    else {
        std::cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return product_count;
}


std::vector<float> GetAllProductsPrice(const std::string& login) {
    std::vector<float> prices;

    sqlite3* db = OpenDatabase();

    if (!db) {
        return prices;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT price FROM cart WHERE user_login = ?;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return prices;
    }

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        float price = static_cast<float>(sqlite3_column_double(stmt, 0));
        prices.push_back(price);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return prices;
}


std::vector<sDiscount> GetAllDiscounts() {

    std::vector<sDiscount> discounts;
    sqlite3* db = OpenDatabase();
    if (!db) {
        std::cerr << "Ошибка при открытии базы данных." << "\n";
        return discounts;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM discounts;";

    int exit = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Ошибка в SQL: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return discounts;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        sDiscount discount;
        discount.id = sqlite3_column_int(stmt, 0);
        discount.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        discount.discount = static_cast<float>(sqlite3_column_double(stmt, 2));

        discounts.push_back(discount);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return discounts;
}


bool IsDiscountExists(int id) {

    sqlite3* db = OpenDatabase();

    if (!db) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* reqest = "SELECT COUNT(*) FROM discounts WHERE id = ?;";

    int exit = sqlite3_prepare_v2(db, reqest, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in SQL: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}