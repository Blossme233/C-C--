#include "Gym.h"
#include <cstdlib>

/**
 * @brief  the Gym class definition
 * @note
 * @retval
 */
Gym::Gym() {
    this->GymName = "";
    this->Badge = "";
}

void Gym::afterFight(bool result) {
    if (result == true) {
        cout << "You win the gym trainer and a badge! Congraduations!" << endl;
    } else {
        cout << "You did not win the badge. Please try again";
    }
}

void Gym::initialize_gym(int index, Pokemon inheritance) {
    this->poke_gym[index] = inheritance;
}

Pokemon Gym::choose(int index) { return poke_gym[index]; }

void Gym::view() { this->poke_gym[2].print_Stats(); }
