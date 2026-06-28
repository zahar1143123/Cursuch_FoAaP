#include <windows.h>
#include "menu.h"
#include "io.h"
#include "file.h"
#include "algo.h"
#include "sort.h"
#include "search.h"
#include "check.h"
#include <iostream>
#include <limits>

using namespace std;

void showMenu(List& list) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    string filename;

    do {
        system("cls");
        cout << "\n=== АЭРОПОРТ: СПРАВОЧНИК АВИАРЕЙСОВ ===\n"
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
             << "11. Фильтрация\n"
             << "12. Взять тестовые данные из файла (20 шт.)\n"
             << "13. Индивидуальное задание\n"
             << "0. Выход\n"
             << "Ввод: ";

        choice = getIntInput();

        switch (choice) {
            case 1: {
                system("cls");
                if (!addRecord(list)) break;
                cout << "Авиарейс добавлен.\n";
                while (true) {
                    cout << "1. Добавить ещё\n0. В главное меню\nВвод: ";
                    int again;
                    check_range(again, 1);
                    if (again == 0) break;
                    system("cls");
                    if (!addRecord(list)) break;
                    cout << "Авиарейс добавлен.\n";
                }
                break;
            }
            case 2: {
                system("cls");
                if (list.size == 0) { cout << "Нет данных.\n"; system("pause"); break; }
                cout << "=== ОТЧЕТ ПО РАСХОДУ ТОПЛИВА ===\n";
                printTable(list);
                system("pause");
                break;
            }
            case 3:
                system("cls");
                create_DB();
                break;
            case 4: {
                system("cls");
                cout << "Имя файла: "; cin >> filename;
                if (!askConfirm("Удалить файл?")) { system("pause"); break; }
                remove_DB(filename);
                system("pause");
                break;
            }
            case 5:
                system("cls");
                save_DB(list); break;
            case 6:
                system("cls");
                load_DB(list); break;
            case 7: {
                system("cls");
                if (askConfirm("Очистить весь список? Все данные будут удалены."))
                    clearMem(list);
                system("pause");
                break;
            }
            case 8:
                handleSort(list); 
                break;
            case 9:
                handleSearch(list); 
                break;
            case 10:
                handleEditByIndex(list); 
                break;
            case 11: 
                handleFilter(list); 
                break;
            case 12:
                system("cls");
                fillTestData(list);
                system("pause");
                break;
            case 13: {
                system("cls");
                if (list.size == 0) { cout << "Нет данных.\n"; system("pause"); break; }

                List backup;
                copyList(backup, list);
                selectionSort(list, 4, false);

                cout << "=== ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ ===\n";
                cout << "Расход топлива на сутки (по убыванию)\n\n";
                printTable(list);

                askApplyAndSave(list, backup, "Индивидуальное задание");
                break;
            }
            
        }
    } while (choice != 0);

    clearMem(list);
}
