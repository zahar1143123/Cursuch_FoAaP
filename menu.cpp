#include <iostream>
#include <windows.h>
#include "menu.h"
#include "check.h"

using namespace std;

void showMenu(Flight*& flights, int& n) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    string filename;

    do {
        cout << "\nГЛАВНОЕ МЕНЮ\n"
             << "1. Добавить авиарейс\n"
             << "2. Вывод данных\n"
             << "3. Создать новый файл\n"
             << "4. Удалить файл\n"
             << "5. Сохранить данные в файл\n"
             << "6. Загрузить данные из файла\n"
             << "7. Очистить весь список\n"
             << "8. Сортировка списка\n"
             << "9. Поиск записей\n"
             << "10. Редактирование по индексу\n"
             << "0. Выход\n"
             << "Ввод: ";

        choice = getIntInput();

        switch (choice) {
            case 1: 
                addRecord(flights, n); 
                break;
            case 2: 
                printTable(flights, n); 
                break;
            case 3: 
                cout << "Имя файла: "; 
                cin >> filename;
                new_DB(filename); 
                break;
            case 4: 
                cout << "Имя файла: "; 
                cin >> filename; 
                remove_DB(filename); 
                break;
            case 5: 
                save_DB(flights, n);
                break;
            case 6: 
                load_DB(flights, n);
                break;
            case 7: 
                clearMem(flights, n); 
                break;
                        case 8:
                // Вся логика спрятана в sort.cpp
                handleSort(flights, n); 
                break;

            case 9:
                // Вся логика спрятана в search.cpp
                handleSearch(flights, n); 
                break;

            case 10:
                // Вся логика спрятана в search.cpp
                handleEditByIndex(flights, n); 
                break;
        }
    } while (choice != 0);

    clearMem(flights, n);
}