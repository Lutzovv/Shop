#include "menu.hpp"

void Menu(const std::string& login) {
	
	std::string req;

	while (true) {
		system("cls");
		std::cout << "Меню:\n"
			"1. Аккаунт\n"
			"2. Каталог товаров\n"
			"3. Корзина\n"
			"4. \n"
			"0. Выйти из аккаунта\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			Account(login);
		}
		else if (req == "2") {
			ProductCatalog(login);
		}
		else if (req == "3") {
			Basket(login);
		}
		else {
			std::cout << "Ошибка ввода\n";
		}
	}
}


void Account(const std::string& login) {

	std::string req;

	while (true) {
		system("cls");
		std::cout << "Логин: " << login << "\n"
			"Баланс: " << GetBalance(login) << "\n\n\n" <<
			"1. Пополнить баланс\n" <<
			"2. Изменить пароль\n"
			"0. Выйти в меню\n>>> ";
		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			TopUpBalance(login);
		}
		else if (req == "2") {
			SetNewPassword(login);
		}
		else {
			system("cls");
			std::cout << "Ошибка ввода\n";
		}
	}
}


void ProductCatalog(const std::string& login) {
	int product_id, product_count;
	std::string str, product_name;

	while (true) {
		std::vector<Products> products = GetProductsCatalog();

		std::cout << "Каталог товаров:\n";
		for (const auto& product : products) {
			std::cout << std::left << std::setw(5) << product.id
				<< std::setw(64) << product.name
				<< std::setw(15) << product.price
				<< std::setw(5) << product.count << "\n";
		}

		std::cout << "Для покупки введите id товара (0 - для выхода): ";
		std::getline(std::cin, str, '\n');
		product_id = std::stoi(str);
		product_name = IsProductExists(product_id);

		if (str == "0") {
			break;
		}
		else if (product_name != "") {
			if (GetProductCount(product_name) > 0) {
				while (true) {
					std::cout << "Введите количество товара (0 - для выхода): ";
					std::getline(std::cin, str, '\n');
					product_count = std::stoi(str);

					if (str == "0") {
						break;
					}
					else if (GetProductCount(product_name) >= product_count) {

						InsertProductInBasket(login, product_name, product_count, (GetProductPrice(product_name) * product_count));

					}
					else {
						std::cout << "Товара на складе не хватает для покупки\n";
					}
				}
			}
			else {
				std::cout << "Товара нет на складе!\n";
			}
		}
		else {
			std::cout << "Товара с таким id не сущетсвует\n";
		}
	}
}


void Basket(const std::string& login) {
	std::string req, str;
	std::string product_name;
	int new_count, iteration{}, iteration2{};
	float sum;

	while (true) {
		std::vector<Products> products = GetBasketList(login);
		std::cout << "Корзина:\n";
		for (const auto& product : products) {
			std::cout << std::left << std::setw(5) << product.id
				<< std::setw(64) << product.name
				<< std::setw(15) << product.price
				<< std::setw(5) << product.count << "\n";
		}
		for (int i : GetAllProductsPrice(login)) {
			sum += i;
		}
		std::cout << "Итого: " << sum << "\n";

		std::cout << "1. Удалить товар\n"
			<< "2. Редактировать количество товара\n"
			<< "3. Перейти к оплате\n"
			<< "0. Выйти\n>>> ";

		std::getline(std::cin, req, '\n');

		if (req == "0") {
			break;
		}
		else if (req == "1") {
			while (true) {
				std::cout << "Введите название товара, который хотите удалить (0 - для выхода): ";
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProductFromBasket(login, product_name)) {
					if (RemoveProductFromBasket(login, product_name)) {
						std::cout << "Товар успешно удален из корзины\n";
						break;
					}
					else {
						std::cout << "Ошбика при удалении товара\n";
					}
				}
				else {
					std::cout << "Такого товара нет в корзине\n";
				}
			}
		}
		else if (req == "2") {
			while (true) {
				std::cout << "Введите название товара, количество которого хотите изменить (0 - для выхода): "; //Добавить полную очистку корзины
				std::getline(std::cin, product_name, '\n');

				if (product_name == "0") {
					break;
				}
				else if (GetProductFromBasket(login, product_name)) {
					while (true) {
						std::cout << "Введите новое количество товара: ";
						std::getline(std::cin, str, '\n');
						new_count = std::stoi(str);

						if (GetProductCountFromBasket(login, product_name) == new_count) {
							continue;
						}
						else if (GetProductCountFromBasket(login, product_name) != new_count) {
							if (GetProductCount(product_name) == 0) {
								RemoveProductFromBasket(login, product_name);
								std::cout << "На складе товар закончился\n";
							}
							else if (new_count == 0) {
								RemoveProductFromBasket(login, product_name);
							}
							else if (new_count <= GetProductCount(product_name)) {
								SetNewProductCountInBasket(login, product_name, new_count);
							}
						}
					}
				}
			}
		}
		else if (req == "3") {
			while (true) {
				std::cout << "1. Оплатить\n"
					"0. Выйти\n>>> ";
				std::getline(std::cin, req, '\n');

				if (req == "0") {
					break;
				}
				else if (req == "1") {
					std::vector<float> prices = GetAllProductsPrice(login);
					for (int i : prices) {
						sum += i;
					}
					std::vector<sDiscount> discounts = GetAllDiscounts();
					for (const auto& discount : discounts) {
						if (discount.type == "all") {
							sum = sum - ((discount.discount * prices[iteration]) / 100);
							break;
						}
						for (const auto& product : GetBasketList(login)) {
							if (discount.type == product.name) {
								prices[iteration2] -= ((discount.discount * prices[iteration2]) / 100);
							}
							iteration2++;
						}
						iteration++;
						iteration2 = 0;
					}
					for (int i : prices) {
						sum += i;
					}
					if (GetBalance(login) >= sum) {

					}
					else {
						std::cout << "Недостаточно денег на балансе\n";
						break;
					}
				}
			}
		}
		else {
			std::cout << "Ошибка ввода\n";
		}
	}
}


void TopUpBalance(const std::string& login) {

	std::string req;
	float amount;

	while (true) {
		system("cls");
		std::cout << "Сумма для пополнения (0 - для выхода): ";
		std::getline(std::cin, req, '\n');

		amount = std::stof(req);

		if (req == "0") {
			break;
		}
		else if (TopUpBalance(login, amount)) {
			break;
		}
		else {
			std::cout << "Ошибка в пополнении\n";
		}
	}
}


void SetNewPassword(const std::string& login) {

	std::string req;
	std::string password, new_password;

	while (true) {
		system("cls");
		std::cout << "Ввдите текущий пароль (0 - для выхода): ";
		password = EnterPassword();

		if (password == "0") {
			break;
		}
		else if (IsPasswordTrue(login, Hash(password))) {
			std::cout << "Введите новый пароль (0 - для выхода): ";
			new_password = EnterPassword();

			if (password == "0") {
				break;
			}
			else if (CheckPassword(new_password)) {
				if (SetNewPassword(login, Hash(new_password))) {
					std::cout << "Пароль успешно изменён\n";
					break;
				}
				else {
					std::cout << "Ошибка в изменении пароля\n";
				}
			}
			else {
				system("cls");
				std::cout << "Слишком слабый пароль!\n"
					"В пароле должно быть более 8 символов\n"
					"Должна быть хотя бы 1 буква верхнего и нижнего регистра\n"
					"Хотя бы 1 цифра и 1 спец. символ\n";
			}
		}
		else {
			system("cls");
			std::cout << "Не верный пароль\n";
		}
	}
}