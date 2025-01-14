#include "utils.hpp"


std::string Hash(const std::string& str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.length(), hash);

	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
	}
	return ss.str();
}


std::string EnterPassword() {
	std::string password;
	char ch;

	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (!password.empty()) {
				password.pop_back();
				std::cout << "\b \b";
			}
		}
		else {
			password.push_back(ch);
			std::cout << '*';
		}
	}
	std::cout << "\n";
	return password;
}


bool CheckPassword(const std::string& password) {
	if (password.length() <= 8) {
		return false;
	}

	bool has_upper = false;
	bool has_lower = false;
	bool has_digit = false;
	bool has_special = false;

	for (char ch : password) {
		if (std::isupper(ch)) {
			has_upper = true;
		}
		else if (std::islower(ch)) {
			has_lower = true;
		}
		else if (std::isdigit(ch)) {
			has_digit = true;
		}
		else if (std::ispunct(ch)) {
			has_special = true;
		}
	}

	return has_upper && has_lower && has_digit && has_special;
}