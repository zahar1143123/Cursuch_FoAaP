#include <windows.h>

#include "sort.h"
#include "algo.h"
#include "io.h"
#include "check.h"
#include <iostream>

using namespace std;

void selectionSort(Flight* arr, int n, int field, int asc) {
    for (int i = 0; i < n - 1; i++) {
        int target = i;
        for (int j = i + 1; j < n; j++) {
            bool shouldSwap = false;
            
            if (asc) { 
                if (field == 1 && arr[j].type < arr[target].type) shouldSwap = true;
                if (field == 2 && arr[j].year < arr[target].year) shouldSwap = true;
                if (field == 3 && arr[j].fuel1000 < arr[target].fuel1000) shouldSwap = true;
                if (field == 4 && arr[j].fuelDay < arr[target].fuelDay) shouldSwap = true;
                if (field == 5 && arr[j].distance < arr[target].distance) shouldSwap = true; // НОВОЕ
            } else { 
                if (field == 1 && arr[j].type > arr[target].type) shouldSwap = true;
                if (field == 2 && arr[j].year > arr[target].year) shouldSwap = true;
                if (field == 3 && arr[j].fuel1000 > arr[target].fuel1000) shouldSwap = true;
                if (field == 4 && arr[j].fuelDay > arr[target].fuelDay) shouldSwap = true;
                if (field == 5 && arr[j].distance > arr[target].distance) shouldSwap = true; // НОВОЕ
            }

            if (shouldSwap) {
                target = j;
            }
        }
        if (target != i) {
            swapFlights(arr[i], arr[target]);
        }
    }
}

void handleSort(Flight*& flights, int& n) {
    system("cls");
    if (n == 0) {
        cout << "Нет данных для сортировки.\n";
        system("pause");
        return;
    }
    
    cout << "=== СОРТИРОВКА ВЫБОРОМ ===\n";
    cout << "Выберите поле для сортировки:\n";
    cout << "1. Тип самолета\n";
    cout << "2. Год выпуска\n";
    cout << "3. Расход на 1000км\n";
    cout << "4. Расход за сутки\n";
    cout << "5. Дистанция полета\n"; // НОВОЕ
    cout << "Ввод: ";
    int field; check_range(field, 5);
    
    cout << "Направление:\n1. По возрастанию\n2. По убыванию\nВвод: ";
    int dir; check_range(dir, 2);
    
    selectionSort(flights, n, field, (dir == 1));
    
    cout << "Сортировка выполнена.\n";
    printTable(flights, n);
    system("pause");
}