#include "search.h"
#include "algo.h"       // Для binarySearch, inputFlightData, deleteFlightByIndex, printTable
#include "check.h"      // Для check_range и getIntInput
#include <iostream>
#include <windows.h>

using namespace std;

// --- CASE 9: БИНАРНЫЙ ПОИСК ---
void handleSearch(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) {
        cout << "Нет данных.\n";
        system("pause");
        return;
    }
    
    cout << "=== БИНАРНЫЙ ПОИСК ===\n";
    cout << "Введите тип самолета для поиска: ";
    string key;
    cin >> key;

    // Вызываем алгоритм поиска
    int foundIndex = binarySearch(flights, n, key);

    if (foundIndex == -1) {
        cout << "Запись с типом '" << key << "' не найдена.\n";
        system("pause");
        return;
    }

    // Если найдено
    cout << "\n--- ЗАПИСЬ НАЙДЕНА (Индекс: " << foundIndex << ") ---\n";
    printTable(flights, n);

    // Подменю действий
    int act;
    do {
        cout << "\n=== ДЕЙСТВИЯ С НАЙДЕННОЙ ЗАПИСЬЮ ===\n";
        cout << "1. Изменить запись\n";
        cout << "2. Удалить запись\n";
        cout << "0. Вернуться в меню\n";
        cout << "Выберите: ";
        check_range(act, 2);

        if (act == 1) {
            cout << "Введите новые данные:\n";
            inputFlightData(flights[foundIndex]);
            cout << "Запись обновлена.\n";
            act = 0; 
        }
        else if (act == 2) {
            deleteFlightByIndex(flights, n, foundIndex);
            cout << "Запись удалена.\n";
            act = 0;
        }
    } while (act != 0);
    system("pause");
}

// --- CASE 10: РЕДАКТИРОВАНИЕ ПО ИНДЕКСУ ---
void handleEditByIndex(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) {
        cout << "Нет данных.\n";
        system("pause");
        return;
    }
    
    cout << "=== РЕДАКТИРОВАНИЕ ПО ИНДЕКСУ ===\n";
    printTable(flights, n); 
    
    int idx;
    cout << "Введите индекс для редактирования (0-" << n-1 << ", -1 для выхода): ";
    cin >> idx; 
    
    if (idx == -1) return;
    
    while (idx < 0 || idx >= n) {
        cout << "Ошибка! Введите от 0 до " << n-1 << " или -1: ";
        cin >> idx;
        if (idx == -1) return;
    }

    int num;
    cout << "\nТекущая запись:\n";
    cout << "[" << idx << "] " << flights[idx].type << " | " << flights[idx].year << endl;
    cout << "0 - выход\n1 - Изменить данные\n2 - Удалить запись\n";
    check_range(num, 2);

    if (num == 1) {
        cout << "Введите новые данные:\n";
        inputFlightData(flights[idx]);
        cout << "Данные обновлены.\n";
        printTable(flights, n);
        system("pause");
    }
    else if (num == 2) {
        deleteFlightByIndex(flights, n, idx);
        cout << "Запись удалена.\n";
        printTable(flights, n);
        system("pause");
    }
}