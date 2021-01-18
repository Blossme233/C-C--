#include "Graph.hpp"

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

void Graph::addEdge(string v1, string v2) {
    int index;
    adjVertex temp, temp2;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == v1) {
            index = i;
        }
    }
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == v2 && index != i) {
            temp.v = vertices[index];
            temp2.v = vertices[i];
            vertices[index]->adj.push_back(temp2);
            vertices[i]->adj.push_back(temp);
        }
    }
}

void Graph::addVertex(string name) {
    bool found = false;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == name) {
            found = true;  // means this element is already in the structure
        }
    }
    if (found == false) {
        vertex* temp = new vertex;
        temp->name = name;
        vertices.push_back(temp);
        // if there is no exist element inside, then put this in
    }
}

void Graph::displayEdges() {
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i]->name << " --> ";
        for (int j = 0; j < vertices[i]->adj.size(); j++) {
            cout << " " << vertices[i]->adj[j].v->name;
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex) {
    vertex* temp = NULL;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == sourceVertex) {
            temp = vertices[i];
        }
    }
    temp->visited = true;
    temp->distance = 0;
    queue<vertex*> tempNode;
    tempNode.push(temp);
    cout << "Starting vertex (root): " << temp->name << "-> ";
    while (!tempNode.empty()) {
        vertex* pres = tempNode.front();
        tempNode.pop();
        for (int i = 0; i < pres->adj.size(); i++) {
            if (!(pres->adj[i].v)->visited) {
                (pres->adj[i].v)->distance = pres->distance + 1;
                (pres->adj[i].v)->visited = true;
                cout << pres->adj[i].v->name << "(" << pres->adj[i].v->distance
                     << ")"
                     << " ";
                tempNode.push(pres->adj[i].v);
            }
        }
        pres->visited = true;
    }
}
void DFShelper(vertex* temp) {
    if (temp->visited == false) {
        temp->visited = true;
        for (int i = 0; i < temp->adj.size(); i++) {
            DFShelper(temp->adj[i].v);
        }
    }
}
int Graph::getConnectedComponents() {
    int count = 0;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->visited == false) {
            DFShelper(vertices[i]);
            count++;
        }
    }
    return count;
}
