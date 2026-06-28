#include <windows.h>

#include "search.h"
#include "sort.h"
#include "algo.h"
#include "io.h"
#include "file.h"
#include "check.h"
#include <iostream>
#include <iomanip>

using namespace std;

int binarySearchLeftString(List& list, string key) {
    int left = 0; int right = list.size - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        if (midNode->data.type == key) { result = mid; right = mid - 1; }
        else if (midNode->data.type < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

int binarySearchRightString(List& list, string key) {
    int left = 0; int right = list.size - 1; int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        if (midNode->data.type == key) { result = mid; left = mid + 1; }
        else if (midNode->data.type < key) left = mid + 1; else right = mid - 1;
    }
    return result;
}

int lowerBoundIntField(List& list, int value, int field) {
    int left = 0, right = list.size - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        int val = (field == 2) ? midNode->data.year : (field == 5 ? (int)midNode->data.distance : (int)midNode->data.fuel1000);
        if (val >= value) { result = mid; right = mid - 1; }
        else left = mid + 1;
    }
    return result;
}

int upperBoundIntField(List& list, int value, int field) {
    int left = 0, right = list.size - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        int val = (field == 2) ? midNode->data.year : (field == 5 ? (int)midNode->data.distance : (int)midNode->data.fuel1000);
        if (val <= value) { result = mid; left = mid + 1; }
        else right = mid - 1;
    }
    return result;
}

int lowerBoundFloatField(List& list, float value, int field) {
    int left = 0, right = list.size - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        float val;
        if (field == 3) val = midNode->data.fuel1000;
        else if (field == 4) val = midNode->data.fuelDay;
        else val = midNode->data.distance;
        if (val >= value) { result = mid; right = mid - 1; }
        else left = mid + 1;
    }
    return result;
}

int upperBoundFloatField(List& list, float value, int field) {
    int left = 0, right = list.size - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(list, mid);
        float val;
        if (field == 3) val = midNode->data.fuel1000;
        else if (field == 4) val = midNode->data.fuelDay;
        else val = midNode->data.distance;
        if (val <= value) { result = mid; left = mid + 1; }
        else right = mid - 1;
    }
    return result;
}

void handleSearch(List& list) {
    system("cls");
    if (list.size == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    
    cout << "=== БИНАРНЫЙ ПОИСК ===\n";
    cout << "1. Поиск по Типу (строка)\n";
    cout << "2. Поиск по Году (число)\n";
    cout << "3. Поиск по Расходу 1000 (число)\n";
    cout << "4. Поиск по Расходу за сутки (число)\n";
    cout << "5. Поиск по Дистанции (число)\n";
    cout << "0. Выход\n";
    cout << "Ввод: ";
    int field; check_range(field, 5);
    if (field == 0) return;

    List backup;
    copyList(backup, list);

    selectionSort(list, field, true);

    int left = -1, right = -1;
    if (field == 1) {
        string key = getType(); 
        left = binarySearchLeftString(list, key);
        right = binarySearchRightString(list, key);
    } else if (field == 2) {
        int key;
        cout << "Введите Год: ";
        key = getIntInput();
        left = lowerBoundIntField(list, key, field);
        right = upperBoundIntField(list, key, field);
    } else {
        float key;
        if (field == 3) cout << "Введите Расход 1000: ";
        if (field == 4) cout << "Введите Расход за сутки: ";
        if (field == 5) cout << "Введите Дистанцию: ";
        key = getFloatInput();
        left = lowerBoundFloatField(list, key, field);
        right = upperBoundFloatField(list, key, field);
    }

    if (left == -1 || right == -1 || left > right) {
        cout << "Записи не найдены.\n";
        restoreList(list, backup);
        freeList(backup);
        system("pause");
    } else {
        int count = right - left + 1;
        cout << "\n--- НАЙДЕНО: " << count << " ЗАПИСЕЙ ---\n";
        printTable(list, left, right);

        int pickIdx;
        cout << "Введите индекс записи (1-" << count << ", 0 выход): ";
        pickIdx = getIntInput();
        if (pickIdx == 0) { restoreList(list, backup); freeList(backup); system("pause"); return; }
        while (pickIdx < 1 || pickIdx > count) {
            cout << "Ошибка! Индекс от 1 до " << count << " (0 выход): ";
            pickIdx = getIntInput();
            if (pickIdx == 0) { restoreList(list, backup); freeList(backup); system("pause"); return; }
        }

        int realIdx = left + pickIdx - 1;

        int act;
        cout << "1. Изменить\n2. Удалить\n0. Выход: \nВвод: ";
        check_range(act, 2);
        if (act == 1) { Node* node = getNodeAt(list, realIdx); editRecord(node->data); cout << "Запись обновлена.\n"; }
        else if (act == 2) {
            if (askConfirm("Удалить выбранную запись?")) {
                deleteFlightByIndex(list, realIdx);
                cout << "Запись удалена.\n";
            } else {
                cout << "Удаление отменено.\n";
            }
        }

        askApplyAndSave(list, backup, "Поиск");
    }
}

void handleFilter(List& list) {
    system("cls");
    if (list.size == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    
    cout << "=== ФИЛЬТРАЦИЯ (БИНАРНЫЙ ПОИСК) ===\n";
    cout << "Выберите поле для фильтрации:\n";
    cout << "1. Тип самолета\n";
    cout << "2. Год выпуска (диапазон)\n";
    cout << "3. Расход на 1000км (диапазон)\n";
    cout << "4. Расход за сутки (диапазон)\n";
    cout << "5. Дистанция (диапазон)\n";
    cout << "0. Выход\n";
    cout << "Ввод: ";
    int field; check_range(field, 5);
    if (field == 0) return;

    int left = -1, right = -1;
    int sortField = field;

    List backup;
    copyList(backup, list);

    if (field == 1) {
        string key = getType();
        selectionSort(list, field, true);
        left = binarySearchLeftString(list, key);
        right = binarySearchRightString(list, key);
    } else if (field == 2) {
        cout << "Год выпуска ОТ: ";
        int from = getIntInput();
        cout << "Год выпуска ДО: ";
        int to = getIntInput();
        if (from > to) { int temp = from; from = to; to = temp; }
        sortField = 2;
        selectionSort(list, sortField, true);
        left = lowerBoundIntField(list, from, sortField);
        right = upperBoundIntField(list, to, sortField);
    } else if (field == 3) {
        cout << "Расход на 1000км ОТ: ";
        float from = getFloatInput();
        cout << "Расход на 1000км ДО: ";
        float to = getFloatInput();
        if (from > to) { float temp = from; from = to; to = temp; }
        sortField = 3;
        selectionSort(list, sortField, true);
        left = lowerBoundFloatField(list, from, sortField);
        right = upperBoundFloatField(list, to, sortField);
    } else if (field == 4) {
        cout << "Расход за сутки ОТ: ";
        float from = getFloatInput();
        cout << "Расход за сутки ДО: ";
        float to = getFloatInput();
        if (from > to) { float temp = from; from = to; to = temp; }
        sortField = 4;
        selectionSort(list, sortField, true);
        left = lowerBoundFloatField(list, from, sortField);
        right = upperBoundFloatField(list, to, sortField);
    } else if (field == 5) {
        cout << "Дистанция ОТ: ";
        float from = getFloatInput();
        cout << "Дистанция ДО: ";
        float to = getFloatInput();
        if (from > to) { float temp = from; from = to; to = temp; }
        sortField = 5;
        selectionSort(list, sortField, true);
        left = lowerBoundFloatField(list, from, sortField);
        right = upperBoundFloatField(list, to, sortField);
    }

    if (left == -1 || right == -1 || left > right) {
        cout << "Ничего не найдено.\n";
        restoreList(list, backup);
        system("pause");
    } else {
        int backupSize = backup.size;
        for (int i = list.size - 1; i > right; i--) {
            deleteFlightByIndex(list, i);
        }
        for (int i = left - 1; i >= 0; i--) {
            deleteFlightByIndex(list, i);
        }

        cout << "\n--- РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ ---\n";
        printTable(list);
        cout << "Найдено: " << list.size << " из " << backupSize << " записей.\n";

        askApplyAndSave(list, backup, "Фильтрация");
    }
}

void handleEditByIndex(List& list) {
    system("cls");
    if (list.size == 0) { cout << "Нет данных.\n"; system("pause"); return; }
    printTable(list);
    int idx;
    cout << "Введите индекс (1-" << list.size << ", 0 выход): "; idx = getIntInput(); 
    if (idx == 0) return;
    while (idx < 1 || idx > list.size) { cout << "Ошибка индекса: "; idx = getIntInput(); if (idx == 0) return; }

    int num;
    cout << "1. Изменить\n2. Удалить\n0. Выход:\nВвод:"; 
    check_range(num, 2);

    if (num == 1) {
        Node* node = getNodeAt(list, idx - 1);
        editRecord(node->data);
        cout << "Данные обновлены.\n";
        printTable(list); system("pause");
    }
    else if (num == 2) {
        if (askConfirm("Удалить выбранную запись?")) {
            deleteFlightByIndex(list, idx - 1);
            cout << "Запись удалена.\n";
        } else {
            cout << "Удаление отменено.\n";
        }
        printTable(list); system("pause");
    }
}
