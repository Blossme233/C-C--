#include "Player.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief  the Player class definition
 * @note
 * @retval
 */

Player::Player() {
    this->num_Pokeballs = 10;
    this->num_Slots = 6;
    this->userName = "";
    this->row = 0;
    this->row = 0;
}

string Player::setName(string UserName) {
    // in this part, ask user to input their own name
    this->userName = UserName;
    return this->userName;
}

int Player::change_Pokeballs(int balls) {
    // int this part of code, whenever player catch a pokemon, or rest, or
    // supply some new Pokeballs, this function will called
    this->num_Pokeballs += balls;
    return this->num_Pokeballs;
}

string Player::getName() { return this->userName; }

int Player::change_Slots(int slots) {
    // whenever the player catch a Pokemon
    // this function will be called
    this->num_Slots += slots;
    return this->num_Slots;
}

int Player::getSlots() { return this->num_Slots; }

int Player::getPokeballs() { return this->num_Pokeballs; }

void Player::stats() {
    // use the function to print the stats each turn
}

bool Player::set_position(int row, int column, char map) {
    if (map == 'w') {
        return false;
    } else {
        this->row = row;
        this->column = column;
        return true;
    }
}

int Player::get_position() {
    return (this->row + 2) * (this->column * this->column);
}

int Player::get_row() { return this->row; }

int Player::get_column() { return this->column; }