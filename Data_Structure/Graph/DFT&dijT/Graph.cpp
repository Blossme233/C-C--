#include "Graph.hpp"

#include "queue"
using namespace std;

void Graph::addEdge(string v1, string v2, int num) {
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
            temp.weight = num;
            temp2.weight = num;
            vertices[index]->adj.push_back(temp2);
            vertices[i]->adj.push_back(temp);
        }
    }
}

void DFShelper(vertex* temp) {
    if (temp->visited == false) {
        temp->visited = true;
        cout << temp->name << " -> ";
        for (int i = 0; i < temp->adj.size(); i++) {
            DFShelper(temp->adj[i].v);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex) {
    vertex* temp = NULL;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == sourceVertex) {
            temp = vertices[i];
        }
    }
    vertex* pres = temp;
    for (int i = 0; i < pres->adj.size(); i++) {
        pres->adj[i].v->visited = false;
        DFShelper(temp);
    }
    cout << "DONE" << endl;
}

void DijkstraTraverse(vertex* n) {
    n->visited = true;

    for (int x = 0; x < (int)n->adj.size(); x++) {
        adjVertex edge = n->adj[x];
        if (edge.v->distance > (n->distance + edge.weight)) {
            edge.v->distance = n->distance + edge.weight;
            edge.v->pred = n;
        }
        if (!n->adj[x].v->visited) {
            DijkstraTraverse(n->adj[x].v);
        }
    }
}

int indexOf(vector<vertex*> vertices, string name) {
    int index1 = -1;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == name) {
            index1 = i;
        }
    }
    return index1;
}

int min(vector<vertex*> vertices) {
    int min = 99999999, min_index;

    for (int v = 0; v < vertices.size(); v++)
        if (vertices[v]->visited == false && vertices[v]->distance <= min) {
            min = vertices[v]->distance;
            min_index = v;
        }
    return min_index;
}

void Graph::dijkstraTraverse(string source) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i]->visited = false;
        vertices[i]->distance = 99999999;
        vertices[i]->pred = nullptr;
    }
    vertices[indexOf(vertices, source)]->distance = 0;
    for (int count = 0; count < vertices.size(); count++) {
        int u = min(vertices);
        vertices[u]->visited = true;
        for (int v = 0; v < vertices[u]->adj.size(); v++) {
            if (!vertices[u]->adj[v].v->visited &&
                vertices[u]->distance + vertices[u]->adj[v].weight <
                    vertices[u]->adj[v].v->distance) {
                vertices[u]->adj[v].v->pred = vertices[u];
                vertices[u]->adj[v].v->distance =
                    vertices[u]->distance + vertices[u]->adj[v].weight;
            }
        }
    }
}

void printPath(vertex* n) {
    if (n->pred != NULL) {
        printPath(n->pred);
    }
    cout << n->name << " -> ";
}

void printPath(vector<vertex*> vertices, int index) {
    if (vertices[index]->pred != nullptr) {
        printPath(vertices, indexOf(vertices, vertices[index]->pred->name));
        cout << vertices[index]->name << " -> ";
    } else {
        cout << vertices[index]->name << " -> ";
    }
}

void Graph::shortestPath(string s1, string s2) {
    dijkstraTraverse(s1);
    printPath(vertices, indexOf(vertices, s2));
    cout << "DONE "
         << "[" << vertices[indexOf(vertices, s2)]->distance << "]" << endl;
}
