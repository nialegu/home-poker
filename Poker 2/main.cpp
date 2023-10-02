#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <string>

using namespace std;
int hello();
void one_line();
void double_line();
void space_line();

enum ColorConsole {
	white = 15,
	red = 4
};

class chips {
private:
	int name;
	float value;
public:
	chips() : name(0), value(0){}
	chips(int n, float v, int c) : name (n), value (v){}

	void get_chip() {
		cout << "Введите номер фишки: "; cin >> name;
		if ( name != 1 && name != 5 && name != 10 && name != 25 && name != 50 ) {
			cout << "Такого номера фишки нет! Попробуй еще: ";
			get_chip();
		}
		else cout << "Введите денежный эквивалент: "; cin >> value;
	}
	void get_chip(int n, float v) {
		name = n;
		value = v;
	}
	void put_chip() const {
		cout << "Фишка " << name << ": " << value << endl;
	}
	float get_value() {
		return value;
	}
};

class player {
private:
	string name;
	chips ch1, ch5, ch10, ch25, ch50;
	float personal_bank;
	int countchips;
public:
	void get_info(float value) {
		space_line();
		cout << "Введите информацию об игроке.\nИмя: "; cin.ignore(); cin >> name;
		cout << "Количество фишек 1: "; cin >> countchips; ch1.get_chip(1, 20 * value * countchips);
		cout << "Количество фишек 5: "; cin >> countchips; ch5.get_chip(5, value * countchips);
		cout << "Количество фишек 10: "; cin >> countchips; ch10.get_chip(10, 2 * value * countchips);
		cout << "Количество фишек 25: "; cin >> countchips; ch25.get_chip(25, 5 * value * countchips);
		cout << "Количество фишек 50: "; cin >> countchips; ch50.get_chip(50, 10 * value * countchips);
	}

	float pers_bank() {
		float pb;
		pb = ch1.get_value() + ch5.get_value() + ch10.get_value() + ch25.get_value() + ch50.get_value();
		return pb;
	}

	void put_info() {
		cout << endl; double_line();
		cout << name << endl;
		//ch1.put_chip();
		//ch5.put_chip();
		//ch10.put_chip();
		//ch25.put_chip();
		//ch50.put_chip();
		personal_bank = pers_bank();
		cout << "Общая сумма: " << personal_bank << endl;
		double_line(); cout << endl;
	}

	void name_output() {
		cout << name;
	}

	bool operator> (player p1) {
		bool check;
		check = (pers_bank() > p1.pers_bank()) ? 1 : 0;
		return check;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	system("color 2F"); //цвет
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получить консоль
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	//GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo); // Получить текущий шрифт
	//wcscpy(fontInfo.FaceName, L"Lucida Console"); // меняем какие то параметры
	fontInfo.dwFontSize.Y = 24;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	
	const int MAX = 10;
	chips ch5[4];
	int count_of_players, cchforonepl;
	float value = 0, due=0;

	cout << "Приветствуем! ";
	count_of_players = hello();
	cout << "Введите сумму входа в игру: "; cin >> due;
	cchforonepl = (25 - 25 % count_of_players) / count_of_players;
	value = due / (cchforonepl * 38);

	/*switch (count_of_players) {
	case 6: value = 0.3; break;
	case 7: value = 0.4; break;
	case 8: value = 0.4; break;
	}*/

	player pl[10]; char ch = 'a';
	for (int i = 0; i < count_of_players; i++) {
		cout << "Хотите ввести данные об игроке? (д/н): "; ch = _getche(); cout << endl;
		if (ch == 'н') {
			i--; cout << endl;
			cout << "Осталось " << count_of_players - (i + 1) << " игроков" << endl;
		}
		else if (ch == 'д') {
			pl[i].get_info(value);
			pl[i].put_info();
			cout << "Осталось " << count_of_players - (i + 1) << " игроков" << endl;
		}
		else i--;
	}
	
	player max;
	for (int i = 1; i < count_of_players; i++) {
		max = (pl[i] > pl[i - 1]) ? pl[i] : pl[i - 1];
	}
	cout << "Победитель "; max.name_output(); cout << endl;
	return 0;
}

int hello() {
	cout << "Введите количество игроков: ";
	int c; cin >> c;
	if (c != 4 && c != 5 && c != 6 && c != 7 && c != 8 && c != 9 && c != 10) {
		cout << "Некорректно введено количество. Попробуйте снова.\n";
		hello();
	}
	return c;
}

void one_line() {
	for (int i = 0; i < 45; i++) {
		cout << "-";
	} cout << endl;
}

void double_line() {
	for (int i = 0; i < 45; i++) {
		cout << "=";
	} cout << endl;
}

void space_line() {
	for (int i = 0; i < 10; i++) {
		cout << "-    ";
	} cout << endl;
}