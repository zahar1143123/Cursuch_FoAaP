#pragma once
#include "Flight.h"
#include <string>

using namespace std;

void addRecord(Flight*& arr, int& n);
// ƒобавлены startIdx и endIdx со значени€ми по умолчанию
void printTable(Flight* arr, int n, int startIdx = 0, int endIdx = -1);
void fillTestData(Flight*& arr, int& n);