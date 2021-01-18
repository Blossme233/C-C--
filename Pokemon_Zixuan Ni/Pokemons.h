#ifndef POKEMON_H
#define POKEMON_H

#include <string>
using namespace std;

/**
 * @brief  the Pokemon class reference
 * @note   
 * @retval None
 */
class Pokemon {
   private:
    string PokeName;
    int HP;
    int maxHP;
    int Attack;
    int Defense;
    int Speed;
    int Max;
    int experience;
    int level;
    string type1;
    string type2;
    int row, column;

   public:
    Pokemon();
    void setPokemon(string, int, int, int, int, int, int, int, string, string);
    int change_HP(int);
    int change_experience(int);
    void level_UP();
    string getname();
    int getHP();
    void print_Stats();
    bool check_Active();
    bool set_position(int, int);
    int get_position();
    int get_row();
    int get_column();
    void heal();
    int get_speed();
    int get_attack();
    int get_defense();
};

#endif