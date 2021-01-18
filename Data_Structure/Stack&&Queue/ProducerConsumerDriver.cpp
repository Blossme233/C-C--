/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include <iostream>
#include "ProducerConsumer.hpp"
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu() {
    cout << "*----------------------------------------*" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
    cout << "2. Consumer (Consume items from the queue)" << endl;
    cout << "3. Return the queue size and exit" << endl;
    cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[]) {
    ProducerConsumer temp;
    while (true) {
        menu();
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                cout << "Enter the number of items to be produced:" << endl;
                int number;
                cin >> number;
                cin.ignore();
                for (int i = 1; i <= number; i++) {
                    string items;
                    cout << "Item" << i << ":" << endl;
                    getline(cin, items);
                    temp.enqueue(items);
                }
                break;
            }
            case 2: {
                cout << "Enter the number of items to be consumed:" << endl;
                int number;
                cin >> number;
                cin.ignore();
                if (number > temp.queueSize()) {
                    int size = temp.queueSize();
                    for (int i = 0; i < size; i++) {
                        cout << "Consumed: " << temp.peek() << endl;
                        temp.dequeue();
                    }
                    cout << "No more items to consume from queue" << endl;
                } else {
                    for (int i = 0; i < number; i++) {
                        cout << "Consumed: " << temp.peek() << endl;
                        temp.dequeue();
                    }
                }
                break;
            }
            case 3: {
                cout << "Number of items in the queue:" << temp.queueSize()
                     << endl;
                break;
            }
        }
        if (choice == 3) {
            break;
        }
    }
}
