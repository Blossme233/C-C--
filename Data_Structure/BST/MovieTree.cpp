#include "MovieTree.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
void printHelp(MovieNode *temp) {
    if (temp == NULL) {
        return;
    } else {
        printHelp(temp->left);
        cout << "Movie: " << temp->title << " " << temp->rating << endl;
        printHelp(temp->right);
    }
}

void queryHelp(MovieNode *temp, float rating, int year) {
    if (temp == NULL) {
        return;
    }
    if (temp->rating >= rating && temp->year > year) {
        cout << temp->title << "(" << temp->year << ") " << temp->rating
             << endl;
    }
    queryHelp(temp->left, rating, year);
    queryHelp(temp->right, rating, year);
}

void averageHelp(MovieNode *temp, float &sum, int &count) {
    if (temp == NULL) {
        return;
    }
    averageHelp(temp->left, sum, count);
    sum += temp->rating;
    count++;
    averageHelp(temp->right, sum, count);
}

void levelHelp(MovieNode *temp, int level) {
    if (temp == NULL) {
        return;
    }
    if (level == 0) {
        cout << "Movie: " << temp->title << " " << temp->rating << endl;
    } else {
        levelHelp(temp->left, level - 1);
        levelHelp(temp->right, level - 1);
    }
}

// int getLevelUtil(MovieNode *node, int key, int level) {
//     if (node == NULL) return 0;

//     if (node->key == key) return level;

//     int downlevel = getLevelUtil(node->left, key, level + 1);
//     if (downlevel != 0) return downlevel;

//     downlevel = getLevelUtil(node->right, key, level + 1);
//     return downlevel;
// }

// /* Returns level of given key value */
// int getLevel(MovieNode *node, int key) { return getLevelUtil(node, key, 1); }

MovieTree::MovieTree() {
    // write your code
    this->root = NULL;
}

MovieTree::~MovieTree() {
    // write your code
    delete root;
}

void MovieTree::printMovieInventory() {
    if (root == NULL) {
        cout << "Tree is Empty. Cannot print" << endl;
    }
    printHelp(root);
}

void MovieTree::addMovieNode(int ranking, string title, int year,
                             float rating) {
    // write your code
    MovieNode *temp = new MovieNode(ranking, title, year, rating);
    if (this->root == NULL) {
        root = temp;
    } else {
        MovieNode *currNode = root;
        while (currNode != NULL) {
            if (currNode->title > title) {
                if (currNode->left == NULL) {
                    currNode->left = temp;
                    break;
                } else {
                    currNode = currNode->left;
                }
            } else if (currNode->title < title) {
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

void MovieTree::findMovie(string title) {
    // write your code
    MovieNode *temp = this->root;
    if (temp == NULL) {
        cout << "Tree is empty" << endl;
    } else {
        while (temp != NULL) {
            if (temp->title > title) {
                temp = temp->left;
            } else if (temp->title < title) {
                temp = temp->right;
            } else {
                break;
            }
        }
        if (temp == NULL) {
            cout << "Movie not found." << endl;
        } else {
            cout << "Movie Info:" << endl;
            cout << "==================" << endl;
            cout << "Ranking:" << temp->ranking << endl;
            cout << "Title  :" << temp->title << endl;
            cout << "Year   :" << temp->year << endl;
            cout << "rating :" << temp->rating << endl;
        }
    }
}

void MovieTree::queryMovies(float rating, int year) {
    // write your code
    if (root == NULL) {
        cout << "Tree is Empty. Cannot query Movies" << endl;
    } else {
        cout << "Movies that came out after " << year
             << " with rating at least " << rating << ": " << endl;
        queryHelp(root, rating, year);
    }
}

void MovieTree::averageRating() {
    // write your code
    if (root == NULL) {
        cout << "Average rating:0.0" << endl;
    } else {
        int count = 0;
        float sum = 0.0;
        averageHelp(root, sum, count);
        cout << "Average rating:" << float(sum / count) << endl;
    }
}

void MovieTree::printLevelNodes(int level) {
    // write your code
    levelHelp(root, level);
}
