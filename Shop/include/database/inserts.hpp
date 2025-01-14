#ifndef _INSERTS_HPP_
#define _INSERTS_HPP_

#include "database.hpp"

bool InsertUser(const std::string& login, const std::string& password);
bool InsertNewProduct(const std::string& product_name, float product_price);
bool InsertProductInBasket(const std::string& login,
	const std::string& product_name,
	int count, float total_price);
bool InsertDiscount(float discount, const std::string& type = "all");

#endif // !_INSERTS_HPP_
