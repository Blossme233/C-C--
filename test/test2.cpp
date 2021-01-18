#include <windows.h>

#include <cctype>
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

#include "cfloat"
using namespace std;

class RaceTrack {
   private:
    vector<double> speeds;
    vector<string> models;
    string name;

   public:
    RaceTrack();
    RaceTrack(string raceName);
    double calcAvgSpeed();
    int countAvailable(double minSpeed);
    int counAvailableModels(string model);
    bool addCar(double topSpeed, string carModel);
};