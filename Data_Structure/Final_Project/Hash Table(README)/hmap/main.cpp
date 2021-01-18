#include <iostream>
#include <fstream>
#include "hash.cpp"

using namespace std;

char fileName[50] = "dataSetB.csv";

int main() {
    cout << "-----------Linear PROBING--------------------" << endl;
    cout << "Enter FileName" << endl;
 //   cin >> fileName;
    HashTable *hashTable = new HashTable(40009);
    ifstream in(fileName);
    int key;
    char x;
    if (in.is_open()) {
        while (!in.eof()) {
            in >> key;
            hashTable->insertItem(key);
            in >> x;
        }
    } else {
        cout << "err Reading file" << endl;
    }
    cout << "No of COLLISION : " << hashTable->getNumOfCollision() << endl;
    char op = ' ';
    while (op != 'Q' && op != 'q') {
        cout << "Q for quit\nI for input\nP for print" << endl;
        cin >> op;
        if (op == 'P')
            hashTable->printTable();
        if (op == 'I') {
            int key;
            cout << "Enter Key : ";
            cin >> key;
            node *n = hashTable->searchItem(key);
            if (n == nullptr)
                cout << "No item exist" << endl;
            else
                cout << n->key << " Exists" << endl;
        }
    }
    cout << "Enter FileName" << endl;

    cout << "-----------QUADRATIC PROBING--------------------" << endl;
    HashTable *hashTable1 = new HashTable(40009);
    ifstream in1(fileName);
    int key1;
    char x1;
    if (in1.is_open()) {
        while (!in1.eof()) {
            in1 >> key;
            hashTable1->insertItemQprobing(key);
            in1 >> x;
        }
    } else {
        cout << "err Reading file" << endl;
    }
    cout << "No of COLLISION : " << hashTable1->getNumOfCollision() << endl;
    op = ' ';
    while (op != 'Q' && op != 'q') {
        cout << "Q for quit\nI for input\nP for print" << endl;
        cin >> op;
        if (op == 'P')
            hashTable1->printTable();
        if (op == 'I') {
            int key;
            cout << "Enter Key : ";
            cin >> key;
            node *n = hashTable1->searchItemQpobing(key);
            if (n == nullptr)
                cout << "No item exist" << endl;
            else
                cout << n->key << " Exists" << endl;
        }
    }
    cout << "-----------LinkList PROBING--------------------" << endl;
    hashTable1 = new HashTable(40009);
    ifstream in2(fileName);
    if (in2.is_open()) {
        while (!in2.eof()) {
            in2 >> key;
            hashTable1->insertItemLinkList(key);
            in2 >> x;
        }
    } else {
        cout << "err Reading file" << endl;
    }
    cout << "No of COLLISION : " << hashTable1->getNumOfCollision() << endl;
    op = ' ';
    while (op != 'Q' && op != 'q') {
        cout << "Q for quit\nI for input\nP for print" << endl;
        cin >> op;
        if (op == 'P')
            hashTable1->printTable();
        if (op == 'I') {
            int key;
            cout << "Enter Key : ";
            cin >> key;
            node *n = hashTable1->searchItemLinkList(key);
            if (n == nullptr)
                cout << "No item exist" << endl;
            else
                cout << n->key << " Exists" << endl;
        }
    }

    getchar();
    return 0;
}
