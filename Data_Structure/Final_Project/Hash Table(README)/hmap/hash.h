#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

typedef struct node
{
    int key;
    struct node* next;
} node;

class HashTable
{
    // No. of buckets (linked lists)
    int tableSize;
    // Pointer to an array containing buckets
    node **table;
    // The total number of collision
    int numOfcolision =0;
    // To create New Node
    int currentSize;
    node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor
    // inserts a key into hash table
    bool insertItem(int key);
    // hash function to map values to key
    unsigned int hashFunction(int key);
    // To print the table
    void printTable();
    //To get number of Collisions
    int getNumOfCollision();
    //To fine the node
    node* searchItem(int key);

    node *searchItemQpobing(int key);

    node *searchItemLinkList(int key);

    bool insertItemLinkList(int key);

    bool insertItemQprobing(int key);
};

#endif