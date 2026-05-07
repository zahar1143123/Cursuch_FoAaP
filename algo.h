#pragma once
#include "Flight.h"
#include <string>

using namespace std;

// Обмен местами двух элементов
void swapFlights(Flight& a, Flight& b);

// Удаление по индексу (изменяет массив и n)
void deleteFlightByIndex(Flight*& arr, int& n, int index);

// Редактирование существующей записи (без изменения размера)
void editRecord(Flight& f);

// Бинарный поиск (требует отсортированного по type массива!)
int binarySearch(Flight* arr, int n, string key);