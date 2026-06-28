#pragma once
#include "Flight.h"
#include <string>

using namespace std;

bool addRecord(List& list);
void printTable(List& list, int startIdx = 0, int endIdx = -1);
void fillTestData(List& list);