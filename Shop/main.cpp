#include "login.hpp"

int main() {

	system("chcp 1251>nul");
	std::string req;
	
	while (true) {
		system("cls");
		std::cout << "1. ������� �������\n2. ����� � �������\n0. �����\n>>> ";
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
			std::cout << "������ �����\n";
		}
	}
	
}