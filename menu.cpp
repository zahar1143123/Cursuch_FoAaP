#include <windows.h>

#include "menu.h"
#include "io.h"
#include "file.h"
#include "sort.h"
#include "search.h"
#include "check.h"
#include <iostream>
#include <limits>

using namespace std;

void showMenu(Flight*& flights, int& n) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    string filename;

    do {
        system("cls");
        cout << "\n=== АЭРОПОРТ: СПРАВОЧНИК АВИАРЕЙСОВ ===\n"
             << "1. Добавить авиарейс\n"
             << "2. Вывод данных (Отчет по расходу)\n"
             << "3. Создать новый файл\n"
             << "4. Удалить файл\n"
             << "5. Сохранить данные в файл\n"
             << "6. Загрузить данные из файла\n"
             << "7. Очистить весь список\n"
             << "8. Сортировка списка\n"
             << "9. Поиск записей\n"
             << "10. Редактирование по индексу\n"
             << "11. Фильтрация (Бинарный поиск диапазона)\n"
             << "12. Сгенерировать тестовые данные (20 шт.)\n"
             << "0. Выход\n"
             << "Ввод: ";

        choice = getIntInput();

        switch (choice) {
            case 1: 
                addRecord(flights, n); 
                system("pause"); 
                break;
            case 2: {
                system("cls");
                if (n == 0) { cout << "Нет данных.\n"; system("pause"); break; }
                cout << "=== ОТЧЕТ ПО РАСХОДУ ТОПЛИВА ===\n";
                
                // Сортировка для отчета (по расходу за сутки, убывание)
                for(int i=0; i<n-1; i++) {
                    for(int j=i+1; j<n; j++) {
                        if(flights[j].fuelDay > flights[i].fuelDay) {
                            Flight t = flights[i]; flights[i] = flights[j]; flights[j] = t;
                        }
                    }
                }
                printTable(flights, n);
                system("pause");
                break;
            }
            case 3: 
                cout << "Имя файла: "; 
                cin >> filename;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                new_DB(filename); 
                system("pause");
                break;
            case 4: 
                cout << "Имя файла: "; cin >> filename; 
                remove_DB(filename); 
                system("pause");
                break;
            case 5: 
                save_DB(flights, n); break;
            case 6: 
                load_DB(flights, n); break;
            case 7: 
                clearMem(flights, n); 
                system("pause");
                break;
            case 8:
                handleSort(flights, n); 
                break;
            case 9:
                handleSearch(flights, n); 
                break;
            case 10:
                handleEditByIndex(flights, n); 
                break;
            case 11: 
                handleFilter(flights, n); 
                break; // Наша новая фильтрация
            case 12:
                system("cls");
                fillTestData(flights, n);
                system("pause");
                break;
            
        }
    } while (choice != 0);

    clearMem(flights, n);
}