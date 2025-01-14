#ifndef _DELETE_HPP_
#define _DELETE_HPP_

#include "database.hpp"

bool DeleteUser(const std::string& login);
bool DeleteProduct(const std::string& name);
bool RemoveProductFromBasket(const std::string& login, const std::string& product_name);
bool DeleteDiscount(int id);

#endif // !_DELETE_HPP_
