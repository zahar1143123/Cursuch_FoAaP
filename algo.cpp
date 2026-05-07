#include "algo.h"
#include "check.h"
#include <iostream>

using namespace std;

void swapFlights(Flight& a, Flight& b) {
    Flight temp = a;
    a = b;
    b = temp;
}

void deleteFlightByIndex(Flight*& arr, int& n, int index) {
    if (n == 0 || index < 0 || index >= n) return;

    Flight* newArr = new Flight[n - 1];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i != index) {
            newArr[j++] = arr[i];
        }
    }
    delete[] arr;
    arr = newArr;
    n--;
}

void editRecord(Flight& f) {
    cout << "--- Редактирование записи ---\n";
    cout << "Текущий тип: " << f.type << "\n";
    f.type = getType();
    
    while (true) {
        cout << "Новый год выпуска: ";
        f.year = getIntInput();
        if (f.year >= 1903 && f.year <= 2026) break;
        cout << "Ошибка! (1903-2026)\n";
    }
    
    while (true) {
        cout << "Новая дистанция: ";
        f.distance = getFloatInput();
        if (f.distance >= 100 && f.distance <= 20000) break;
        cout << "Ошибка! (100-20000)\n";
    }
    
    while (true) {
        cout << "Новый расход на 1000км: ";
        f.fuel1000 = getFloatInput();
        if (f.fuel1000 >= 500 && f.fuel1000 <= 20000) break;
        cout << "Ошибка! (500-20000)\n";
    }
    
    // Пересчет суточного расхода
    f.fuelDay = f.fuel1000 * f.distance / 1000;
    cout << "Запись обновлена. Новый суточный расход: " << f.fuelDay << endl;
}

int binarySearch(Flight* arr, int n, string key) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].type == key) {
            return mid;
        }
        if (arr[mid].type < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}