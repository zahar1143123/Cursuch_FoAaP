#include <iostream>
#include <limits>
#include <iomanip>
#include "io.h"
#include "check.h"

using namespace std;

void addRecord(Flight*& arr, int& n) {
    Flight* temp = new Flight[n + 1];
    for (int i = 0; i < n; i++)
        temp[i] = arr[i];

    cout << "Ввод авиарейса" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    temp[n].type = getType();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Год выпуска: ";
        temp[n].year = getIntInput();
        if (temp[n].year >= 1903 && temp[n].year <= 2026) break;
        cout << "Некорректный ввод года выпуска самолета(1903-2026)" << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Планируемое расстояние на сутки: ";
        temp[n].distance = getFloatInput();
        if (temp[n].distance >= 100 && temp[n].distance <= 20000) break;
        cout << "Ошибка: расстояние должно быть от 100 до 20000 км\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Расход топлива на 1000 км: ";
        temp[n].fuel1000 = getFloatInput();
        if (temp[n].fuel1000 >= 500 && temp[n].fuel1000 <= 20000) break;
        cout << "Ошибка: расход должен быть от 500 до 20000 л/1000км\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    temp[n].fuelDay = temp[n].fuel1000 * temp[n].distance / 1000;
    delete[] arr;
    arr = temp;
    n++;
}

void selectionSort(Flight* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].fuelDay > arr[max].fuelDay)
                max = j;
        swap(arr[i], arr[max]);
    }
}

void printTable(Flight* arr, int n) {
    if (n == 0) {
        cout << "Нет данных\n";
        return;
    }

    selectionSort(arr, n);

    cout << setw(15) << "Тип"
         << setw(10) << "Год"
         << setw(15) << "Расход л/1000км"
         << setw(15) << "Дистанция"
         << setw(15) << "Сутки\n";

    for (int i = 0; i < n; i++) {
        cout << setw(15) << arr[i].type
             << setw(10) << arr[i].year
             << setw(15) << arr[i].fuel1000
             << setw(15) << arr[i].distance
             << setw(15) << arr[i].fuelDay << endl;
    }
}