#pragma once
#include "Flight.h"

// Обработчик пункта меню 9 (Бинарный поиск)
void handleSearch(Flight*& flights, int& n);

// Обработчик пункта меню 10 (Редактирование по индексу)
void handleEditByIndex(Flight*& flights, int& n);