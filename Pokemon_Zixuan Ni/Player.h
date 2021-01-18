#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Pokemons.h"
using namespace std;

/**
 * @brief  the Player class reference
 * @note   
 * @retval None
 */
class Player {
   private:
    int num_Pokeballs;
    int num_Slots;
    string userName;
    int row, column;

   public:
    Player();
    string setName(string userName);
    int change_Pokeballs(int);
    string getName();
    int change_Slots(int);
    int getPokeballs();
    int getSlots();
    void stats();
    bool set_position(int, int, char);
    int get_position();
    int get_row();
    int get_column();
};

#endif