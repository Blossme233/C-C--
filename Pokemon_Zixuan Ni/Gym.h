#ifndef GYM_H
#define GYM_H
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Pokemons.h"
using namespace std;

/**
 * @brief  the Gym class reference
 * @note   
 * @retval None
 */
class Gym {
   private:
    string GymName;
    string Badge;
    Pokemon poke_gym[5];

   public:
    Gym();
    bool result();
    void afterFight(bool);
    void initialize_gym(int, Pokemon);
    void view();
    Pokemon choose(int);
};

#endif  // !GYM_H
