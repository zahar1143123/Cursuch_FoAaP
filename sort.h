#pragma once
#include "Flight.h"

// Обработчик меню
void handleSort(Flight*& flights, int& n);

// Сам алгоритм сортировки (нужен search.cpp и menu.cpp)
void selectionSort(Flight* arr, int n, int field, int asc);