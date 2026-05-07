#include <windows.h>

#include "search.h"
#include "sort.h"        // <--- ВАЖНО: Подключаем, чтобы видеть selectionSort
#include "algo.h"
#include "io.h"
#include "check.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ==========================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ (ОБЯЗАТЕЛЬНО ВВЕРХУ)
// ==========================================

// Бинарный поиск для строк (Тип)
int binarySearchString(Flight* arr, int n, string key) {
    int left = 0; int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].type == key) return mid;
        if (arr[mid].type < key) left = mid + 1; else right = mid - 1;
    }
    return -1;
}

// Левая граница для строк (для фильтрации)
int binarySearchLeftString(Flight* arr, int n, string key) {
    int left = 0; int right = n - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].type == key) { result = mid; right = mid - 1; }
        else if (arr[mid].type < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

// Правая граница для строк
int binarySearchRightString(Flight* arr, int n, string key) {
    int left = 0; int right = n - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].type == key) { result = mid; left = mid + 1; }
        else if (arr[mid].type < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

// Аналогично для INT (Год, Расход, Дистанция)
int binarySearchInt(Flight* arr, int n, int key, int field) {
    int left = 0; int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = (field == 2) ? arr[mid].year : (field == 5 ? (int)arr[mid].distance : (int)arr[mid].fuel1000);
        if (val == key) return mid;
        if (val < key) left = mid + 1; else right = mid - 1;
    }
    return -1;
}

int binarySearchLeftInt(Flight* arr, int n, int key, int field) {
    int left = 0; int right = n - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = (field == 2) ? arr[mid].year : (field == 5 ? (int)arr[mid].distance : (int)arr[mid].fuel1000);
        if (val == key) { result = mid; right = mid - 1; }
        else if (val < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

int binarySearchRightInt(Flight* arr, int n, int key, int field) {
    int left = 0; int right = n - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = (field == 2) ? arr[mid].year : (field == 5 ? (int)arr[mid].distance : (int)arr[mid].fuel1000);
        if (val == key) { result = mid; left = mid + 1; }
        else if (val < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

// ==========================================
// ОСНОВНЫЕ ОБРАБОТЧИКИ
// ==========================================

// --- CASE 9: БИНАРНЫЙ ПОИСК (ОДНА ЗАПИСЬ) ---
void handleSearch(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    
    cout << "=== БИНАРНЫЙ ПОИСК ===\n";
    cout << "1. Поиск по Типу (строка)\n";
    cout << "2. Поиск по Году (число)\n";
    cout << "3. Поиск по Расходу 1000 (число)\n";
    cout << "4. Поиск по Дистанции (число)\n";
    cout << "Ввод: ";
    int field; check_range(field, 4);

    // Сортируем перед поиском
    selectionSort(flights, n, field, true);

    int foundIndex = -1;
    if (field == 1) {
        // ИСПОЛЬЗУЕМ getType() ДЛЯ ВВОДА
        string key = getType(); 
        foundIndex = binarySearchString(flights, n, key);
    } else {
        int key; 
        if (field == 2) cout << "Введите Год: ";
        if (field == 3) cout << "Введите Расход 1000: ";
        if (field == 4) cout << "Введите Дистанцию: ";
        cin >> key;
        foundIndex = binarySearchInt(flights, n, key, field);
    }

    if (foundIndex == -1) cout << "Запись не найдена.\n";
    else {
        cout << "\n--- ЗАПИСЬ НАЙДЕНА (Индекс: " << foundIndex << ") ---\n";
        printTable(flights, n);
        
        int act;
        cout << "1. Изменить\n2. Удалить\n0. Выход: \nВвод: ";
        check_range(act, 2);
        if (act == 1) { editRecord(flights[foundIndex]); cout << "Запись обновлена.\n"; }
        else if (act == 2) { deleteFlightByIndex(flights, n, foundIndex); cout << "Запись удалена.\n"; }
    }
    system("pause");
}

// --- CASE 11: ФИЛЬТРАЦИЯ ---
void handleFilter(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    
    cout << "=== ФИЛЬТРАЦИЯ (БИНАРНЫЙ ПОИСК) ===\n";
    cout << "Выберите поле для фильтрации:\n";
    cout << "1. Тип самолета\n";
    cout << "2. Год выпуска\n";
    cout << "3. Расход на 1000км\n";
    cout << "4. Дистанция\n";
    cout << "Ввод: ";
    int field; check_range(field, 4);

    selectionSort(flights, n, field, true);

    int left = -1, right = -1;

    if (field == 1) {
        // ИСПОЛЬЗУЕМ getType() ДЛЯ ВВОДА
        string key = getType();
        left = binarySearchLeftString(flights, n, key);
        right = binarySearchRightString(flights, n, key);
    } else {
        int key;
        if (field == 2) cout << "Введите Год: ";
        if (field == 3) cout << "Введите Расход 1000: ";
        if (field == 4) cout << "Введите Дистанцию: ";
        cin >> key;
        left = binarySearchLeftInt(flights, n, key, field);
        right = binarySearchRightInt(flights, n, key, field);
    }

    if (left == -1) cout << "Ничего не найдено.\n";
    else {
        cout << "\n--- РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ (Индексы " << left << " - " << right << ") ---\n";
        printTable(flights, n, left, right);
        cout << "Всего найдено: " << (right - left + 1) << " записей.\n";
    }
    system("pause");
}

// --- CASE 10: РЕДАКТИРОВАНИЕ ---
void handleEditByIndex(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    printTable(flights, n);
    int idx;
    cout << "Введите индекс (0-" << n-1 << ", -1 выход): "; cin >> idx; 
    if (idx == -1) return;
    while (idx < 0 || idx >= n) { cout << "Ошибка индекса: "; cin >> idx; if (idx == -1) return; }

    int num;
    cout << "1. Изменить\n2. Удалить\n0. Выход:\nВвод:"; 
    check_range(num, 2);

    if (num == 1) {
        editRecord(flights[idx]);
        cout << "Данные обновлены.\n";
        printTable(flights, n); system("pause");
    }
    else if (num == 2) {
        deleteFlightByIndex(flights, n, idx);
        cout << "Запись удалена.\n";
        printTable(flights, n); system("pause");
    }
}