#include <iostream>
#include "hash.h"


HashTable::HashTable(int bsize) {
    this->tableSize = bsize;
    this->numOfcolision = 0;
    this->currentSize = 0;
    this->table = new node *[bsize];
    for (int i = 0; i < bsize; ++i) {
        this->table[i] = nullptr;
    }
}

unsigned int HashTable::hashFunction(int key) {
    return key % this->tableSize;
}

bool HashTable::insertItem(int key) {
    currentSize++;
    unsigned map = hashFunction(key);
    while (table[map] != nullptr) {
        map++;
        map = map % tableSize;
        this->numOfcolision++;
    }
    table[map] = createNode(key, nullptr);
    return true;
}

bool HashTable::insertItemQprobing(int key) {
    currentSize++;
    unsigned map = hashFunction(key);
    if (table[map] == nullptr) {
        table[map] = createNode(key, nullptr);
    }
    int x = 1;
    while (table[map] != nullptr) {
        map = map + (x * x);
        map = map % tableSize;
        cout << map << endl;
        this->numOfcolision++;
        x++;
    }
    table[map] = createNode(key, nullptr);
    return true;
}

bool HashTable::insertItemLinkList(int key) {
    currentSize++;
    unsigned map = hashFunction(key);
    if (table[map] == nullptr) {
        table[map] = createNode(key, nullptr);
        return true;
    }
    this->numOfcolision++;
    node *temp = table[map];
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = createNode(key, nullptr);
    return true;
}

void HashTable::printTable() {
    for (int i = 0; i < this->tableSize; ++i) {
        if (table[i] != nullptr) {
            std::cout << table[i]->key;
            node *temp = table[i]->next;
            while (temp != nullptr) {
                cout << " -> " << temp->key;
                temp = temp->next;
            }
            cout << endl;
        } else
            std::cout << "nullptr" << endl;
    }
    cout << "Current Size :" << currentSize << endl;
}

node *HashTable::createNode(int key, node *next) {
    node *n = new node;
    n->next = next;
    n->key = key;
    return n;
}

int HashTable::getNumOfCollision() {
    return this->numOfcolision;
}

node *HashTable::searchItem(int key) {
    unsigned map = hashFunction(key);
    node *n = nullptr;
    while (table[map] != nullptr) {

        if (table[map]->key == key) {
            n = table[map];
            break;
        }
        map++;
        map = map % tableSize;
    }
    return n;
}

node *HashTable::searchItemQpobing(int key) {
    unsigned map = hashFunction(key);
    node *n = nullptr;
    int x = 0;
    if (table[map]!= nullptr) {
        n = table[map];
        return n;
    }
    x=1;
    while (table[map] != nullptr) {
        if (table[map]->key == key) {
            n = table[map];
            break;
        }
        map = map + (x * x);
        map = map % tableSize;
        x++;
    }
    return n;
}

node *HashTable::searchItemLinkList(int key) {
    unsigned map = hashFunction(key);
    if (table[map] == nullptr)
        return nullptr;
    if (table[map]->key == key)
        return table[map];
    node *temp = table[map];
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}


