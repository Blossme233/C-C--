#include <iostream>

#include "ProducerConsumer.hpp"
using namespace std;

ProducerConsumer::ProducerConsumer() {
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty() {
    if (queueFront == queueEnd) {
        return true;
    }
    return false;
}

bool ProducerConsumer::isFull() {
    if (queueEnd == queueFront - 1) {
        return true;
    }
    return false;
}

void ProducerConsumer::enqueue(string item) {
    if (!isFull()) {
        queue[queueEnd] = item;
        queueEnd++;
        queueEnd %= SIZE;
    } else {
        cout << "Queue full, cannot add new item" << endl;
    }
}
void ProducerConsumer::dequeue() {
    if (!isEmpty()) {
        for(int i = 0;i < queueEnd - 1;i++){
        queue[i] = queue[i + 1];
        }
        queueEnd--;
    } else {
        cout << "Queue empty, cannot dequeue an item" << endl;
    }
}

int ProducerConsumer::queueSize() {
    if (isEmpty()) {
        return 0;
    }
    return queueEnd;
}

string ProducerConsumer::peek() {
    if (isEmpty()) {
        cout << "Queue empty, cannot peek" << endl;
    } else {
        return queue[queueFront];
    }
}