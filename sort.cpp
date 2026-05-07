#include "sort.h"
#include "algo.h"       // Для selectionSort и printTable
#include "check.h"      // Для system("pause")
#include <iostream>
#include <windows.h>

using namespace std;

void handleSort(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) {
        cout << "Нет данных для сортировки.\n";
        system("pause");
        return;
    }
    
    cout << "=== СОРТИРОВКА ВЫБОРОМ (по типу самолета) ===\n";
    
    // Вызываем алгоритм из algo.cpp
    selectionSort(flights, n);
    
    cout << "Массив отсортирован.\n";
    
    // Выводим таблицу из algo.cpp
    printTable(flights, n);
    system("pause");
}