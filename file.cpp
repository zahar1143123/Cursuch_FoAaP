#include <iostream>
#include <fstream>
#include <cstdio>
#include "file.h"
#include "check.h"

using namespace std;

ofstream new_DB(const string& filename) {
    ofstream file(filename, ios::out | ios::trunc);
    if (file.fail())
        cerr << "Ошибка создания файла\n";
    return file;
}

bool remove_DB(const string& filename) {
    if (remove(filename.c_str()) == 0) return true;
    cerr << "Ошибка удаления\n";
    return false;
}

void clearMem(Flight*& arr, int& n) {
    delete[] arr;
    arr = nullptr;
    n = 0;
}

void save_DB(Flight* flights, int& n){
    if (n == 0) {
        cout << "Нет данных.\n";
        system("pause");
        return;
    }
    int num;

    cout << "СОХРАНЕНИЕ \n"; 
    cout << "1. Текстовый \n"; 
    cout << "2. Двоичный \n"; 
    cout << "3. Текстовый с дозаписью \n"; 
    cout << "4. Двоичный с дозаписью \n"; 
    cout << "0. Выход \n"; 
    cout << "Ввод: "; 
    check_range(num, 4);

    if (num == 0) return;

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    switch (num) {
        case 1:
            save_txt(filename, flights, n);
            cout << "Данные сохранены в текст.\n";
            break;
        case 2:
            save_bin(filename, flights, n);
            cout << "Данные сохранены в бинарный файл.\n";
            break;
        case 3:
            txt_append(filename, flights, n);
            cout << "Данные добавлены в текстовый файл.\n";
            break;
        case 4:
            bin_append(filename, flights, n); 
            cout << "Данные добавлены в бинарный файл.\n";
            break;
    }
    system("pause");
}

void load_DB(Flight*& flights, int& n) {
    int choice;
    cout << "\nЗАГРУЗКА ДАННЫХ\n";
    cout << "1. Загрузить из текстового файла\n";
    cout << "2. Загрузить из двоичного файла\n";
    cout << "0. Отмена\n";
    cout << "Ввод: ";
    
    check_range(choice, 2); 

    if (choice == 0) return;

    string filename;
    cout << "Введите имя файла для загрузки: ";
    cin >> filename;

    switch (choice) {
        case 1:
            load_txt(filename, flights, n);
            cout << "Данные успешно загружены из текста (записей: " << n << ")\n";
            break;
        case 2:
            load_bin(filename, flights, n);
            cout << "Данные успешно загружены из бинарного файла (записей: " << n << ")\n";
            break;
    }
    system("pause");
}

void save_txt(const string& filename, Flight* arr, int n) {
    ofstream file(filename);
    if (!file) { 
        cerr << "Ошибка файла\n"; 
        return; 
    }
    file << n << '\n';
    for (int i = 0; i < n; i++)
        file << arr[i].type << '\n'
             << arr[i].year << '\n'
             << arr[i].fuel1000 << '\n'
             << arr[i].distance << '\n'
             << arr[i].fuelDay << '\n';
}

void load_txt(const string& filename, Flight*& arr, int& n) {
    ifstream file(filename);
    if (!file) { cerr << "Ошибка открытия файла\n"; return; }

    int batch_n; // Количество записей в одной "порции" файла

    // Читаем в цикле, пока удается считать число (пока не конец файла)
    while (file >> batch_n) {
        file.ignore(); // Пропускаем перевод строки после числа

        // 1. Создаем временный буфер для текущей порции
        Flight* temp_arr = new Flight[batch_n];

        // 2. Читаем данные из файла во временный буфер
        for (int i = 0; i < batch_n; i++) {
            getline(file, temp_arr[i].type);
            file >> temp_arr[i].year >> temp_arr[i].fuel1000 >> temp_arr[i].distance >> temp_arr[i].fuelDay;
            file.ignore();
        }

        // 3. Расширяем основной массив (arr), чтобы вместить старые + новые данные
        int old_n = n;       // Запоминаем текущее количество
        n += batch_n;        // Увеличиваем счетчик
        Flight* new_arr = new Flight[n]; // Выделяем новую память

        // Копируем старые данные (если были)
        for (int i = 0; i < old_n; i++) {
            new_arr[i] = arr[i];
        }
        // Копируем новые данные из временного буфера
        for (int i = 0; i < batch_n; i++) {
            new_arr[old_n + i] = temp_arr[i];
        }

        // 4. Освобождаем старую память и временный буфер
        delete[] arr;
        delete[] temp_arr;

        // 5. Переназначаем указатель на новый массив
        arr = new_arr;
        
        // Цикл продолжится, попытается считать следующее число. 
        // Если файл закончился, цикл while завершится.
    }
}

void save_bin(const string& filename, Flight* arr, int n) {
    ofstream file(filename, ios::binary);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    file.write((char*)&n, sizeof(n));
    for (int i = 0; i < n; i++) {
        size_t len = arr[i].type.size();
        file.write((char*)&len, sizeof(len));
        file.write(arr[i].type.c_str(), len);
        file.write((char*)&arr[i].year, sizeof(int));
        file.write((char*)&arr[i].fuel1000, sizeof(float));
        file.write((char*)&arr[i].distance, sizeof(float));
        file.write((char*)&arr[i].fuelDay, sizeof(float));
    }
}

void load_bin(const string& filename, Flight*& arr, int& n) {
    ifstream file(filename, ios::binary);
    if (!file) { cerr << "Ошибка открытия бинарного файла\n"; return; }

    while (true) {
        int batch_n;
        file.read((char*)&batch_n, sizeof(batch_n));
        
        // Если не удалось прочитать число (достигнут конец файла или ошибка), выходим
        if (file.fail()) break; 

        if (batch_n <= 0 || batch_n > 10000) { 
            cerr << "Ошибка чтения количества записей\n"; 
            break; 
        }

        // Временный буфер
        Flight* temp_arr = new Flight[batch_n];

        // Чтение порции
        for (int i = 0; i < batch_n; i++) {
            size_t len;
            file.read((char*)&len, sizeof(len));
            if (file.fail() || len > 1000) { 
                cerr << "Ошибка чтения строки\n"; 
                delete[] temp_arr; 
                return; 
            }

            temp_arr[i].type.resize(len);
            file.read(&temp_arr[i].type[0], len);
            file.read((char*)&temp_arr[i].year, sizeof(int));
            file.read((char*)&temp_arr[i].fuel1000, sizeof(float));
            file.read((char*)&temp_arr[i].distance, sizeof(float));
            file.read((char*)&temp_arr[i].fuelDay, sizeof(float));
        }

        // Объединение массивов (логика такая же, как в текстовом варианте)
        int old_n = n;
        n += batch_n;
        Flight* new_arr = new Flight[n];

        for (int i = 0; i < old_n; i++) new_arr[i] = arr[i];
        for (int i = 0; i < batch_n; i++) new_arr[old_n + i] = temp_arr[i];

        delete[] arr;
        delete[] temp_arr;
        arr = new_arr;
        
        // Цикл повторяется для следующего блока данных
    }
}

void txt_append(const string& filename, Flight* arr, int n) {
    ofstream file(filename, ios::app);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    // !!! ДОБАВЛЕНО: Пишем количество записей в этот блок !!!
    file << n << '\n'; 

    for (int i = 0; i < n; i++)
        file << arr[i].type << '\n'
             << arr[i].year << '\n'
             << arr[i].fuel1000 << '\n'
             << arr[i].distance << '\n'
             << arr[i].fuelDay << '\n';
}

void bin_append(const string& filename, Flight* arr, int n) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    // !!! ДОБАВЛЕНО: Пишем количество записей в этот блок !!!
    file.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++) {
        size_t len = arr[i].type.size();
        file.write((char*)&len, sizeof(len));
        file.write(arr[i].type.c_str(), len);
        file.write((char*)&arr[i].year, sizeof(int));
        file.write((char*)&arr[i].fuel1000, sizeof(float));
        file.write((char*)&arr[i].distance, sizeof(float));
        file.write((char*)&arr[i].fuelDay, sizeof(float));
    }
}