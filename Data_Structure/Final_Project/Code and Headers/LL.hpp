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

struct LLNode
{
    int key;
    LLNode *next;
};

class LL
{
private:
    LLNode *head;

public:
    LL();
    void insertNode(int);
    void deleteAll();
    bool searchNode(LLNode *head, int key);
    bool display();
    LLNode *returnHead();
};