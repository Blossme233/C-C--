#include <iostream>

#include "RPNCalculator.hpp"
using namespace std;

RPNCalculator::RPNCalculator() { stackHead = NULL; }

RPNCalculator::~RPNCalculator() {
    if (!isEmpty()) {
        while (stackHead->next != NULL) {
            pop();
        }
        pop();
    }
    stackHead = NULL;
}

void RPNCalculator::push(float num) {
    Operand *temp = new Operand;
    if (isEmpty()) {
        temp->number = num;
        stackHead = temp;
    } else {
        temp->number = num;
        temp->next = stackHead;
        stackHead = temp;
    }
}

void RPNCalculator::pop() {
    if (isEmpty()) {
        cout << "Stack empty, cannot pop an item." << endl;
    } else {
        Operand *temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
}

Operand *RPNCalculator::peek() {
    if (isEmpty()) {
        cout << "Stack empty, cannot peek." << endl;
        return NULL;
    } else {
        return stackHead;
    }
}

bool RPNCalculator::compute(string symbol) {
    if (symbol == "*" || symbol == "+") {
        if (isEmpty()) {
            cout << "err: not enough operands" << endl;
            return false;
        } else {
            Operand *temp = new Operand;
            temp = stackHead;
            if (stackHead->next == NULL) {
                cout << "err: not enough operands" << endl;
                return false;
            } else {
                if (symbol == "+") {
                    float calNumber =
                        stackHead->number + stackHead->next->number;
                    stackHead->next->number = calNumber;
                } else {
                    float calNumber =
                        float(stackHead->number * stackHead->next->number);
                    stackHead->next->number = calNumber;
                }
                stackHead = stackHead->next;
                delete temp;
            }
        }
    } else {
        cout << "err: invalid operation" << endl;
        return false;
    }
    return true;
}

bool RPNCalculator::isEmpty() {
    if (stackHead == NULL) {
        return true;
    }
    return false;
}