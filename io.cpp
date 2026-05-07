#include "io.h"
#include "check.h"
#include "algo.h" // Для swapFlights, если нужно, или просто логика внутри
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void addRecord(Flight*& arr, int& n) {
    Flight* temp = new Flight[n + 1];
    for (int i = 0; i < n; i++)
        temp[i] = arr[i];

    cout << "Ввод авиарейса" << endl;
    temp[n].type = getType();
    while (true) {
        cout << "Год выпуска: ";
        temp[n].year = getIntInput();
        if (temp[n].year >= 1903 && temp[n].year <= 2026) break;
        cout << "Некорректный ввод года (1903-2026)" << endl;
    }
    while (true) {
        cout << "Планируемое расстояние на сутки: ";
        temp[n].distance = getFloatInput();
        if (temp[n].distance >= 100 && temp[n].distance <= 20000) break;
        cout << "Ошибка: расстояние должно быть от 100 до 20000 км\n";
    }
    while (true) {
        cout << "Расход топлива на 1000 км: ";
        temp[n].fuel1000 = getFloatInput();
        if (temp[n].fuel1000 >= 500 && temp[n].fuel1000 <= 20000) break;
        cout << "Ошибка: расход должен быть от 500 до 20000 л/1000км\n";
    }
    temp[n].fuelDay = temp[n].fuel1000 * temp[n].distance / 1000;
    
    delete[] arr;
    arr = temp;
    n++;
}

void printTable(Flight* arr, int n, int startIdx, int endIdx) {
    if (n == 0) {
        cout << "Нет данных\n";
        return;
    }

    // Если endIdx равен -1, значит вывести всё до конца
    if (endIdx == -1) endIdx = n - 1;

    // Защита от выхода за границы массива
    if (startIdx < 0) startIdx = 0;
    if (endIdx >= n) endIdx = n - 1;
    if (startIdx > endIdx) {
        cout << "Некорректный диапазон для вывода.\n";
        return;
    }

    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "| Ind | Тип          | Год | Расход(1000) | Дальность | Расход(сутки) |\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    
    // Цикл от startIdx до endIdx
    for (int i = startIdx; i <= endIdx; i++) {
        cout << "| " << setw(3) << i << " | " 
             << setw(12) << arr[i].type << " | " 
             << setw(3) << arr[i].year << " | " 
             << setw(12) << arr[i].fuel1000 << " | " 
             << setw(9) << arr[i].distance << " | " 
             << setw(13) << arr[i].fuelDay << " |\n";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
}

void fillTestData(Flight*& arr, int& n) {
    int addCount = 20;
    
    // Создаем новый массив большего размера
    Flight* newArr = new Flight[n + addCount];

    // Копируем старые данные (если были)
    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }

    // --- ЖЕСТКО ЗАДАННЫЕ ДАННЫЕ (20 ШТУК) ---
    
    // 1
    newArr[n].type = "пассажирский";
    newArr[n].year = 2010;
    newArr[n].fuel1000 = 2500;
    newArr[n].distance = 5000;
    newArr[n].fuelDay = 12500;

    // 2
    newArr[n+1].type = "грузовой";
    newArr[n+1].year = 1995;
    newArr[n+1].fuel1000 = 6000;
    newArr[n+1].distance = 2500;
    newArr[n+1].fuelDay = 15000;

    // 3
    newArr[n+2].type = "военный";
    newArr[n+2].year = 2018;
    newArr[n+2].fuel1000 = 5000;
    newArr[n+2].distance = 3000;
    newArr[n+2].fuelDay = 15000;

    // 4
    newArr[n+3].type = "бизнес-джет";
    newArr[n+3].year = 2022;
    newArr[n+3].fuel1000 = 1500;
    newArr[n+3].distance = 4500;
    newArr[n+3].fuelDay = 6750;

    // 5
    newArr[n+4].type = "пассажирский";
    newArr[n+4].year = 2015;
    newArr[n+4].fuel1000 = 2800;
    newArr[n+4].distance = 8000;
    newArr[n+4].fuelDay = 22400;

    // 6
    newArr[n+5].type = "грузовой";
    newArr[n+5].year = 2000;
    newArr[n+5].fuel1000 = 5500;
    newArr[n+5].distance = 2000;
    newArr[n+5].fuelDay = 11000;

    // 7
    newArr[n+6].type = "военный";
    newArr[n+6].year = 2005;
    newArr[n+6].fuel1000 = 7000;
    newArr[n+6].distance = 4000;
    newArr[n+6].fuelDay = 28000;

    // 8
    newArr[n+7].type = "бизнес-джет";
    newArr[n+7].year = 2019;
    newArr[n+7].fuel1000 = 1400;
    newArr[n+7].distance = 5000;
    newArr[n+7].fuelDay = 7000;

    // 9
    newArr[n+8].type = "пассажирский";
    newArr[n+8].year = 2008;
    newArr[n+8].fuel1000 = 2300;
    newArr[n+8].distance = 6000;
    newArr[n+8].fuelDay = 13800;

    // 10
    newArr[n+9].type = "грузовой";
    newArr[n+9].year = 2012;
    newArr[n+9].fuel1000 = 5800;
    newArr[n+9].distance = 3500;
    newArr[n+9].fuelDay = 20300;

    // 11
    newArr[n+10].type = "военный";
    newArr[n+10].year = 2010; // Повтор года для проверки фильтрации
    newArr[n+10].fuel1000 = 7500;
    newArr[n+10].distance = 2500;
    newArr[n+10].fuelDay = 18750;

    // 12
    newArr[n+11].type = "бизнес-джет";
    newArr[n+11].year = 2021;
    newArr[n+11].fuel1000 = 1300;
    newArr[n+11].distance = 5500;
    newArr[n+11].fuelDay = 7150;

    // 13
    newArr[n+12].type = "пассажирский";
    newArr[n+12].year = 2023;
    newArr[n+12].fuel1000 = 2600;
    newArr[n+12].distance = 9000;
    newArr[n+12].fuelDay = 23400;

    // 14
    newArr[n+13].type = "грузовой";
    newArr[n+13].year = 1998;
    newArr[n+13].fuel1000 = 5200;
    newArr[n+13].distance = 2200;
    newArr[n+13].fuelDay = 11440;

    // 15
    newArr[n+14].type = "военный";
    newArr[n+14].year = 2016;
    newArr[n+14].fuel1000 = 6800;
    newArr[n+14].distance = 3800;
    newArr[n+14].fuelDay = 25840;

    // 16
    newArr[n+15].type = "бизнес-джет";
    newArr[n+15].year = 2017;
    newArr[n+15].fuel1000 = 1600;
    newArr[n+15].distance = 4800;
    newArr[n+15].fuelDay = 7680;

    // 17
    newArr[n+16].type = "пассажирский";
    newArr[n+16].year = 2015; // Повтор года
    newArr[n+16].fuel1000 = 2400;
    newArr[n+16].distance = 7000;
    newArr[n+16].fuelDay = 16800;

    // 18
    newArr[n+17].type = "грузовой";
    newArr[n+17].year = 2010; // Повтор года
    newArr[n+17].fuel1000 = 6100;
    newArr[n+17].distance = 2800;
    newArr[n+17].fuelDay = 17080;

    // 19
    newArr[n+18].type = "военный";
    newArr[n+18].year = 2020;
    newArr[n+18].fuel1000 = 8200;
    newArr[n+18].distance = 3200;
    newArr[n+18].fuelDay = 26240;

    // 20
    newArr[n+19].type = "бизнес-джет";
    newArr[n+19].year = 2014;
    newArr[n+19].fuel1000 = 1700;
    newArr[n+19].distance = 6000;
    newArr[n+19].fuelDay = 10200;

    // Удаляем старый массив и обновляем указатель
    delete[] arr;
    arr = newArr;
    n += addCount;
    
    cout << "Успешно добавлено " << addCount << " готовых записей.\n";
}