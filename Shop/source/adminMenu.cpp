#include "adminMenu.hpp"

void AdminMenu() {

	std::string req;

	while (true) {
		system("cls");
		std::cout << "1. �����������\n"
			"2. �����\n"
			"3. ������������\n"
			"4. ������\n"
			"0. ����� �� ��������\n"
			">>> ";

		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			Assortment();
		}
		else if (req == "2") {
			Storage();
		}
		else if (req == "3") {
			Users();
		}
		else if (req == "4") {
			Discounts();
		}
		else {
			system("cls");
			std::cout << "������ �����\n";
		}
	}
}


void Assortment() {

	std::string req, str;
	std::string product_name, new_product_name;
	float product_price;

	while (true) {
		std::vector<Product> products = GetAllProducts();
		
		system("cls");
		std::cout << "������ ����� ������������:\n";

		std::cout << std::setw(5) << std::left << "ID" << std::setw(64) << "��������" << std::setw(5) << "����\n";
		for (const auto& product : products) {
			std::cout << std::left << std::setw(5) << product.id
				<< std::setw(64) << product.name << std::setw(15) 
				<< product.price << "\n";
		}

		std::cout << "1. �������� �����\n"
			"2. ������� �����\n"
			"3. ������������� �����\n"
			"0. �����\n"
			">>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			std::cout << "������� �������� ������ (0 - ��� ������): ";
			std::getline(std::cin, product_name, '\n');

			if (product_name == "0") {
				break;
			}

			std::cout << "������� ���� ������ (0 - ��� ������): ";
			std::getline(std::cin, str, '\n');
			product_price = std::stof(str);

			if (product_price == 0) {
				break;
			}
			else if (InsertNewProduct(product_name, product_price)) {
				system("cls");
				std::cout << "����� ������� ��������\n";
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "������� �������� ������ (0 - ��� ������): ";
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProduct(product_name)) {
					if (DeleteProduct(product_name)) {
						std::cout << "����� ������� �����\n";
						break;
					}
					else {
						std::cout << "������ ��� �������� �������\n";
					}
				}
				else {
					std::cout << "������ � ����� ������ �� ����������\n";
				}
			}
		}
		else if (req == "3") {
			while (true) {
				std::cout << "1. ������������� ��� ������\n"
					"2. ������������� ���� ������\n"
					"0. �����\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					while (true) {
						std::cout << "������� �������� ������ (0 - ��� ������):";
						std::getline(std::cin, product_name, '\n');

						if (product_name == "0") {
							break;
						}
						else if (GetProduct(product_name)) {
							std::cout << "������� ����� �������� ������ (0 - ��� ������): ";
							std::getline(std::cin, str, '\n');

							if (new_product_name == "0") {
								break;
							}
							else if (SetNewProductName(product_name, new_product_name)) {
								std::cout << "�������� ������ ������� ��������\n";
								break;
							}
							else {
								std::cout << "������ � ��������� �������� ������\n";
							}
						}
					}
				}
				else if (req == "2") {
					while (true) {
						std::cout << "������� �������� ������ (0 - ��� ������):";
						std::getline(std::cin, product_name, '\n');
						product_price = std::stof(str);

						if (product_name == "0") {
							break;
						}
						else if (GetProduct(product_name)) {
							std::cout << "������� ����� ���� ������ (0 - ��� ������): ";
							std::getline(std::cin, new_product_name, '\n');

							if (new_product_name == "0") {
								break;
							}
							else if (SetNewProductPrice(product_name, product_price)) {
								std::cout << "���� ������ ������� ��������\n";
								break;
							}
							else {
								std::cout << "������ � ��������� ���� ������\n";
							}
						}
					}
				}
				else {
					std::cout << "������ �����\n";
				}
			}
		}
		else {
			system("cls");
			std::cout << "������ �����\n";
		}
	}
}


void Storage() {
	std::string req;
	std::string product_name, product_count;
	int count;

	while (true) {
		system("cls");
		std::cout << "1. �������� ����� �� �����\n"
			"2. ������ ������ �� ������\n"
			"0. �����\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "������� �������� ������ ��� ���������� (0 - ��� ������): ";
				std::getline(std::cin, product_name, '\n');

				if (GetProduct(product_name)) {
					std::cout << "������� ���������� ������ ������ ������ ���������: ";
					std::getline(std::cin, product_count, '\n');
					count = std::stoi(product_count);
					if (AddProductToStorage(product_name, count)) {
						std::cout << "����� ������� �������� �� �����\n";
						break;
					}
					else {
						std::cout << "������ ��� ���������� ������\n";
					}
				}
				else {
					std::cout << "������ � ����� ������ �� ����������\n";
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "������� �������� ������ ��� �������� (0 - ��� ������): ";
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProduct(product_name)) {
					std::cout << "������� ���������� ������ ������ ������ �������: ";
					std::getline(std::cin, product_count, '\n');
					count = std::stoi(product_count);
					if (RemoveProductToStorage(product_name, count)) {
						std::cout << "����� ������� ������ �� ������\n";
						break;
					}
					else {
						std::cout << "������ ��� �������� ������\n";
					}
				}
				else {
					std::cout << "������ � ����� ������ �� ����������\n";
				}
			}
		}
		else {
			std::cout << "������ �����\n";
		}
	}

}


void Users() {
	
	std::string req;
	std::string login, new_login, password;

	while (true) {
		std::cout << "1. ������� �������\n"
			"2. ������������� �������\n"
			"3. ������� �������\n"
			"0. �����\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "������� ����� �������� (0 - ��� ������): ";
				std::getline(std::cin, login, '\n');

				if (login == "0") {
					system("cls");
					break;
				}

				std::cout << "������� ������ �� �������� (0 - ��� ������): ";
				password = EnterPassword();

				if (password == "0") {
					break;
				}
				else if (InsertUser(login, Hash(password))) {
					system("cls");
					std::cout << "������� ������� ������\n";
					break;
				}
				else {
					std::cout << "������ ��� �������� ��������\n";
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "1. ������������� �����\n"
					"2. ������������ ������\n"
					"3. ������������� ������\n"
					"0. �����\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					while (true) {
						std::cout << "������� ������� ����� ��������: ";
						std::getline(std::cin, login, '\n');

						if (IsUserExists(login)) {
							std::cout << "������� ����� ����� ��������: ";
							std::getline(std::cin, new_login, '\n');

							if (SetNewLogin(login, new_login)) {
								std::cout << "����� ������� ������\n";
								break;
							}
						}
						else {
							std::cout << "������������ � ����� ������� �� ����������\n";
						}

					}
					break;
				}
				else if (req == "2") {
					std::cout << "������� ����� ������������ ������� ������ �������� ������ (0 - ��� ������): ";
					std::getline(std::cin, login, '\n');

					if (password == "0") {
						break;
					}
					else if (IsUserExists(login)) {
						std::cout << "������� ����� ������: ";
						password = EnterPassword();

						SetNewPassword(login, Hash(password));
					}
					else {
						std::cout << "������������ � ����� ������� �� ����������\n";
					}
				}
				else if (req == "3") {
					while (true) {
						std::cout << "������� ����� ������������ ������� ������ �������� ������ (0 - ��� ������): ";
						std::getline(std::cin, login, '\n');

						if (IsUserExists(login)) {
							if (CheckIsAdmin(login)) {
								SetNewStatus(login, 1);
								std::cout << login << " ������� ���� ���������������\n";
								break;
							}
							else {
								SetNewStatus(login, 0);
								std::cout << login << " ������� ���� �������������\n";
								break;
							}
						}
						else {
							std::cout << "������������ � ����� ������� �� ����������\n";
						}
					}
				}
			}
		}
		else if (req == "3") {
			while (true) {
				std::cout << "������ ����� ������������ �������� ������ ������� (0 - ��� ������): ";
				std::getline(std::cin, login, '\n');

				if (login == "0") {
					break;
				}
				else if (IsUserExists(login)) {
					if (DeleteUser(login)) {
						system("cls");
						std::cout << "������������ " + login + " ������� �����\n";
						break;
					}
					else {
						std::cout << "������ � �������� ������������\n";
					}
				}
				else {
					std::cout << "������ ������������ �� ����������\n";
				}
			}
		}
		else {
			std::cout << "������ �����\n";
		}

	}
}


void Discounts() {
	std::string req;
	std::string str, product_name;
	float f_discount;
	int id;

	while (true) {
		std::vector<sDiscount> discounts = GetAllDiscounts();

		system("cls");
		std::cout << "������ ����� ������������:\n";

		std::cout << std::setw(5) << std::left << "ID" << std::setw(64) << "��������" << std::setw(5) << "����\n";
		for (const auto& discount : discounts) {
			std::cout << std::left << std::setw(5) << discount.id
				<< std::setw(64) << discount.type << std::setw(4)
				<< discount.discount << "\n";
		}

		std::cout << "1. �������� ������\n"
			"2. ������� ������\n"
			"0. �����\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "1. �������� ������ �� ���� �����������\n"
					"2. �������� ������ �� �����\n"
					"0. �����\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					std::cout << "������� ������: ";
					std::getline(std::cin, str, '\n');
				}
				else if (req == "2") {
					while (true) {
						std::cout << "������� �������� ������: ";
						std::getline(std::cin, product_name, '\n');

						if (GetProduct(product_name)) {
							std::cout << "������� ������: ";
							std::getline(std::cin, str, '\n');
							f_discount = std::stof(str);
						}
						else {
							std::cout << "������ ������ �� ����������\n";
						}
					}
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "������� id ������ (0 - ��� ������):";
				std::getline(std::cin, str, '\n');
				id = std::stoi(str);

				if (str == "0") {
					break;
				}
				else if (IsDiscountExists(id)) {
					DeleteDiscount(id);
					break;
				}
				else {
					std::cout << "������ � ����� id �� ����������\n";
				}
			}
		}
	}
}
