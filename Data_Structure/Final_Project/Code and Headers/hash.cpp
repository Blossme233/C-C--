#include "hash.hpp"

#include <iostream>

/**
 * @brief  Constructor
 * @note
 * @param  bsize: the size of the hash table
 * @retval
 */
HashTable::HashTable(int bsize) {
    this->tableSize = bsize;
    this->numOfcolision = 0;
    this->currentSize = 0;
    this->table = new node *[bsize];
    for (int i = 0; i < bsize; ++i) {
        this->table[i] = nullptr;
    }
}

unsigned int HashTable::hashFunction(int key) { return key % this->tableSize; }

/**
 * @brief  use linear probing to do the insertion
 * @note
 * @param  key: the key value of each node
 * @retval return true when insertion done
 */
bool HashTable::insertItemLprobing(int key) {
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

/**
 * @brief  use quadratic probing to do the insertion
 * @note
 * @param  key: key value of each node
 * @retval return true when insertion done
 */
bool HashTable::insertItemQprobing(int key) {
    currentSize++;
    unsigned map = hashFunction(key);
    if (table[map] == nullptr) {
        table[map] = createNode(key, nullptr);
    }
    int i = 1;
    while (table[map] != nullptr) {
        map = map + (i * i);
        map = map % tableSize;
        //cout << map << endl;
        this->numOfcolision++;
        i++;
    }
    table[map] = createNode(key, nullptr);
    return true;
}

/**
 * @brief  use linked list to do the insertion
 * @note
 * @param  key: key value of each node
 * @retval return true when insertion done
 */
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

/**
 * @brief  print the table
 * @note
 * @retval None
 */
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

/**
 * @brief  create a node of the linked list
 * @note
 * @param  key: key value of each node
 * @param  *next: next element of node
 * @retval
 */
node *HashTable::createNode(int key, node *next) {
    node *n = new node;
    n->next = next;
    n->key = key;
    return n;
}

int HashTable::getNumOfCollision() { return this->numOfcolision; }

/**
 * @brief  use linear probing to do the insertion
 * @note
 * @param  key: key value of each node
 * @retval return the node after searching
 */
node *HashTable::searchItemLprobing(int key) {
    unsigned map = hashFunction(key);
    node *temp = nullptr;
    while (table[map] != nullptr) {
        if (table[map]->key == key) {
            temp = table[map];
            break;
        }
        map++;
        map = map % tableSize;
    }
    return temp;
}

/**
 * @brief  use quadratic probing to do the search
 * @note
 * @param  key: key value of each node
 * @retval return the node after searching
 */
node *HashTable::searchItemQpobing(int key) {
    unsigned map = hashFunction(key);
    node *n = nullptr;
    int i = 0;
    if (table[map] != nullptr) {
        n = table[map];
        return n;
    }
    i = 1;
    while (table[map] != nullptr) {
        if (table[map]->key == key) {
            n = table[map];
            break;
        }
        map = map + (i * i);
        map = map % tableSize;
        i++;
    }
    return n;
}

/**
 * @brief  use linked list to do the search
 * @note
 * @param  key: key value of each node
 * @retval return the node after searching
 */
node *HashTable::searchItemLinkList(int key) {
    unsigned map = hashFunction(key);
    if (table[map] == nullptr) return nullptr;
    if (table[map]->key == key) return table[map];
    node *temp = table[map];
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
