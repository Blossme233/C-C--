#include <iostream>

#include "ProducerConsumer.hpp"
using namespace std;

ProducerConsumer::ProducerConsumer() {
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty() {
    if (queueEnd == 0) {
        return true;
    }
    return false;
}

bool ProducerConsumer::isFull() {
    if (queueEnd == 20) {
        return true;
    }
    return false;
}

void ProducerConsumer::enqueue(string item) {
    if (!isFull()) {
        queue[queueEnd] = item;
        queueEnd++;
    } else {
        cout << "Queue full, cannot add new item" << endl;
    }
}

void ProducerConsumer::dequeue() {
    if (!isEmpty()) {
        if (queueFront == queueEnd - 1) {
            queueFront = 0;
            queueEnd = 0;
        } else {
            queueFront++;
        }
    } else {
        cout << "Queue empty, cannot dequeue an item" << endl;
    }
}

int ProducerConsumer::queueSize() {
    return (queueEnd - queueFront) % (SIZE + 1);
}

string ProducerConsumer::peek() {
    if (isEmpty()) {
        cout << "Queue empty, cannot peek" << endl;
    } else {
        return queue[queueFront];
    }
}