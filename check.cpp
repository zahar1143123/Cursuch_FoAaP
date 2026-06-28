#include <iostream>
#include <limits>
#include "check.h"
#include "Flight.h"
#include "file.h"

using namespace std;

int getIntInput() {
    string line;
    while (true) {
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, line);

        if (line.empty()) {
            cerr << "Ошибка ввода! Повторите: ";
            continue;
        }

        bool allDigits = true;
        for (char c : line) {
            if (c < '0' || c > '9') { allDigits = false; break; }
        }
        if (!allDigits) {
            cerr << "Ошибка! Ожидается целое число. Повторите: ";
            continue;
        }

        if (line.size() > 1 && line[0] == '0') {
            cerr << "Ошибка! Число не должно начинаться с нуля. Повторите: ";
            continue;
        }

        if (line.size() > 10) {
            cerr << "Слишком большое число! Повторите: ";
            continue;
        }
        return stoi(line);
    }
}

float getFloatInput() {
    string line;
    while (true) {
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, line);

        if (line.empty()) {
            cerr << "Ошибка ввода! Повторите: ";
            continue;
        }

        bool hasDot = false;
        bool valid = true;
        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c == '.') {
                if (hasDot) { valid = false; break; } 
                hasDot = true;
            } else if (c < '0' || c > '9') {
                valid = false; break;
            }
        }
        if (!valid) {
            cerr << "Ошибка! Ожидается вещественное число. Повторите: ";
            continue;
        }

        if (line == ".") {
            cerr << "Ошибка! Некорректное число. Повторите: ";
            continue;
        }

        if (line.size() > 15) {
            cerr << "Слишком большое число! Повторите: ";
            continue;
        }
        return stof(line);
    }
}

string getType() {
    int type;
    while (true) {
        cout << "1. пассажирский\n2. грузовой\n3. военный\n4. бизнес-джет\n";
        cout << "0. Выход\n";
        cout << "Введите тип: ";
        type = getIntInput();

        if (type == 0) return "";
        if (type == 1) return "пассажирский";
        if (type == 2) return "грузовой";
        if (type == 3) return "военный";
        if (type == 4) return "бизнес-джет";

        cout << "Ошибка!\n";
    }
}

void check_range(int &num, int max_range) {
    num = getIntInput();

    while (num < 0 || num > max_range) {
        cout << "Ошибка! Диапазон должен быть от 0 до " << max_range << "\n";
        cout << "Повторите ввод: ";
        num = getIntInput();
    }
}

bool askConfirm(const char* message) {
    cout << message << "\n";
    cout << "1. Да\n0. Нет\nВвод: ";
    int ans;
    check_range(ans, 1);
    return ans == 1;
}

void freeList(List& list) {
    Node* curr = list.head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

void askApplyAndSave(List& list, List& backup, const char* actionName) {
    int applyChoice;
    cout << "Применить изменения?\n";
    cout << "1. Да\n";
    cout << "2. Нет (вернуть исходный порядок)\n";
    cout << "0. Отмена\nВвод: ";
    check_range(applyChoice, 2);
    if (applyChoice == 2 || applyChoice == 0) {
        restoreList(list, backup);
        cout << actionName << " отменено. Исходный порядок восстановлен.\n";
    } else if (applyChoice == 1) {
        cout << "Изменения применены.\n";
    }

    freeList(backup);

    if (applyChoice == 1 || applyChoice == 2) {
        int saveChoice;
        cout << "1. Сохранить данные в файл\n0. Вернуться в меню\nВвод: ";
        check_range(saveChoice, 1);
        if (saveChoice == 1) save_DB(list);
        else system("pause");
    } else if (applyChoice == 0) {
        system("pause");
    }
}
