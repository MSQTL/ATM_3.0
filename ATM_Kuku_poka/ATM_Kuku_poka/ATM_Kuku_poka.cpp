#include <iostream>
#include <list>
#include <Windows.h>
#include <Wincon.h>
using namespace std;

//Создание класса Credit
class Credit {
	string dateOfCredit = "", bankDetails;
	float summa;
	int srok;

public:
	
	Credit(string bd, float sum, int s) {
		bankDetails = bd;
		summa = sum;
		srok = s;
		SYSTEMTIME time;
		GetSystemTime(&time);
		dateOfCredit += time.wDay + time.wMonth + time.wYear;
	}

	float getSumma() {
		return summa;
	}

	int getSrok() {
		return srok;
	}
};

//Создание списка объектов класса Credit
list <Credit> creditniySpisok;
int showMethods();
bool nominal(int money);

//Создание класса Пользователей банка
class Individual {

public:
	string name, bankDetails;
	int pinCode;
	float balance, money;

	
	Individual(string n, string bd, int pc, float b)
	{
		name = n; bankDetails = bd; pinCode = pc; balance = b;
	}

	void Money(int operation) {
		
		bool flag = true;
		int status;

		while (flag) {
			switch (operation)
			{
			case 1:
				showBalance();
				flag = false;
				break;
			case 2:
				cout << "Введите сумму, которую хотите снять: ";
				cin >> money;
				if (nominal(money)) {
					withDraw(money);
					flag = false;
				}
				break;
			case 3:
				cout << "Введите сумму, которую хотите внести: ";
				cin >> money;
				top(money);
				flag = false;
				break;
			case 4:
				cout << "Введите сумму займа: ";
				cin >> money;
				cout << "На какой срок (месяцев): ";
				int srok;
				cin >> srok;
				top(money);
				creditniySpisok.push_back(Credit(bankDetails, money, srok));
				flag = false;
				cout << "Поздравляем, " << name << ", Вы взяли кредит на сумму " 
					<< money << " на срок " << srok << " месяцев";
				break;
			default:
				cout << "Выбрана неверная операция!\n";
			}
		}

		cout << "\nХотите продолжить операции?\n1 - да, 2 - нет\n";
		cin >> status;
		if (status == 1) Money(showMethods());
	}

	void showBalance() {
		cout << "\n" << "Ваш баланс: " << balance << "\n";
	}

	void withDraw(float money) {
		balance -= money;
		cout << "Ваш баланс после снятия наличных: " << balance << "\n";
	}

	void top(float money) {
		balance += money;
		cout << "Ваш баланс после пополнения счета: " << balance << "\n";
	}

	bool checkBd(string bd) {
		return (bankDetails == bd) ? true : false;
	}

	bool checkPc(int pc) {
		return (pinCode == pc) ? true : false;
	}

	string getName() {
		return name;
	}

	string getBankDetails() {
		return bankDetails;
	}
};

//Создание списка объектов класса Пользователей банка
list <Individual> spisok;
//Итератор для поиска нужного объекта класса Пользователей банка
list <Individual>::iterator it;
//Проверка на купюры
bool nominal(int money) {
	if (!(money % 50 == 0)) {
		cout << "Такую сумму вывести невозможно!\n";
		return false;
	}
	else {
		return true;
	}
}

//Показ возможных операция для пользователя
int showMethods() {

	cout << "\n1 - Показать баланс\n2 - Снять наличные\n3 - Пополнить счет\n4 - Хотите взять займ?:)\n";
	int operation;
	cin >> operation;
	return operation;
}

//Авторизация пользователя (проверка совпадения банковского счета и ПИН-кода)
bool authorization() {

	bool status = true;
	cout << "Введите Ваш банковский счет: ";
	string bd;
	cin >> bd;

	for (it = spisok.begin(); it != spisok.end(); it++)
	{
		if (it -> checkBd(bd)) {
			while (true) {
				cout << "Введите Ваш ПИН-код: ";
				int pc;
				cin >> pc;
				if (it->checkPc(pc)) {
					cout << it->getName() << ", Вы вошли в личный кабинет!\n";
					return true;
				}
				else {
					cout << "Неверный ПИН-код! Повторите попытку\n";

				}
			}
		}
	}
	cout << "Неверный банковский счет!\n";
	return false;
}

//Регистрация нового пользователя
void registration() {

	string name, bankDetails;
	int pinCode;

	cout << "Пройдите регистрацию!\n";

	cout << "Введите Ваше имя: ";
	cin >> name;

	cout << "Введите Ваш банковский счет: ";
	cin >> bankDetails;
	
	for (it = spisok.begin(); it != spisok.end(); it++) {

		if (it->checkBd(bankDetails)) {
			cout << "Данный банковский счет уже зарегестрирован!\n";
			return;
		}
	}

	cout << "Введите Ваш ПИН-код: ";
	cin >> pinCode;

	spisok.push_back(Individual(name, bankDetails, pinCode, 0));

	cout << "Регистрация прошла успешно!\n\n";
}

int main()
{
	setlocale(LC_ALL, "RU");
	SetConsoleTitleA("ATM");

	bool status = true;
		
	spisok.push_back(Individual("Софья", "1", 1, 100000)); //Добавление нового пользователя
	spisok.push_back(Individual("Сергей", "2", 2, 1000)); //Добавление нового пользователя

	while (status) {

		if (authorization()) {
			it->Money(showMethods());
			status = false;
		}
		else {
			registration();
		}
	}
}
