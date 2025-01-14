#include "adminMenu.hpp"

void AdminMenu() {

	std::string req;

	while (true) {
		system("cls");
		std::cout << "1. Ассортимент\n"
			"2. Склад\n"
			"3. Пользователи\n"
			"4. Скидки\n"
			"0. Выйти из аккаунта\n"
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
			std::cout << "Ошибка ввода\n";
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
		std::cout << "Список всего ассортимента:\n";

		std::cout << std::setw(5) << std::left << "ID" << std::setw(64) << "Название" << std::setw(5) << "Цена\n";
		for (const auto& product : products) {
			std::cout << std::left << std::setw(5) << product.id
				<< std::setw(64) << product.name << std::setw(15) 
				<< product.price << "\n";
		}

		std::cout << "1. Добавить товар\n"
			"2. Удалить товар\n"
			"3. Редактировать товар\n"
			"0. Выйти\n"
			">>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			std::cout << "Введите название товара (0 - для выхода): ";
			std::getline(std::cin, product_name, '\n');

			if (product_name == "0") {
				break;
			}

			std::cout << "Введите цену товара (0 - для выхода): ";
			std::getline(std::cin, str, '\n');
			product_price = std::stof(str);

			if (product_price == 0) {
				break;
			}
			else if (InsertNewProduct(product_name, product_price)) {
				system("cls");
				std::cout << "Товар успешно добавлен\n";
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "Введите название товара (0 - для выхода): ";
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProduct(product_name)) {
					if (DeleteProduct(product_name)) {
						std::cout << "Товар успешно удалён\n";
						break;
					}
					else {
						std::cout << "Ошибка при удалении товаров\n";
					}
				}
				else {
					std::cout << "Товара с таким именем не существует\n";
				}
			}
		}
		else if (req == "3") {
			while (true) {
				std::cout << "1. Редактировать имя товара\n"
					"2. Редактировать цену товара\n"
					"0. Выйти\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					while (true) {
						std::cout << "Введите название товара (0 - для выхода):";
						std::getline(std::cin, product_name, '\n');

						if (product_name == "0") {
							break;
						}
						else if (GetProduct(product_name)) {
							std::cout << "Введите новое название товара (0 - для выхода): ";
							std::getline(std::cin, str, '\n');

							if (new_product_name == "0") {
								break;
							}
							else if (SetNewProductName(product_name, new_product_name)) {
								std::cout << "Название товара успешно изменено\n";
								break;
							}
							else {
								std::cout << "Ошибка в изменении названия товара\n";
							}
						}
					}
				}
				else if (req == "2") {
					while (true) {
						std::cout << "Введите название товара (0 - для выхода):";
						std::getline(std::cin, product_name, '\n');
						product_price = std::stof(str);

						if (product_name == "0") {
							break;
						}
						else if (GetProduct(product_name)) {
							std::cout << "Введите новую цену товара (0 - для выхода): ";
							std::getline(std::cin, new_product_name, '\n');

							if (new_product_name == "0") {
								break;
							}
							else if (SetNewProductPrice(product_name, product_price)) {
								std::cout << "Цена товара успешно изменено\n";
								break;
							}
							else {
								std::cout << "Ошибка в изменении цены товара\n";
							}
						}
					}
				}
				else {
					std::cout << "Ошибка ввода\n";
				}
			}
		}
		else {
			system("cls");
			std::cout << "Ошибка ввода\n";
		}
	}
}


void Storage() {
	std::string req;
	std::string product_name, product_count;
	int count;

	while (true) {
		system("cls");
		std::cout << "1. Добавить товар на склад\n"
			"2. Убрать товары со склада\n"
			"0. Выйти\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "Введите название товара для пополнения (0 - для выхода): ";
				std::getline(std::cin, product_name, '\n');

				if (GetProduct(product_name)) {
					std::cout << "Введите количество товара хоторе хотите пополнить: ";
					std::getline(std::cin, product_count, '\n');
					count = std::stoi(product_count);
					if (AddProductToStorage(product_name, count)) {
						std::cout << "Товар успешно добавлен на склад\n";
						break;
					}
					else {
						std::cout << "Ошибка при пополнении товара\n";
					}
				}
				else {
					std::cout << "Товара с таким именем не существует\n";
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "Введите название товара для списания (0 - для выхода): ";
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProduct(product_name)) {
					std::cout << "Введите количество товара хоторе хотите списать: ";
					std::getline(std::cin, product_count, '\n');
					count = std::stoi(product_count);
					if (RemoveProductToStorage(product_name, count)) {
						std::cout << "Товар успешно списан со склада\n";
						break;
					}
					else {
						std::cout << "Ошибка при списании товара\n";
					}
				}
				else {
					std::cout << "Товара с таким именем не существует\n";
				}
			}
		}
		else {
			std::cout << "Ошибка ввода\n";
		}
	}

}


void Users() {
	
	std::string req;
	std::string login, new_login, password;

	while (true) {
		std::cout << "1. Создать аккаунт\n"
			"2. Редактировать аккаунт\n"
			"3. Удалить аккаунт\n"
			"0. Выйти\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "Введите логин аккаунта (0 - для выхода): ";
				std::getline(std::cin, login, '\n');

				if (login == "0") {
					system("cls");
					break;
				}

				std::cout << "Введите пароль от аккаунта (0 - для выхода): ";
				password = EnterPassword();

				if (password == "0") {
					break;
				}
				else if (InsertUser(login, Hash(password))) {
					system("cls");
					std::cout << "Аккаунт успешно создан\n";
					break;
				}
				else {
					std::cout << "Ошибка при создании аккаунта\n";
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "1. Редактировать логин\n"
					"2. Редктировать пароль\n"
					"3. Редактировать статус\n"
					"0. Выйти\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					while (true) {
						std::cout << "Введите текущий логин аккаунта: ";
						std::getline(std::cin, login, '\n');

						if (IsUserExists(login)) {
							std::cout << "Введите новый логин аккаунта: ";
							std::getline(std::cin, new_login, '\n');

							if (SetNewLogin(login, new_login)) {
								std::cout << "Логин успешно изменён\n";
								break;
							}
						}
						else {
							std::cout << "Пользователя с таким логином не существует\n";
						}

					}
					break;
				}
				else if (req == "2") {
					std::cout << "Введите логин пользователя которму хотите изменить пароль (0 - для выхода): ";
					std::getline(std::cin, login, '\n');

					if (password == "0") {
						break;
					}
					else if (IsUserExists(login)) {
						std::cout << "Введите новый пароль: ";
						password = EnterPassword();

						SetNewPassword(login, Hash(password));
					}
					else {
						std::cout << "Пользователя с таким логином не существует\n";
					}
				}
				else if (req == "3") {
					while (true) {
						std::cout << "Введите логин пользователя которму хотите изменить статус (0 - для выхода): ";
						std::getline(std::cin, login, '\n');

						if (IsUserExists(login)) {
							if (CheckIsAdmin(login)) {
								SetNewStatus(login, 1);
								std::cout << login << " успешно стал администратором\n";
								break;
							}
							else {
								SetNewStatus(login, 0);
								std::cout << login << " успешно стал пользователем\n";
								break;
							}
						}
						else {
							std::cout << "Пользователя с таким логином не существует\n";
						}
					}
				}
			}
		}
		else if (req == "3") {
			while (true) {
				std::cout << "Ведите логин пользователя которого хотите удалить (0 - для выхода): ";
				std::getline(std::cin, login, '\n');

				if (login == "0") {
					break;
				}
				else if (IsUserExists(login)) {
					if (DeleteUser(login)) {
						system("cls");
						std::cout << "Пользователь " + login + " успешно удалён\n";
						break;
					}
					else {
						std::cout << "Ошибка в удалении пользователя\n";
					}
				}
				else {
					std::cout << "Такого пользователя не существует\n";
				}
			}
		}
		else {
			std::cout << "Ошибка ввода\n";
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
		std::cout << "Список всего ассортимента:\n";

		std::cout << std::setw(5) << std::left << "ID" << std::setw(64) << "Название" << std::setw(5) << "Цена\n";
		for (const auto& discount : discounts) {
			std::cout << std::left << std::setw(5) << discount.id
				<< std::setw(64) << discount.type << std::setw(4)
				<< discount.discount << "\n";
		}

		std::cout << "1. Добавить скидку\n"
			"2. Удалить скидку\n"
			"0. Выйти\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "1. Добавить скидку на весь ассортимент\n"
					"2. Добавить скидку на товар\n"
					"0. Выйти\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					std::cout << "Введите скидку: ";
					std::getline(std::cin, str, '\n');
				}
				else if (req == "2") {
					while (true) {
						std::cout << "Введите название товара: ";
						std::getline(std::cin, product_name, '\n');

						if (GetProduct(product_name)) {
							std::cout << "Введите скидку: ";
							std::getline(std::cin, str, '\n');
							f_discount = std::stof(str);
						}
						else {
							std::cout << "Такого товара не существует\n";
						}
					}
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "Введите id скидки (0 - для выхода):";
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
					std::cout << "Скидки с таким id не существует\n";
				}
			}
		}
	}
}
