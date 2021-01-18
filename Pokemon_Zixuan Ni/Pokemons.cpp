#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include "Pokemons.h"

/**
 * @brief  the Pokemon class definition
 * @note   
 * @retval 
 */

Pokemon::Pokemon() {
    this->PokeName = "";
    this->HP = 0;
    this->maxHP = 0;
    this->Attack = 0;
    this->Defense = 0;
    this->Speed = 0;
    this->Max = 0;
    this->experience = 0;
    this->level = 0;
    this->type1 = "";
    this->type2 = "";
    this->row = 500;
    this->column = 500;
}

void Pokemon::setPokemon(string PokeName, int HP, int Attack, int Defense,
                         int Speed, int Max, int exp, int level, string type1,
                         string type2) {
    // use this part of cade to put data int the txt to initialize pokemon's
    // element
    this->PokeName = PokeName;
    this->HP = HP;
    this->maxHP = HP;
    this->Attack = Attack;
    this->Defense = Defense;
    this->Speed = Speed;
    this->Max = Max;
    this->experience = exp;
    this->level = level;
    this->type1 = type1;
    this->type2 = type2;
}

int Pokemon::change_HP(int changeHP) {
    // use this part of code to change the hp of a pokemon after a fight
    this->HP += changeHP;
    return this->HP;
}

int Pokemon::change_experience(int changeExp) {
    // use this part of code to change the experience
    this->experience = changeExp;
    return this->experience;
}

void Pokemon::level_UP() {
    // use the level up function to change the data
    if (this->Max <= this->Attack) {
        this->Attack += 2;
    }
    if (this->Max <= Defense) {
        this->Defense += 2;
    }
    this->HP += 2;
    this->maxHP += 2;
    this->Speed += 2;
    this->level += 1;
}

string Pokemon::getname() { return this->PokeName; }

int Pokemon::getHP() { return this->HP; }

void Pokemon::print_Stats() {
    // get the stats of each Pokemon
    cout << "Name: " << this->PokeName << ',' << "HP: " << this->HP << ','
         << "A: " << this->Attack << ',' << "D: " << this->Defense << ','
         << "S: " << this->Speed << ',' << "M: " << this->Max << endl;
}

bool Pokemon::check_Active() {
    if (this->getHP() > 0) {
        return true;
    } else {
        return false;
        ;
    }
}

bool Pokemon::set_position(int row, int column) {
    this->row = row;
    this->column = column;
    if (this->row == 500 || this->column == 500) {
        return false;
    } else {
        return true;
    }
}

int Pokemon::get_position() {
    return (this->row + 2) * (this->column * this->column);
}

int Pokemon::get_row() { return this->row; }

int Pokemon::get_column() { return this->column; }

void Pokemon::heal() { this->HP = this->maxHP; }

int Pokemon::get_attack() { return this->Attack; }

int Pokemon::get_speed() { return this->Speed; }

int Pokemon::get_defense() { return this->Defense; }