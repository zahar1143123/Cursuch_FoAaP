#include "algo.h"
#include "check.h"
#include <iostream>

using namespace std;

void swapFlights(Flight& a, Flight& b) {
    Flight temp = a;
    a = b;
    b = temp;
}

void deleteFlightByIndex(List& list, int index) {
    if (list.size == 0 || index < 0 || index >= list.size) return;

    Node* toDelete = getNodeAt(list, index);

    if (toDelete->prev) toDelete->prev->next = toDelete->next;
    else list.head = toDelete->next;

    if (toDelete->next) toDelete->next->prev = toDelete->prev;
    else list.tail = toDelete->prev;

    delete toDelete;
    list.size--;
}

void editRecord(Flight& f) {
    cout << "--- Редактирование записи ---\n";

    while (true) {
        cout << "Текущий тип: " << f.type << "\n";
        cout << "1. пассажирский\n2. грузовой\n3. военный\n4. бизнес-джет\n";
        cout << "0. Не менять\nВвод: ";
        int typeChoice = getIntInput();
        if (typeChoice == 0) break;
        if (typeChoice == 1) { f.type = "пассажирский"; break; }
        if (typeChoice == 2) { f.type = "грузовой"; break; }
        if (typeChoice == 3) { f.type = "военный"; break; }
        if (typeChoice == 4) { f.type = "бизнес-джет"; break; }
        cout << "Ошибка!\n";
    }

    int yearInput;
    while (true) {
        cout << "Текущий год выпуска: " << f.year << "\n";
        cout << "Новый год выпуска (-1 чтобы пропустить): ";
        yearInput = getIntInput();
        if (yearInput == -1) break;
        if (yearInput >= 1903 && yearInput <= 2026) { f.year = yearInput; break; }
        cout << "Ошибка! (1903-2026)\n";
    }

    float distInput;
    while (true) {
        cout << "Текущая дистанция: " << f.distance << "\n";
        cout << "Новая дистанция (-1 чтобы пропустить): ";
        distInput = getFloatInput();
        if (distInput == -1) break;
        if (distInput >= 100 && distInput <= 20000) { f.distance = distInput; break; }
        cout << "Ошибка! (100-20000)\n";
    }

    float fuelInput;
    while (true) {
        cout << "Текущий расход на 1000км: " << f.fuel1000 << "\n";
        cout << "Новый расход на 1000км (-1 чтобы пропустить): ";
        fuelInput = getFloatInput();
        if (fuelInput == -1) break;
        if (fuelInput >= 500 && fuelInput <= 20000) { f.fuel1000 = fuelInput; break; }
        cout << "Ошибка! (500-20000)\n";
    }

    f.fuelDay = f.fuel1000 * f.distance / 1000;
    cout << "Запись обновлена. Суточный расход: " << f.fuelDay << endl;
}


