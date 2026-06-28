#pragma once
#include <string>

using namespace std;

struct Flight {
    string type;
    int year;
    float fuel1000;
    float distance;
    float fuelDay;
};

struct Node {
    Flight data;
    Node* prev;
    Node* next;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
};

const char* const TEST_DATA_FILE = "testdata.txt";

inline void pushBack(List& list, const Flight& f) {
    Node* newNode = new Node{f, nullptr, nullptr};
    if (!list.head) {
        list.head = list.tail = newNode;
    } else {
        list.tail->next = newNode;
        newNode->prev = list.tail;
        list.tail = newNode;
    }
    list.size++;
}

inline Node* getNodeAt(List& list, int index) {
    Node* curr = list.head;
    for (int i = 0; i < index && curr; i++)
        curr = curr->next;
    return curr;
}

inline void copyList(List& dest, const List& src) {
    Node* curr = src.head;
    while (curr) {
        pushBack(dest, curr->data);
        curr = curr->next;
    }
}

inline void restoreList(List& target, List& backup) {
    Node* curr = target.head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    target.head = target.tail = nullptr;
    target.size = 0;
    curr = backup.head;
    while (curr) {
        pushBack(target, curr->data);
        curr = curr->next;
    }
}