#include "BST.hpp"
using namespace std;

/**
 * @brief  Constructor
 * @note   /
 * @retval None
 */
BST::BST() { this->root = NULL; }

/**
 * @brief  insert a new node into the tree based on the binary search tree rules
 * @note
 * @param  key: the key value of each node
 * @retval None
 */
/*
void BST::insert(int key) {
    BSTNode *temp = new BSTNode(key);
    if (this->root == NULL) {
        root = temp;
    } else {
        BSTNode *currNode = root;
        while (currNode != NULL) {
            if (currNode->key > key) {
                if (currNode->left == NULL) {
                    currNode->left = temp;
                    break;
                } else {
                    currNode = currNode->left;
                }
            } else if (currNode->key < key) {
                if (currNode->right == NULL) {
                    currNode->right = temp;
                    break;
                } else {
                    currNode = currNode->right;
                }
            }
        }
    }
}
*/

BSTNode *insertHelper(BSTNode *node, BSTNode *key) //EXAM READY
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return key;
    /* Otherwise, recur down the tree */
    if (key->key < node->key)
        node->left = insertHelper(node->left, key);
    else if (key->key > node->key)
        node->right = insertHelper(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

void BST::insert(int key)
{
    BSTNode *temp = new BSTNode(key);
    if (root == NULL)
    {
        root - temp;
    }
    else
    {
        insertHelper(root, temp);
    }
}

/**
 * @brief  use traverse method to find a specific key value
 * @note   based on the Big O, three traverse methods' time complecity is about
 * same, so we randomly choose one
 * @param  key: the key value of each node
 * @retval return true if the value is found, otherwise return false
 */
BSTNode *BST::search(int key)
{
    BSTNode *temp = this->root;
    if (temp == NULL)
    {
        return nullptr;
        cout << "Tree is empty." << endl;
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->key > key)
            {
                temp = temp->left;
            }
            else if (temp->key < key)
            {
                temp = temp->right;
            }
            else
            {
                break;
            }
        }
        return temp;
    }
}

/**
 * @brief  the traverse helper function
 * @note
 * @param  temp: the traverse node
 * @retval None
 */
void displayHelp(BSTNode *temp)
{
    if (temp == NULL)
    {
        return;
    }
    else
    {
        displayHelp(temp->left);
        cout << temp->key << " ";
        displayHelp(temp->right);
    }
}

bool BST::display()
{
    if (root == NULL)
    {
        return false;
        cout << "Tree is empty" << endl;
    }
    else
    {
        displayHelp(root);
        return true;
    }
}

/**
 * @brief  free the tree
 * @note
 * @retval None
 */
BST::~BST() { delete root; }