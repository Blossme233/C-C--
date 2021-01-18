#include "MovieTree.hpp"

#include <fstream>
#include <iostream>

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree() { root = NULL; }

void destroyTree(TreeNode* temp) {
    if (temp != NULL) {
        if (temp->leftChild != NULL) {
            destroyTree(temp->leftChild);
        }
        if (temp->rightChild != NULL) {
            destroyTree(temp->rightChild);
        }
        LLMovieNode* current = temp->head;
        delete current;
        current = NULL;
        delete temp;
    }
}

MovieTree::~MovieTree() { destroyTree(root); }

void printMovieInventoryHelper(TreeNode* temp) {
    if (temp != NULL) {
        printMovieInventoryHelper(temp->leftChild);
        cout << "Movies starting with letter: " << temp->titleChar << endl;
        LLMovieNode* currNode = temp->head;
        while (currNode != NULL) {
            cout << " >> " << currNode->title << " " << currNode->rating
                 << endl;
            currNode = currNode->next;
        }

        printMovieInventoryHelper(temp->rightChild);
    }
}

void MovieTree::printMovieInventory() { printMovieInventoryHelper(root); }

TreeNode* addMovieHelper(TreeNode*& temp, TreeNode* newNode) {
    if (temp == NULL) {
        return newNode;
    }

    if (newNode->titleChar < temp->titleChar) {
        TreeNode* leftNode = addMovieHelper(temp->leftChild, newNode);
        temp->leftChild = leftNode;
        leftNode->parent = temp;
    } else if (newNode->titleChar > temp->titleChar) {
        TreeNode* rightNode = addMovieHelper(temp->rightChild, newNode);
        temp->rightChild = rightNode;
        rightNode->parent = temp;
    } else if (newNode->titleChar == temp->titleChar) {
        LLMovieNode* nodeToInsert = newNode->head;
        LLMovieNode* currNode = temp->head;
        LLMovieNode* prevNode = NULL;
        while (currNode != NULL &&
               currNode->title.compare(nodeToInsert->title) < 0) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        if (currNode != NULL &&
            currNode->title.compare(nodeToInsert->title) == 0) {
            return temp;
        } else {
            if (prevNode == NULL) {
                nodeToInsert->next = temp->head;
                temp->head = nodeToInsert;
            } else if (currNode == NULL) {
                prevNode->next = nodeToInsert;
            } else {
                prevNode->next = nodeToInsert;
                nodeToInsert->next = currNode;
            }
        }
    }

    return temp;
}

void MovieTree::addMovie(int ranking, std::string title, int year,
                         float rating) {
    LLMovieNode* temp = new LLMovieNode(ranking, title, year, rating);
    TreeNode* newNode = new TreeNode;
    newNode->head = temp;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;
    newNode->titleChar = title[0];
    root = addMovieHelper(root, newNode);
}

TreeNode* deleteMovieHelper(TreeNode* temp, string title) {
    if (temp == NULL) {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return temp;
    } else {
        if (title[0] < temp->titleChar) {
            temp->leftChild = deleteMovieHelper(temp->leftChild, title);
        } else if (title[0] > temp->titleChar) {
            temp->rightChild = deleteMovieHelper(temp->rightChild, title);
        } else {
            LLMovieNode* currNode = temp->head;
            LLMovieNode* prevNode = NULL;

            while (currNode != NULL && currNode->title != title) {
                prevNode = currNode;
                currNode = currNode->next;
            }

            if (currNode == NULL) {
                cout << "Movie: " << title << " not found, cannot delete."
                     << endl;
                return temp;
            } else {
                if (prevNode == NULL && temp->head->next != NULL) {
                    temp->head = temp->head->next;
                    return temp;
                } else if (prevNode != NULL && currNode != NULL) {
                    prevNode->next = currNode->next;
                    return temp;
                }

                if (temp->leftChild == NULL && temp->rightChild == NULL) {
                    delete temp;
                    temp = NULL;
                } else if (temp->leftChild == NULL) {
                    TreeNode* tempNode = temp;
                    temp->rightChild->parent = temp->parent;
                    temp = temp->rightChild;
                    delete tempNode;
                } else if (temp->rightChild == NULL) {
                    TreeNode* tempNode = temp;
                    temp->leftChild->parent = temp->parent;
                    temp = temp->leftChild;
                    delete tempNode;
                } else {
                    TreeNode* minValueNode = temp->rightChild;
                    while (minValueNode->leftChild != NULL) {
                        minValueNode = minValueNode->leftChild;
                    }
                    temp->head = minValueNode->head;
                    temp->titleChar = minValueNode->titleChar;
                    temp->rightChild = deleteMovieHelper(
                        temp->rightChild, minValueNode->head->title);
                }
            }
        }
    }

    return temp;
}

void MovieTree::deleteMovie(string title) {
    root = deleteMovieHelper(root, title);
}

void MovieTree::leftRotation(TreeNode* currNode) {
    TreeNode* temp = currNode->rightChild;
    currNode->rightChild = temp->leftChild;
    if (temp->leftChild != NULL) {
        temp->leftChild->parent = currNode;
    }
    temp->parent = currNode->parent;
    if (currNode->parent == NULL) {
        root = temp;
    } else if (currNode == currNode->parent->leftChild) {
        currNode->parent->leftChild = temp;
    } else {
        currNode->parent->rightChild = temp;
    }
    temp->leftChild = currNode;
    currNode->parent = temp;
}
// persudocode on C++ Primer
//------ Given Methods--------//

void _grader_inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    _grader_inorderTraversal(root->leftChild);
    cout << root->titleChar << " ";
    _grader_inorderTraversal(root->rightChild);
}

void MovieTree::inorderTraversal() {
    _grader_inorderTraversal(root);
    cout << endl;
}

TreeNode* searchCharHelper(TreeNode* currNode, char key) {
    if (currNode == NULL)
        return currNode;
    else if (currNode->titleChar == key)
        return currNode;
    else if (currNode->titleChar > key)
        return searchCharHelper(currNode->leftChild, key);
    else
        return searchCharHelper(currNode->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key) {
    return searchCharHelper(root, key);
}
