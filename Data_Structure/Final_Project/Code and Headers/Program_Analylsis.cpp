// Member 1: Shancheng Huang
// Member 2: Zixuan Ni
#include <bits/stdc++.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "BST.hpp"
#include "LL.hpp"
#include "hash.hpp"
#include "string"

using namespace std;
using namespace std::chrono;

// random generator function
int randomfunc(int j) { return rand() % j; }

void randomShuffle(int list[]) {
    srand(unsigned(time(0)));
    vector<int> arr;

    // set some values:
    // It need to be 101
    for (int j = 1; j < 101; ++j)

        // 1 2 3 4 5 6 7 8 9
        arr.push_back(j);

    // using built-in random generator
    random_shuffle(arr.begin(), arr.end());

    // using randomfunc
    random_shuffle(arr.begin(), arr.end(), randomfunc);

    // put everything back to the list
    //
    for (int i = 0; i < 100; i++) {
        list[i] = arr[i];
    }
}

int first_100_mixed_data(
    int location, int randomNumber[], int temp[], int mixed_data[],
    int data[]) {  // Get the first 100 data from the source
    for (int i = location; i < location + 100; i++) {
        temp[i] = data[i];
    }

    // cearte 100 random & not repeating number
    randomShuffle(randomNumber);
    int x = 0;

    for (int i = 0; i < 100; i++) {
        x = randomNumber[i];
        mixed_data[i] = temp[x];
    }

    if (location == 40000) {
        cout << "Location has reach to the MAX" << endl;
    }

    // update the location
    return location + 100;
}

int split(string str, char s, string *arr, int size) {
    int num = 0;
    int len_w = 0;
    int i;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == s) {
            if (i > 0)  // make sure that it is not the first one
            {
                if (size > num)  // test whethere there has space on array
                {
                    if (len_w > 0)  // test the words is not ""
                    {
                        arr[num] = str.substr(i - len_w, len_w);
                        len_w = 0;
                        num++;
                    }
                } else {
                    num = -1;
                    break;
                }
                len_w = 0;
            }
        } else {
            len_w++;
        }
    }

    if (len_w > 0) {
        arr[num] = str.substr(i - len_w, len_w);
        num++;
    }

    if (num == 0) {
        arr[0] = str;
        num = 1;
    }

    if (str == "") {
        arr[0] = str;
        num = 0;
    }

    return num;
}

void readCsv(int arr[], string fileName) {
    ifstream fin(fileName);

    string temp;
    string data[40000];
    fin >> temp;

    split(temp, ',', data, 40000);

    for (int i = 0; i < 40000; i++) {
        arr[i] = stoi(data[i]);
    }
}

void returnTimingAsCSV(string str, double arr[]) {
    ofstream csv(str);
    for (int i = 0; i < 400; i++) {
        csv << arr[i] << ",";
    }
}

// g++ Program_Analylsis.cpp -o test; .\test.exe
int main(int argc, char const *argv[]) {
    double run_time;
    _LARGE_INTEGER time_start;  //开始时间
    _LARGE_INTEGER time_over;   //结束时间
    double dqFreq;              //计时器频率
    LARGE_INTEGER f;            //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    int testDataA[40000];
    int testDataB[40000];

    int temp[100];
    int mixed_data[100];
    int randomNumber[100];

    readCsv(testDataA, "dataSetA.csv");  // Open the file as read
    readCsv(testDataB, "dataSetB.csv");

    int location = 0;
    // Link list
    LL linkList_A;
    double linkList_insertTime_A[400];
    double linkList_searchTime_A[400];
    LL linkList_B;
    double linkList_insertTime_B[400];
    double linkList_searchTime_B[400];

    // Binary Search Tree
    BST bst_A;
    double BST_insertTime_A[400];
    double BST_searchTime_A[400];
    BST bst_B;
    double BST_insertTime_B[400];
    double BST_searchTime_B[400];

    // Hash table with chaining
    HashTable HT_chaining_A(40009);
    double hash_chaining_insertTime_A[400];
    double hash_chaining_searchTime_A[400];
    HashTable HT_chaining_B(40009);
    double hash_chaining_insertTime_B[400];
    double hash_chaining_searchTime_B[400];

    HashTable HT_linear_A(40009);
    double hash_linear_insertTime_A[400];  // Hash table with open addressing,
                                           // linear probing
    double hash_linear_searchTime_A[400];
    HashTable HT_linear_B(40009);
    double hash_linear_insertTime_B[400];
    double hash_linear_searchTime_B[400];

    HashTable HT_quadratic_A(40009);
    double hash_quadratic_insertTime_A[400];  // Hash table withopen addressing,
                                              // quadratic probing
    double hash_quadratic_searchTime_A[400];
    HashTable HT_quadratic_B(40009);
    double hash_quadratic_insertTime_B[400];
    double hash_quadratic_searchTime_B[400];

    for (int i = 0; i < 399; i++) {
        location = first_100_mixed_data(location, randomNumber, temp,
                                        mixed_data, testDataA);

        //
        // Linked List
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            linkList_A.insertNode(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        linkList_insertTime_A[i] = run_time;   // record times
                                               //
                                               // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            linkList_A.searchNode(linkList_A.returnHead(),
                                  mixed_data[x]);  // End timing
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        linkList_searchTime_A[i] = run_time;  // record times

        //
        // BST
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            bst_A.insert(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        BST_insertTime_A[i] = run_time;        // record times
                                               //
                                               // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            bst_A.search(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        BST_searchTime_A[i] = run_time;  // record times

        //
        // HashTable_chaining
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_chaining_A.insertItemLinkList(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_chaining_insertTime_A[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_chaining_A.searchItemLinkList(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_chaining_searchTime_A[i] = run_time;  // record times

        //
        // HashTable_Linear
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_linear_A.insertItemLprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_linear_insertTime_A[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_linear_A.searchItemLprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_linear_searchTime_A[i] = run_time;  // record times

        //
        // HashTable_chaining
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_quadratic_A.insertItemQprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_quadratic_insertTime_A[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_quadratic_A.searchItemQpobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_quadratic_searchTime_A[i] = run_time;  // record times

        cout << i << endl;
    }

    for (int i = 0; i < 399; i++) {
        location = first_100_mixed_data(location, randomNumber, temp,
                                        mixed_data, testDataB);

        //
        // Linked List
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            linkList_B.insertNode(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        linkList_insertTime_B[i] = run_time;   // record times
                                               //
                                               // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            linkList_B.searchNode(linkList_A.returnHead(),
                                  mixed_data[x]);  // End timing
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        linkList_searchTime_B[i] = run_time;  // record times

        //
        // BST
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            bst_B.insert(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        BST_insertTime_B[i] = run_time;        // record times
                                               //
                                               // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            bst_B.search(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        BST_searchTime_B[i] = run_time;  // record times

        //
        // HashTable_chaining
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_chaining_B.insertItemLinkList(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_chaining_insertTime_B[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_chaining_B.searchItemLinkList(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_chaining_searchTime_B[i] = run_time;  // record times

        //
        // HashTable_Linear
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_linear_B.insertItemLprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_linear_insertTime_B[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_linear_B.searchItemLprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_linear_searchTime_B[i] = run_time;  // record times

        //
        // HashTable_chaining
        //
        // Insert
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the insert
        {
            HT_quadratic_B.insertItemQprobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_quadratic_insertTime_B[i] = run_time;  // record times
        //
        // search
        QueryPerformanceCounter(&time_start);  //计时开始
        for (int x = 0; x < 100; x++)          // Do the search
        {
            HT_quadratic_B.searchItemQpobing(mixed_data[x]);
        }
        QueryPerformanceCounter(&time_over);  //计时结束
        run_time =
            1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        hash_quadratic_searchTime_B[i] = run_time;  // record times

        cout << i << endl;
    }

    returnTimingAsCSV("Linklist_insert_A.csv", linkList_insertTime_A);
    returnTimingAsCSV("Linklist_search_A.csv", linkList_searchTime_A);
    returnTimingAsCSV("BST_insert_A.csv", BST_insertTime_A);
    returnTimingAsCSV("BST_search_A.csv", BST_searchTime_A);
    returnTimingAsCSV("hash_chaining_insertTime_A.csv",
                      hash_chaining_insertTime_A);
    returnTimingAsCSV("hash_chaining_searchTime_A.csv",
                      hash_chaining_searchTime_A);
    returnTimingAsCSV("hash_linear_insertTime_A.csv", hash_linear_insertTime_A);
    returnTimingAsCSV("hash_linear_searchTime_A.csv", hash_linear_searchTime_A);
    returnTimingAsCSV("hash_quadratic_insertTime_A.csv",
                      hash_quadratic_insertTime_A);
    returnTimingAsCSV("hash_quadratic_searchTime_A.csv",
                      hash_quadratic_searchTime_A);

    // Data_b

    returnTimingAsCSV("Linklist_insert_B.csv", linkList_insertTime_B);
    returnTimingAsCSV("Linklist_search_B.csv", linkList_searchTime_B);
    returnTimingAsCSV("BST_insert_B.csv", BST_insertTime_B);
    returnTimingAsCSV("BST_search_B.csv", BST_searchTime_B);
    returnTimingAsCSV("hash_chaining_insertTime_B.csv",
                      hash_chaining_insertTime_B);
    returnTimingAsCSV("hash_chaining_searchTime_B.csv",
                      hash_chaining_searchTime_B);
    returnTimingAsCSV("hash_linear_insertTime_B.csv", hash_linear_insertTime_B);
    returnTimingAsCSV("hash_linear_searchTime_B.csv", hash_linear_searchTime_B);
    returnTimingAsCSV("hash_quadratic_insertTime_B.csv",
                      hash_quadratic_insertTime_B);
    returnTimingAsCSV("hash_quadratic_searchTime_B.csv",
                      hash_quadratic_searchTime_B);

    return 0;
}
