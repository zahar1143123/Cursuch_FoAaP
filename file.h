#pragma once
#include "Flight.h"
#include <string>
#include <fstream>

using namespace std;

void new_DB(const string& filename, int format);
void create_DB();
bool remove_DB(const string& filename);
void clearMem(List& list);
void save_DB(List& list);
void save_txt(const string& filename, List& list);
void save_bin(const string& filename, List& list);
void load_DB(List& list);
void load_txt(const string& filename, List& list);
void load_bin(const string& filename, List& list);
void txt_append(const string& filename, List& list);
void bin_append(const string& filename, List& list);