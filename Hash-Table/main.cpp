//
//  main.cpp
//  Hash-Table
//
//  Created by Desislava Stoyanova on 10/17/15.
//  Copyright © 2015 Desislava Stoyanova. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

//   Template for Linked List
//------------------------------
template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>&);
    LinkedList<T>& operator=(const LinkedList<T>&);
    
    void insert(const T&);
    bool search(const T&) const;
    void remove(const T&);
    void print() const;
    bool empty() const;
    size_t size() const;
private:
    Node<T>* start;
    Node<T>* end;
    
    void copyLinkedList(const LinkedList<T>&);
    void deleteLinkedList();
};

template <typename T>
LinkedList<T>::LinkedList() {
    start = NULL;
    end = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    deleteLinkedList();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    copyLinkedList(list);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
    if (this != &list) {
        deleteLinkedList();
        copyLinkedList(list);
    }
    return *this;
}

template <typename T>
void LinkedList<T>::insert(const T& elem) {
    if (empty()) {
        start = new Node<T>;
        start->data = elem;
        start->next = NULL;
        end = start;
    }
    else {
        Node<T>* p = end;
        end = new Node<T>;
        end->data = elem;
        end->next = NULL;
        p->next = end;
    }
}

template <typename T>
bool LinkedList<T>::search(const T& elem) const {
    bool flag = false;
    if (!empty()) {
        Node<T>* p = start;
        while (p) {
            if (p->data == elem) {
                flag = true;
                break;
            }
            p = p->next;
        }
    }
    return flag;
}

template <typename T>
void LinkedList<T>::remove(const T& elem) {
    if (!empty()) {
        Node<T>* p = start;
        Node<T>* q = NULL;
        while (p) {
            if (p->next->data == elem) {
                q = p->next;
                break;
            }
            p = p->next;
        }
        p->next = p->next->next;
        delete q;
    }
}

template <typename T>
void LinkedList<T>::print() const {
    if (!empty()) {
        Node<T>* p = start;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
}

template <typename T>
inline bool LinkedList<T>::empty() const {
    return start == NULL && end == NULL;
}

template <typename T>
size_t LinkedList<T>::size() const {
    size_t br = 0;
    if (!empty()) {
        Node<T>* p = start;
        while (p) {
            br++;
            p = p->next;
        }
    }
    return br;
}

template <typename T>
void LinkedList<T>::copyLinkedList(const LinkedList<T>& list) {
    if (!list.empty()) {
        Node<T>* p = list.start;
        start = new Node<T>;
        start->data = p->data;
        start->next = NULL;
        end = start;
        p = p->next;
        while (p) {
            insert(p->data);
            p = p->next;
        }
    }
}

template <typename T>
void LinkedList<T>::deleteLinkedList() {
    if (!empty()) {
        Node<T>* p = start;
        Node<T>* q = NULL;
        while (p) {
            q = p;
            p = p->next;
            delete q;
        }
    }
}

//   Template for Hash Table
//------------------------------
template <typename T>
class HashTable {
public:
    HashTable();
    HashTable(const size_t&);
    ~HashTable();
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
    
    void output() const;
    bool empty() const;
    void insert(int(*func)(T),T);
    bool search(int(*func)(T),T) const;
    void remove(int(*func)(T),T);
private:
    LinkedList<T>* array;
    size_t size;
    
    void copy(const HashTable&);
};

template <typename T>
HashTable<T>::HashTable() {
    array = NULL;
    size = 0;
}

template <typename T>
HashTable<T>::HashTable(const size_t& n) {
    array = new LinkedList<T>[n];
    size = n;
}

template <typename T>
HashTable<T>::~HashTable() {
    delete [] array;
}

template <typename T>
HashTable<T>::HashTable(const HashTable& t) {
    copy(t);
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable& t) {
    if (this != &t) {
        delete [] array;
        copy(t);
    }
    return *this;
}

template <typename T>
void HashTable<T>::output() const {
    if (!empty()) {
        bool flag = false;
        size_t elements = 0;
        for (int i = 0; i < size; i++) {
            size_t count = array[i].size();
            if (count > 30) {
                flag = true;
            }
            elements += count;
        }
        if (!flag) {
            for (int i = 0; i < size; i++) {
                cout << "Bucket " << i << ": ";
                if (!array[i].empty()) {
                    array[i].print();
                }
                else {
                    cout << "empty" << endl;
                }
            }
        }
        else {
            cout << "Elements = " << elements << endl;
        }
    }
}

template <typename T>
inline bool HashTable<T>::empty() const {
    return size == 0;
}

template <typename T>
inline void HashTable<T>::insert(int(*func)(T),T e) {
    array[func(e)].insert(e);
}

template <typename T>
inline bool HashTable<T>::search(int(*func)(T),T e) const{
    return array[func(e)].search(e);
}

template <typename T>
inline void HashTable<T>::remove(int(*func)(T),T e) {
    return array[func(e)].remove(e);
}

template <typename T>
void HashTable<T>::copy(const HashTable& t) {
    if (!t.empty()) {
        for (int i = 0; i < size; i++) {
            array[i] = t.array[i];
        }
        size = t.size;
    }
}

typedef HashTable<int> HashTableIntegers;
typedef HashTable<char*> HashTableStrings;

// Returns a string's value as integer
int getStringValue(char* str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); i++) {
        sum += str[i];
    }
    return sum;
}

// Generates a random string with length 2 * n
char* randstring(const int& n) {
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
    char* str = new char[2 * n];
    
    for (int i = 0; i < 2 * n; i++) {
        str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    str[2 * n] = 0;
    
    return str;
}

// Hash functions
int h1(int e) {
    return (37 * e) % 11;
}

int h2(int e) {
    return (30 * e) % 8;
}

int h3(int e) {
    return (e * e) % 23;
}

int h4(char* e) {
    return getStringValue(e) % 19;
}

// Test functions
void test1() {
    HashTableIntegers t = HashTableIntegers(11);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h1, rand() % 1000);
    }
    t.output();
}

void test2() {
    HashTableIntegers t = HashTableIntegers(8);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h2, rand() % 1000);
    }
    t.output();
}

void test3() {
    HashTableIntegers t = HashTableIntegers(23);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h3, rand() % 1000);
    }
    t.output();
}

void test4() {
    HashTableIntegers t = HashTableIntegers(11);
    for (int i = 1; i <= 111; i += 11) {
        t.insert(&h1, i);
    }
    t.output();
}

void testdna() {
    HashTableStrings t = HashTableStrings(19);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h4, randstring(10));
    }
    t.output();
}

int main(int argc, const char * argv[]) {
    return 0;
}
