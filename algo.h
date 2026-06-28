#pragma once
#include "Flight.h"
#include <string>

using namespace std;

void swapFlights(Flight& a, Flight& b);

void deleteFlightByIndex(List& list, int index);

void editRecord(Flight& f);