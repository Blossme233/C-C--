#include "LL.hpp"
using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
LL::LL() { this->head = NULL; }

/*
 * Purpose: Add a new node to the Linked List
 *   between the Node *previous and the node that follows it in the
 * list.
 * @param previous node
 * @param key value of the new node
 * @return none
 */
void LL::insertNode(int key)
{
    if (head == NULL)
    {
        LLNode *temp = new LLNode;
        temp->key = key;
        temp->next = head;
        head = temp;
    }
    else
    {
        LLNode *lo;
        lo = head;
        LLNode *temp = new LLNode;
        temp->key = key;
        temp->next = NULL;

        while (lo->next != NULL)
        {
            lo = lo->next;
        }

        lo->next = temp;
    }
}

/*
 * Purpose: Search the Linked List for the specified key and return a pointer to
 * that node
 * @param key value in the Linked List
 * @return pointer to node of node, or NULL if not found
 */
bool LL::searchNode(LLNode *head, int key)
{

    // Base case
    if (head == NULL)
        return false;

    // If key is present in current node, return true
    if (head->key == key)
        return true;

    // Recur for remaining list
    return searchNode(head->next, key);
}

void LL::deleteAll()
{
    LLNode *temp = head;
    head = NULL;
    delete temp;
}

/**
 * @brief  display all the node to test the values
 * @note   /
 * @retval if the linked list is not empty return true, otherwise return false
 */
bool LL::display()
{
    LLNode *temp = head;
    if (temp != NULL)
    {
        while (temp != NULL)
        {
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << endl;
        return true;
    }
    else
    {
        return false;
    }
}

LLNode *LL::returnHead()
{
    return head;
}