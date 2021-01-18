#include "BST.hpp"

#include <iostream>

using namespace std;

/* ----------------------------------------
TODO: Complete the method below.
      You may add helpers, headers (if necessary)
      Helper functions should not be part of the class.
*/

int getLevelUtil(Node* node, int key, int level) {
    if (node == NULL) return 0;

    if (node->key == key) return level;

    int downlevel = getLevelUtil(node->left, key, level + 1);
    if (downlevel != 0) return downlevel;

    downlevel = getLevelUtil(node->right, key, level + 1);
    return downlevel;
}

/* Returns level of given key value */
int getLevel(Node* node, int key) { return getLevelUtil(node, key, 1); }

void recursive_count(Node* temp, int val, int& count) {
    if (temp) {
        recursive_count(temp->left, val, count);
        if (temp->key == val) {
            count++;
        }
        recursive_count(temp->right, val, count);
    }
}

void print_depths_helper(Node* node, int key, int level) {
    while (node) {
        if (key == node->key) {
            cout << level << " ";
        }
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
        level++;
    }
    cout << endl;
}

void BST::print_depths(int val) {
    int level = 0;
    print_depths_helper(root, val, level);  // Use the helper function.
    return;
}

// ----------------------------------------

BST::BST() { root = nullptr; }

BST::~BST() {
    recursive_destroy(root);
    root = nullptr;
}

void BST::print() { print2DUtil(root); }

void BST::insert(int val) { root = recursive_insert(root, val); }

Node* BST::search(int val) { return recursive_search(root, val); }

void BST::inorder() { recursive_inorder(root); }

// -----------------
// RECURSIVE HELPERS
// -----------------
void recursive_destroy(Node* n) {
    if (n) {
        recursive_destroy(n->left);
        recursive_destroy(n->right);
        delete n;
    }
}

Node* recursive_insert(Node* n, int val) {
    if (n == nullptr) {
        Node* tmp = new Node({val, nullptr, nullptr});
        return tmp;
    } else if (val >= n->key) {
        n->right = recursive_insert(n->right, val);
    } else {
        n->left = recursive_insert(n->left, val);
    }

    return n;
}

Node* recursive_search(Node* n, int val) {
    if (!n) {
        return nullptr;
    }

    if (val == n->key) {
        return n;
    } else if (val > n->key) {
        return recursive_search(n->right, val);
    } else {
        return recursive_search(n->left, val);
    }
}

void recursive_inorder(Node* n) {
    if (n) {
        recursive_inorder(n->left);
        cout << n->key << " ";
        recursive_inorder(n->right);
    }
}

void print2DUtil(Node* n, int space, int COUNT) {
    if (n == NULL) return;

    space += COUNT;

    print2DUtil(n->right, space);
    cout << endl;
    for (int i = COUNT; i < space; i++) cout << " ";
    cout << n->key << "\n";

    print2DUtil(n->left, space);
}