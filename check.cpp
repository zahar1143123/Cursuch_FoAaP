#include <iostream>
#include <limits>

using namespace std;

int getIntInput() {
    int value;
    while (!(cin >> value)) {
        cerr << "Ошибка ввода! Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return value;
}

float getFloatInput() {
    float value;
    while (!(cin >> value)) {
        cerr << "Ошибка ввода! Повторите: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return value;
}

string getType() {
    int type;
    while (true) {
        cout << "1. пассажирский\n2. грузовой\n3. военный\n4. бизнес-джет\n";
        cout << "Введите тип: ";
        type = getIntInput();

        if (type == 1) return "пассажирский";
        if (type == 2) return "грузовой";
        if (type == 3) return "военный";
        if (type == 4) return "бизнес-джет";

        cout << "Ошибка!\n";
    }
}

void check_range(int &num, int max_range) {
    num = getIntInput(); // ПРИСВАИВАЕМ ЗНАЧЕНИЕ

    while (num < 0 || num > max_range) { // 0 теперь тоже разрешен, если это выход
        cout << "Ошибка! Диапазон должен быть от 0 до " << max_range << "\n";
        cout << "Повторите ввод: ";
        num = getIntInput(); // ПРИСВАИВАЕМ ЗНАЧЕНИЕ СНОВА
    }
}