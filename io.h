#pragma once
#include "Flight.h"
#include <string>

using namespace std;

void addRecord(Flight*& arr, int& n);
void printRecord(Flight* arr, int n);
void printTable(Flight* arr, int n);
void selectionSort(Flight* arr, int n);