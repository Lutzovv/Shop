#include "login.hpp"

void CreateAccount() {

	std::string login, password, password2;

	while (true) {
		while (true) {

			system("cls");
			std::cout << "������� ����� (0 - ��� ������): ";
			std::getline(std::cin, login, '\n');
			
			if (IsUserExists(login)) {
				std::cout << "����� ����� ��� �����\n";
			}
			else
			{
				break;
			}
		}

		while (true) {
			std::cout << "������� ������ (0 - ��� ������): ";
			password = EnterPassword();

			if (password == "0") {
				break;
			}
			else if (CheckPassword(password)) {
				while (true) {

					system("cls");

					std::cout << "��������� ������ (0 - ��� ������): ";
					password2 = EnterPassword();

					if (password2 == "0") {
						break;
					}
					else if (password == password2) {
						if (InsertUser(login, Hash(password))) {
							std::cout << "������� ������\n";
							break;
						}
						else {
							std::cerr << "������ � �������� ������������\n";
						}
					}
					else {
						std::cout << "������ ������ ���������!\n";
					}
				}
				break;
			}
			else {
				system("cls");
				std::cout << "������� ������ ������!\n"
					"� ������ ������ ���� ����� 8 ��������\n"
					"������ ���� ���� �� 1 ����� �������� � ������� ��������\n"
					"���� �� 1 ����� � 1 ����. ������\n";
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
			std::cout << "������� ����� (0 - ��� ������): ";
			std::getline(std::cin, login, '\n');

			if (login == "0") {
				break;
			}
			else if (IsUserExists(login)) {
				while (true) {

					std::cout << "������� ������ (0 - ��� ������): ";
					password = EnterPassword();

					if (password == "0") {
						break;
					}
					else if (IsPasswordTrue(login, Hash(password))) {
						system("cls");
						std::cout << "�������� ����\n";

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
						std::cout << "�������� ������\n";
					}
				}
				break;
			}

		}

		break;
	}
}