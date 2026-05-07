#pragma once
#include "Flight.h"
#include <string>
#include <fstream>

using namespace std;

ofstream new_DB(const string& filename);
bool remove_DB(const string& filename);
void clearMem(Flight*& arr, int& n);
void save_DB(Flight* arr, int &n);
void save_txt(const string& filename, Flight* arr, int n);
void save_bin(const string& filename, Flight* arr, int n);
void load_DB(Flight*& flights, int& n);
void load_txt(const string& filename, Flight*& arr, int& n);
void load_bin(const string& filename, Flight*& arr, int& n);
void txt_append(const string& filename, Flight* arr, int n);
void bin_append(const string& filename, Flight* arr, int n);