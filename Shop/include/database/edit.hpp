#ifndef _EDIT_HPP_
#define _EDIT_HPP_

#include "database.hpp"

bool TopUpBalance(const std::string& login, float amount);
bool SetNewPassword(const std::string& login, const std::string& password);
bool SetNewLogin(const std::string& login, const std::string& new_login);
bool SetNewStatus(const std::string& login, int is_admin);
bool AddProductToStorage(const std::string& name, int count);
bool RemoveProductToStorage(const std::string& product_name, int count);
bool SetNewProductName(const std::string& product_name, const std::string& new_product_name);
bool SetNewProductPrice(const std::string& product_name, float price);
bool SetNewProductCountInBasket(const std::string& login, const std::string& name, int count);
bool DeductFromBalance(const std::string& login, float amount);

#endif // !_EDIT_HPP_
