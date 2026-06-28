#include <windows.h>

#include "sort.h"
#include "algo.h"
#include "io.h"
#include "file.h"
#include "check.h"
#include <iostream>

using namespace std;

void selectionSort(List& list, int field, int asc) {
    for (int i = 0; i < list.size - 1; i++) {
        int target = i;
        for (int j = i + 1; j < list.size; j++) {
            Node* nodeJ = getNodeAt(list, j);
            Node* nodeTarget = getNodeAt(list, target);
            bool shouldSwap = false;
            
            if (asc) { 
                if (field == 1 && nodeJ->data.type < nodeTarget->data.type) shouldSwap = true;
                if (field == 2 && nodeJ->data.year < nodeTarget->data.year) shouldSwap = true;
                if (field == 3 && nodeJ->data.fuel1000 < nodeTarget->data.fuel1000) shouldSwap = true;
                if (field == 4 && nodeJ->data.fuelDay < nodeTarget->data.fuelDay) shouldSwap = true;
                if (field == 5 && nodeJ->data.distance < nodeTarget->data.distance) shouldSwap = true;
            } else {
                if (field == 1 && nodeJ->data.type > nodeTarget->data.type) shouldSwap = true;
                if (field == 2 && nodeJ->data.year > nodeTarget->data.year) shouldSwap = true;
                if (field == 3 && nodeJ->data.fuel1000 > nodeTarget->data.fuel1000) shouldSwap = true;
                if (field == 4 && nodeJ->data.fuelDay > nodeTarget->data.fuelDay) shouldSwap = true;
                if (field == 5 && nodeJ->data.distance > nodeTarget->data.distance) shouldSwap = true;
            }

            if (shouldSwap) {
                target = j;
            }
        }
        if (target != i) {
            Node* nodeI = getNodeAt(list, i);
            Node* nodeTarget = getNodeAt(list, target);
            swapFlights(nodeI->data, nodeTarget->data);
        }
    }
}

void handleSort(List& list) {
    system("cls");
    if (list.size == 0) {
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
    cout << "5. Дистанция полета\n";
    cout << "0. Выход\n";
    cout << "Ввод: ";
    int field; check_range(field, 5);
    if (field == 0) return;

    cout << "Направление:\n1. По возрастанию\n2. По убыванию\n0. Выход\nВвод: ";
    int dir; check_range(dir, 2);
    if (dir == 0) return;

    List backup;
    copyList(backup, list);

    selectionSort(list, field, (dir == 1));
    
    cout << "Сортировка выполнена.\n";
    printTable(list);

    askApplyAndSave(list, backup, "Сортировка");
}
