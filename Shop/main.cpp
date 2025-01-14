#include "login.hpp"

int main() {

	system("chcp 1251>nul");
	std::string req;
	
	while (true) {
		system("cls");
		std::cout << "1. Создать аккаунт\n2. Войти в аккаунт\n0. Выход\n>>> ";
		std::getline(std::cin, req, '\n');
		if (req == "0") {
			break;
		}
		else if (req == "1") {
			CreateAccount();
		}
		else if (req == "2") {
			LoginInAccaunt();
		}
		else {
			system("cls");
			std::cout << "Ошибка ввода\n";
		}
	}
	
}