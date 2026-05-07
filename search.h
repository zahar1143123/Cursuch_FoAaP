#pragma once
#include "Flight.h"

// Обработчик пункта меню (Бинарный поиск одной записи)
void handleSearch(Flight*& flights, int& n);

// Обработчик пункта меню (Редактирование по индексу)
void handleEditByIndex(Flight*& flights, int& n);

// Обработчик пункта меню (Фильтрация через Бинарный поиск)
void handleFilter(Flight*& flights, int& n);