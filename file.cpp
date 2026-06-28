#include <iostream>
#include <fstream>
#include <cstdio>
#include "file.h"
#include "check.h"

using namespace std;

bool endsWith(const string& str, const string& suffix) {
    if (suffix.size() > str.size()) return false;
    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

string ensureExtension(const string& filename, const string& ext) {
    if (endsWith(filename, ext)) return filename;
    return filename + ext;
}

void new_DB(const string& filename, int format) {
    if (format == 1) {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.fail())
            cerr << "Ошибка создания файла\n";
        else
            cout << "Текстовый файл создан.\n";
    } else {
        ofstream file(filename, ios::out | ios::trunc | ios::binary);
        if (file.fail())
            cerr << "Ошибка создания файла\n";
        else
            cout << "Двоичный файл создан.\n";
    }
}

void create_DB() {
    int format;
    cout << "СОЗДАНИЕ ФАЙЛА\n";
    cout << "1. Текстовый\n";
    cout << "2. Двоичный\n";
    cout << "0. Выход\n";
    cout << "Ввод: ";
    check_range(format, 2);

    if (format == 0) return;

    string filename;
    cout << "Имя файла: ";
    cin >> filename;
    filename = ensureExtension(filename, (format == 1) ? ".txt" : ".bin");

    if (filename == TEST_DATA_FILE) {
        cerr << "Ошибка: нельзя перезаписать файл тестовых данных (" << TEST_DATA_FILE << ")!\n";
        system("pause");
        return;
    }

    new_DB(filename, format);
    system("pause");
}

bool remove_DB(const string& filename) {
    if (filename == TEST_DATA_FILE) {
        cerr << "Ошибка: нельзя удалить файл тестовых данных (" << TEST_DATA_FILE << ")!\n";
        return false;
    }
    if (remove(filename.c_str()) == 0) return true;
    cerr << "Ошибка удаления\n";
    return false;
}

void clearMem(List& list) {
    Node* curr = list.head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

void save_DB(List& list){
    if (list.size == 0) {
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
    if (num == 1 || num == 3) filename = ensureExtension(filename, ".txt");
    else filename = ensureExtension(filename, ".bin");

    if (filename == TEST_DATA_FILE) {
        cerr << "Ошибка: нельзя записать/перезаписать файл тестовых данных (" << TEST_DATA_FILE << ")!\n";
        system("pause");
        return;
    }

    switch (num) {
        case 1:
            save_txt(filename, list);
            cout << "Данные сохранены в текст.\n";
            break;
        case 2:
            save_bin(filename, list);
            cout << "Данные сохранены в бинарный файл.\n";
            break;
        case 3:
            txt_append(filename, list);
            cout << "Данные добавлены в текстовый файл.\n";
            break;
        case 4:
            bin_append(filename, list); 
            cout << "Данные добавлены в бинарный файл.\n";
            break;
    }
    system("pause");
}

void load_DB(List& list) {
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
    if (choice == 1) filename = ensureExtension(filename, ".txt");
    else filename = ensureExtension(filename, ".bin");

    switch (choice) {
        case 1:
            load_txt(filename, list);
            cout << "Данные успешно загружены из текста (записей: " << list.size << ")\n";
            break;
        case 2:
            load_bin(filename, list);
            cout << "Данные успешно загружены из бинарного файла (записей: " << list.size << ")\n";
            break;
    }
    system("pause");
}

void save_txt(const string& filename, List& list) {
    ofstream file(filename);
    if (!file) { 
        cerr << "Ошибка файла\n"; 
        return; 
    }
    file << list.size << '\n';
    Node* curr = list.head;
    while (curr) {
        file << curr->data.type << '\n'
             << curr->data.year << '\n'
             << curr->data.fuel1000 << '\n'
             << curr->data.distance << '\n'
             << curr->data.fuelDay << '\n';
        curr = curr->next;
    }
}

void load_txt(const string& filename, List& list) {
    ifstream file(filename);
    if (!file) { cerr << "Ошибка открытия файла\n"; return; }

    int batch_n;

    while (file >> batch_n) {
        file.ignore();

        for (int i = 0; i < batch_n; i++) {
            Flight f;
            getline(file, f.type);
            file >> f.year >> f.fuel1000 >> f.distance >> f.fuelDay;
            file.ignore();
            pushBack(list, f);
        }
    }
}

void save_bin(const string& filename, List& list) {
    ofstream file(filename, ios::binary);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    file.write((char*)&list.size, sizeof(list.size));
    Node* curr = list.head;
    while (curr) {
        size_t len = curr->data.type.size();
        file.write((char*)&len, sizeof(len));
        file.write(curr->data.type.c_str(), len);
        file.write((char*)&curr->data.year, sizeof(int));
        file.write((char*)&curr->data.fuel1000, sizeof(float));
        file.write((char*)&curr->data.distance, sizeof(float));
        file.write((char*)&curr->data.fuelDay, sizeof(float));
        curr = curr->next;
    }
}

void load_bin(const string& filename, List& list) {
    ifstream file(filename, ios::binary);
    if (!file) { cerr << "Ошибка открытия бинарного файла\n"; return; }

    while (true) {
        int batch_n;
        file.read((char*)&batch_n, sizeof(batch_n));
        
        if (file.fail()) break; 

        if (batch_n <= 0 || batch_n > 10000) { 
            cerr << "Ошибка чтения количества записей\n"; 
            break; 
        }

        for (int i = 0; i < batch_n; i++) {
            Flight f;
            size_t len;
            file.read((char*)&len, sizeof(len));
            if (file.fail() || len > 50) { 
                cerr << "Ошибка чтения строки\n"; 
                return; 
            }

            f.type.resize(len);
            file.read(&f.type[0], len);
            file.read((char*)&f.year, sizeof(int));
            file.read((char*)&f.fuel1000, sizeof(float));
            file.read((char*)&f.distance, sizeof(float));
            file.read((char*)&f.fuelDay, sizeof(float));
            pushBack(list, f);
        }
    }
}

void txt_append(const string& filename, List& list) {
    ofstream file(filename, ios::app);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    file << list.size << '\n'; 

    Node* curr = list.head;
    while (curr) {
        file << curr->data.type << '\n'
             << curr->data.year << '\n'
             << curr->data.fuel1000 << '\n'
             << curr->data.distance << '\n'
             << curr->data.fuelDay << '\n';
        curr = curr->next;
    }
}

void bin_append(const string& filename, List& list) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) { cerr << "Ошибка файла\n"; return; }

    file.write((char*)&list.size, sizeof(list.size));

    Node* curr = list.head;
    while (curr) {
        size_t len = curr->data.type.size();
        file.write((char*)&len, sizeof(len));
        file.write(curr->data.type.c_str(), len);
        file.write((char*)&curr->data.year, sizeof(int));
        file.write((char*)&curr->data.fuel1000, sizeof(float));
        file.write((char*)&curr->data.distance, sizeof(float));
        file.write((char*)&curr->data.fuelDay, sizeof(float));
        curr = curr->next;
    }
}
