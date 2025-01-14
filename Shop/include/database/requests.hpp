#ifndef _REQUESTS_HPP_
#define _REQUESTS_HPP_

#include <vector>
#include <codecvt>
#include <locale>
#include "database.hpp"

struct Product {
	int id;
	std::string name;
	float price;
};

struct Products : Product {
	int count;
};

struct sDiscount {
	int id;
	std::string type;
	float discount;
};

bool IsUserExists(const std::string& login);
bool IsPasswordTrue(const std::string& login, const std::string& password);
bool CheckIsAdmin(const std::string& login);
float GetBalance(const std::string& login);
std::vector<Product> GetAllProducts();
bool GetProduct(const std::string& name);
std::vector<Products> GetProductsCatalog();
std::string IsProductExists(int id);
float GetProductPrice(const std::string& name);
int GetProductCount(const std::string& name);
std::vector<Products> GetBasketList(const std::string& login);
bool GetProductFromBasket(const std::string& login, const std::string& name);
float GetProductPriceFromBasket(const std::string& login, const std::string& name);
int GetProductCountFromBasket(const std::string& login, const std::string& name);
std::vector<float> GetAllProductsPrice(const std::string& login);
std::vector<sDiscount> GetAllDiscounts();
bool IsDiscountExists(int id);

#endif // !_REQUESTS_HPP_