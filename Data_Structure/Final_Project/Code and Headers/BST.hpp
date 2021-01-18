#include <cctype>
#include <cfloat>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct BSTNode {
    int key;
    BSTNode* left = NULL;
    BSTNode* right = NULL;
    BSTNode(int keyv) { key = keyv; }
};

class BST {
   private:
    BSTNode* root;

   public:
    BST();
    ~BST();
    void insert(int);
    BSTNode* search(int);
    bool display();
};