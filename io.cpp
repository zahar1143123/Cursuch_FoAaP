#include "io.h"
#include "check.h"
#include "algo.h"
#include "file.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

bool addRecord(List& list) {
    Flight f;

    cout << "=== ВВОД АВИАРЕЙСА ===\n";
    f.type = getType();
    if (f.type == "") return false;

    while (true) {
        cout << "Год выпуска (0 - для выхода): ";
        f.year = getIntInput();
        if (f.year == 0) return false;
        if (f.year >= 1903 && f.year <= 2026) break;
        cout << "Некорректный ввод года (1903-2026) \n";
    }
    while (true) {
        cout << "Планируемое расстояние на сутки (0 - для выхода): ";
        f.distance = getFloatInput();
        if (f.distance == 0) return false;
        if (f.distance >= 100 && f.distance <= 20000) break;
        cout << "Ошибка: расстояние должно быть от 100 до 20000 км\n";
    }
    while (true) {
        cout << "Расход топлива на 1000 км (0 - для выхода): ";
        f.fuel1000 = getFloatInput();
        if (f.fuel1000 == 0) return false;
        if (f.fuel1000 >= 500 && f.fuel1000 <= 20000) break;
        cout << "Ошибка: расход должен быть от 500 до 20000 л/1000км\n";
    }
    f.fuelDay = f.fuel1000 * f.distance / 1000;

    pushBack(list, f);
    return true;
}

void printTable(List& list, int startIdx, int endIdx) {
    if (list.size == 0) {
        cout << "Нет данных\n";
        return;
    }

    if (endIdx == -1) endIdx = list.size - 1;

    if (startIdx < 0) startIdx = 0;
    if (endIdx >= list.size) endIdx = list.size - 1;
    if (startIdx > endIdx) {
        cout << "Некорректный диапазон для вывода.\n";
        return;
    }

    cout << "+-----+--------------+------+--------------+-----------+---------------+\n";
    cout << "| №   | Тип          | Год  | Расход(1000) | Дальность | Расход(сутки) |\n";
    cout << "+-----+--------------+------+--------------+-----------+---------------+\n";
    
    Node* curr = getNodeAt(list, startIdx);
    for (int i = startIdx; i <= endIdx; i++) {
        cout << "| " << setw(3) << (i - startIdx + 1) << " | " 
             << setw(12) << curr->data.type << " | " 
             << setw(3) << curr->data.year << " | " 
             << setw(12) << curr->data.fuel1000 << " | " 
             << setw(9) << curr->data.distance << " | " 
             << setw(13) << curr->data.fuelDay << " |\n";
             curr = curr->next;
            }
    cout << "+-----+--------------+------+--------------+-----------+---------------+\n";
        }

void fillTestData(List& list) {
    ifstream testFile(TEST_DATA_FILE);
    if (!testFile) {
        cerr << "Ошибка: файл " << TEST_DATA_FILE << " не найден!\n";
        cerr << "Убедитесь, что файл находится в той же папке, что и программа.\n";
        return;
    }

    int prevSize = list.size;
    load_txt(TEST_DATA_FILE, list);
    int added = list.size - prevSize;

    if (added > 0)
        cout << "Успешно загружено " << added << " записей из файла " << TEST_DATA_FILE << ".\n";
    else
        cout << "Ошибка: не удалось загрузить данные.\n";
}
