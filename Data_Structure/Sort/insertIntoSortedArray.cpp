#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int insertIntoSortedArray(float arr[], int new_Entreis, float new_Value) {
    int index = 0;
    if (new_Entreis < 100) {
        for (int i = 0; i < new_Entreis; i++) {
            index = i;
            if (new_Value > arr[i]) {
                break;
            }
        }
        for (int j = new_Entreis; j > index; j--) {
            arr[j] = arr[j - 1];
        }
        arr[index] = new_Value;
    }
    new_Entreis++;
    return new_Entreis;
}

int main(int argc, char **argv) {
    ifstream myfile;
    myfile.open(argv[1]);
    float array[100];
    int index = 0;
    for (int i = 0; i < 100; i++) {
        array[i] = 0;
    }
    if (myfile.is_open()) {
        string line;
        float temp;

        while (getline(myfile, line)) {
            temp = atof(line.c_str());
            insertIntoSortedArray(array, index + 1, temp);
            index++;
            for (int i = 0; i < index; i++) {
                cout << array[i];
                if (i != index - 1) {
                    cout << ',';
                }
            }

            cout << endl;
        }
    } else {
        cout << "Failed to open the file." << endl;
    }

    myfile.close();
}