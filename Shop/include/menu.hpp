#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <string>
#include "database/requests.hpp"
#include "database/edit.hpp"
#include "database/inserts.hpp"
#include "database/delete.hpp"
#include "utils.hpp"

void Menu(const std::string& login);
void Account(const std::string& login);
void ProductCatalog(const std::string& login);
void Basket(const std::string& login);
void TopUpBalance(const std::string& login);
void SetNewPassword(const std::string& login);

#endif // !_MENU_HPP_
