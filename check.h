#pragma once
#include <string>

using namespace std;

struct List;
struct Flight;

int getIntInput();
float getFloatInput();
string getType();
void check_range(int &num, int max_range);
void freeList(List& list);
void restoreList(List& target, List& backup);
void askApplyAndSave(List& list, List& backup, const char* actionName);
bool askConfirm(const char* message);
