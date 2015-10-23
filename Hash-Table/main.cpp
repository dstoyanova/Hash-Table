//
//  main.cpp
//  Hash-Table
//
//  Created by Desislava Stoyanova on 10/17/15.
//  Copyright © 2015 Desislava Stoyanova. All rights reserved.
//

#include <iostream>
#include <list>

using namespace std;

//   Template for Hash Table
//------------------------------
template <typename T>
class HashTable {
public:
    // Big four
    HashTable();
    HashTable(const size_t&);
    ~HashTable();
    HashTable(const HashTable<T>&);
    HashTable<T>& operator=(const HashTable<T>&);
    // Modifiers
    void insert(int (*f)(T),T e);
    bool search(int (*f)(T),T e) const;
    void remove(int (*f)(T),T e);
    // Print the content
    void output() const;
private:
    // Properties
    size_t size;
    list<T>* table;
    // Helpers
    void copy(const HashTable<T>&);
};

template <typename T>
HashTable<T>::HashTable() {
    size = 0;
    table = NULL;
}

template <typename T>
HashTable<T>::HashTable(const size_t& pSize) {
    size = pSize;
    table = new list<T>[pSize];
}

template <typename T>
HashTable<T>::~HashTable() {
    delete [] table;
}

template <typename T>
HashTable<T>::HashTable(const HashTable<T>& pTable) {
    copy(pTable);
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& pTable) {
    if (this != &pTable) {
        delete [] table;
        copy(pTable);
    }
    return *this;
}

template <typename T>
void HashTable<T>::copy(const HashTable<T>& pTable) {
    size = pTable.size;
    table = new list<T>[size];
    for (int i = 0; i < pTable.size; i++) {
        table[i] = pTable.table[i];
    }
}

template <typename T>
void HashTable<T>::insert(int (*f)(T), T e) {
    table[f(e)].push_front(e);
}

template <typename T>
bool HashTable<T>::search(int (*f)(T), T e) const {
    bool flag = false;
    int i = f(e);
    if (!table[i].empty()) {
        typename list<T>::iterator iterator = table[i].begin();
        while (iterator != table[i].end()) {
            if (*iterator == e) {
                flag = true;
                break;
            }
            iterator++;
        }
    }
    return flag;
}

template <typename T>
void HashTable<T>::remove(int (*f)(T), T e) {
    table[f(e)].remove(e);
}

template <typename T>
void HashTable<T>::output() const {
    for (int i = 0; i < size; i++) {
        cout << "Bucket " << i;
        if (table[i].empty()) {
            cout << " is empty! " << endl;
        }
        else {
            cout << " has elements: " << endl;
            typename list<T>::iterator iterator = table[i].begin();
            while (iterator != table[i].end()) {
                cout << *iterator << " ";
                iterator++;
            }
            cout << endl;
        }
    }
}

// Return a string's value as integer
int getStringValue(char* str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); i++) {
        sum += str[i];
    }
    return sum;
}

// Generate a random string with length 2 * n
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

typedef HashTable<int> HashTableIntegers;
typedef HashTable<char*> HashTableStrings;

// Test functions
void test1() {
    cout << "----- Test 1 -----" << endl;
    HashTableIntegers t = HashTableIntegers(11);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h1, rand() % 1000);
    }
    t.output();
}

void test2() {
    cout << "----- Test 2 -----" << endl;
    HashTableIntegers t = HashTableIntegers(8);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h2, rand() % 1000);
    }
    t.output();
}

void test3() {
    cout << "----- Test 3 -----" << endl;
    HashTableIntegers t = HashTableIntegers(23);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h3, rand() % 1000);
    }
    t.output();
}

void test4() {
    cout << "----- Test 4 -----" << endl;
    HashTableIntegers t = HashTableIntegers(11);
    for (int i = 1; i <= 111; i += 11) {
        t.insert(&h1, i);
    }
    t.output();
}

void testdna() {
    cout << "----- Test 5 -----" << endl;
    HashTableStrings t = HashTableStrings(19);
    for (int i = 0; i < 1000; i++) {
        t.insert(&h4, randstring(10));
    }
    t.output();
}

int main(int argc, const char * argv[]) {
    test1();
    test2();
    test3();
    test4();
    testdna();
    return 0;
}
