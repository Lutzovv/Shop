#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <windows.h>

std::string EnterPassword();
std::string Hash(const std::string& str);
bool CheckPassword(const std::string& password);

#endif // !_UTILS_HPP_
