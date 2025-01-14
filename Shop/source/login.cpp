#include "login.hpp"

void CreateAccount() {

	std::string login, password, password2;

	while (true) {
		while (true) {

			system("cls");
			std::cout << "Введите логин (0 - для выхода): ";
			std::getline(std::cin, login, '\n');
			
			if (IsUserExists(login)) {
				std::cout << "Такой логин уже занят\n";
			}
			else
			{
				break;
			}
		}

		while (true) {
			std::cout << "Введите пароль (0 - для выхода): ";
			password = EnterPassword();

			if (password == "0") {
				break;
			}
			else if (CheckPassword(password)) {
				while (true) {

					system("cls");

					std::cout << "Повторите пароль (0 - для выхода): ";
					password2 = EnterPassword();

					if (password2 == "0") {
						break;
					}
					else if (password == password2) {
						if (InsertUser(login, Hash(password))) {
							std::cout << "Аккаунт создан\n";
							break;
						}
						else {
							std::cerr << "Ошибка в создании пользователя\n";
						}
					}
					else {
						std::cout << "Пароли должны совпадать!\n";
					}
				}
				break;
			}
			else {
				system("cls");
				std::cout << "Слишком слабый пароль!\n"
					"В пароле должно быть более 8 символов\n"
					"Должна быть хотя бы 1 буква верхнего и нижнего регистра\n"
					"Хотя бы 1 цифра и 1 спец. символ\n";
			}

		}

		break;
	}
}


void LoginInAccaunt() {
	static std::string login;
	std::string password;

	while (true) {
		while (true) {

			system("cls");
			std::cout << "Введите логин (0 - для выхода): ";
			std::getline(std::cin, login, '\n');

			if (login == "0") {
				break;
			}
			else if (IsUserExists(login)) {
				while (true) {

					std::cout << "Введите пароль (0 - для выхода): ";
					password = EnterPassword();

					if (password == "0") {
						break;
					}
					else if (IsPasswordTrue(login, Hash(password))) {
						system("cls");
						std::cout << "Успешный вход\n";

						if (CheckIsAdmin(login)) {
							AdminMenu();
						}
						else {
							Menu(login);
						}

						break;
					}
					else {
						system("cls");
						std::cout << "Неверный пароль\n";
					}
				}
				break;
			}

		}

		break;
	}
}