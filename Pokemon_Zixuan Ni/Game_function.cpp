#include <windows.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
#include "Center.h"
#include "Gym.h"
#include "Player.h"
#include "Pokemons.h"

/**
 * @brief  this file is all the definations of functions in the game,
 * GameOperater.cpp is the code runenr
 * @note   None
 * @retval None
 */

// Here are global variables for these functions
char map[25][16];
Pokemon poke[155];
Gym gym[14];
Player user;
char last_position;
bool quit = false;
Pokemon poke_player[5];
int total_points = 0;
int gymcount = 0;
int badge = 0;
Center center;

/**
 * @brief  the heal definition for the Center header
 * @note
 * @retval None
 */
void Center::heal() {
    for (int i = 0; i < 6; i++) {
        poke_player[i].heal();
    }
}

/**
 * @brief  the result definition for the Gym header
 * @note
 * @retval
 */
bool Gym::result() {
    // this part of code is to get the result of the player finish the fight in
    // the Gym
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (poke_gym[i].get_attack() < poke_player[i].get_attack()) {
            count++;
        }
    }
    if (count >= 4) {
        return true;
        badge++;
        total_points += 60;
    } else {
        return false;
    }
}

/**
 * @brief  print the battle menu(options)
 * @note
 * @retval None
 */
void battle_menu() {
    cout << "What do you want to do (pick 1, 2, or 3):" << endl
         << "1. Fight" << endl
         << "2. Switch Active Pokemon" << endl
         << "3. Run" << endl;
}

/**
 * @brief  put the Pokemap.txt into the global variable char map[25][16]
 * @note
 * @retval None
 */
void readmap() {
    ifstream myfile;
    myfile.open("mapPoke.txt");
    string line, letter;
    int i = 0, j = 0;
    while (getline(myfile, line)) {
        stringstream str(line);
        while (getline(str, letter, ',')) {
            map[i][j] = letter[0];
            j++;
        }
        if (j == 17) {
            i++;
            j = 0;
        }
    }
    myfile.close();
}

/**
 * @brief  print the 7*7 map around the player
 * @note
 * @retval None
 */
void printmap() {
    Sleep(1500);
    cout << "This is the map around you, @ is where you are" << endl;
    for (int i = user.get_row() - 3; i <= user.get_row() + 3; i++) {
        for (int j = user.get_column() - 3; j <= user.get_column() + 3; j++) {
            if (i == user.get_row() && j == user.get_column()) {
                cout << '@' << ' ';
            } else if (map[i][j] == 'p') {
                cout << '*' << ' ';
            } else if (map[i][j] == 'w') {
                cout << '~' << ' ';
            } else {
                cout << map[i][j] << ' ';
            }
        }
        cout << endl;
    }
}

/**
 * @brief  print the logo and ask player to choose a initial pokemon
 * @note
 * @retval None
 */
void greeting() {
    ifstream logo;
    logo.open("logo.txt");
    string line;
    while (getline(logo, line)) {
        cout << line << endl;
        Sleep(150);
    }
    logo.close();
    cout << endl;
    cout << "Welcome to Pokémon!" << endl;
    cout << "Please state your name: ";
    string name;
    getline(cin, name);
    user.setName(name);
    cout << "Welcome, " << user.getName() << "! "
         << "Before you can begin your Pokémon adventure,"
            " you must choose a starting Pokémon, courtesy of the Professor."
            "​Please choose from the following ​Pokémon​:"
         << endl;
    cout << "1. Bulbasaur" << endl
         << "2. Charmander" << endl
         << "3. Squirtle" << endl
         << "4. Pikachu" << endl;
    int choice;
    cin.sync();
    cin >> choice;
    while (choice > 4 || choice < 1) {
        cout << "Invalid choice. Please choose again." << endl;
        cin.sync();
        cin >> choice;
    }
    switch (choice) {
        case 1:
            user.set_position(13, 7, map[13][7]);
            poke_player[0] = poke[1];
            cout << "You choose Bulbasaur! Congraduations!" << endl;
            break;
        case 2:
            user.set_position(13, 8, map[13][8]);
            poke_player[0] = poke[4];
            cout << "You choose Charmander! Congraduations!" << endl;
            break;
        case 3:
            user.set_position(13, 9, map[13][9]);
            poke_player[0] = poke[7];
            cout << "You choose Squirtle! Congraduations!" << endl;
            break;
        case 4:
            user.set_position(13, 10, map[13][10]);
            poke_player[0] = poke[25];
            cout << "You choose Pikachu! Congraduations!" << endl;
            break;
        default:
            break;
    }
}

/**
 * @brief  put 151 pokemon into the global variable Pokemon poke[155]
 * @note
 * @retval None
 */
void initialize_poke() {
    string arr[150];
    ifstream myfile;
    myfile.open("PokeMons.txt");
    int i = 0;
    string line;
    string index, HP, Attack, Defense, Speed, Max;
    string name, type1, type2;
    string temp;
    while (getline(myfile, line)) {
        arr[i] = line;
        i++;
        stringstream str(line);
        getline(str, index, ',');
        getline(str, name, ',');
        getline(str, HP, ',');
        getline(str, Attack, ',');
        getline(str, Defense, ',');
        getline(str, Speed, ',');
        getline(str, Max, ',');
        getline(str, type1, ',');
        getline(str, type2, ',');
        poke[atoi(index.c_str())].setPokemon(
            name, atoi(HP.c_str()), atoi(Attack.c_str()), atoi(Defense.c_str()),
            atoi(Speed.c_str()), atoi(Max.c_str()), 0, 1, type1, type2);
    }
    myfile.close();
}

/**
 * @brief  initialize every trainer's 6 pokemon randomly
 * @note   use the srand() and rand()
 * @param  seed: take a random seed to initial the rand() function
 * @retval None
 */
void initialize_gym(unsigned seed) {
    int number;
    for (int i = 0; i < 14; i++) {
        srand(seed);
        for (int j = 0; j < 5; j++) {
            number = rand() % 151 + 1;
            gym[i].initialize_gym(j, poke[number]);
        }
        seed++;
    }
    // gym[7].view();
}

/**
 * @brief  initialize 20 random pokemon into random plains area in the map
 * @note
 * @param  seed: take a random seed to initial the rand() function
 * @retval None
 */
void set_wild(unsigned seed) {
    srand(seed);
    int number, column, row;
    bool found;
    int count = 0, i = 1;
    while (i <= 151) {
        number = rand() % 151 + 1;
        row = rand() % 25 + 1;
        column = rand() % 16 + 1;
        found = false;
        if (poke[number].get_position() != poke[i].get_position() ||
            user.get_position() != poke[number].get_position()) {
            found = true;
        }
        if (map[row][column] == 'p' && map[row][column] != 'G' &&
            map[row][column] != 'C' && found == true) {
            poke[number].set_position(row, column);
            count++;
        } else {
            row = rand() % 25 + 1;
            column = rand() % 16 + 1;
        }
        i++;
        if (count == 20) {
            break;
        }
    }
}

/**
 * @brief  print player's every active pokemon
 * @note
 * @retval None
 */
void print_active() {
    cout << "Your ACTIVE Pokémon is:";
    bool found = false;
    for (int i = 0; i < 6; i++) {
        if (poke_player[i].getname() != " " &&
            poke_player[i].check_Active() != false) {
            poke_player[i].print_Stats();
            found = true;
        }
    }
    if (found == false) {
        cout << "You have no Pokémon Active! Go to Pokémon Center right away."
             << endl;
    }
    cout << endl;
}

/**
 * @brief  use the equation in the rules.pdf to do the battle bettween two
 * pokemons
 * @note
 * @param  poke1: the player's pokemon
 * @param  poke2: the wild pokemon or trainers' pokemon
 * @retval return the pokemon which won
 */
Pokemon battle(Pokemon poke1, Pokemon poke2) {
    int A, D;
    while (poke1.getHP() <= 0 || poke2.getHP() <= 0) {
        srand(poke2.getHP());
        A = rand() % (poke1.get_attack() + 1);
        D = rand() % (poke2.get_defense() + 1);
        if (A > D) {
            poke2.change_HP(-(A - D));
        }
        Sleep(250);
        cout << poke1.getname() << " deals " << A - D << " damage" << endl;
        A = rand() % (poke2.get_attack() + 1);
        D = rand() % (poke1.get_defense() + 1);
        if (A > D) {
            poke1.change_HP(-(A - D));
        }
        Sleep(250);
        cout << poke2.getname() << " deals " << A - D << " damage" << endl;
    }
    if (poke1.getHP() > 0) {
        poke1.level_UP();
        cout << poke1.getname() << " win, and level up!." << endl;
        poke1.print_Stats();
        total_points += 20;
        return poke1;
    }
    if (poke2.getHP() > 0) {
        poke2.level_UP();
        cout << poke2.getname() << " win, and level up!." << endl;
        poke2.print_Stats();
        return poke2;
    }
    return poke1;
}

/**
 * @brief  check if there any encounter to a wild pokemon around player
 * @note
 * @retval None
 */
void check_encounter() {
    int index = 0;
    for (int z = 1; z <= 151; z++) {
        for (int i = user.get_row() - 2; i <= user.get_row() + 2; i++) {
            for (int j = user.get_column() - 2; j <= user.get_column() + 2;
                 j++) {
                if (i == poke[z].get_row()) {
                    if (j == poke[z].get_column()) index = z;
                }
            }
        }
    }
    if (index != 0) {
        int number;
        cout << "You ran into a wild Pokémon!" << endl;
        poke[index].print_Stats();
        cout << endl;
        print_active();
        bool valid = false;
        battle_menu();
        while (valid == false) {
            int choice;
            cin.sync();
            cin >> choice;
            switch (choice) {
                case 1: {
                    if (poke_player[1].getname() == "") {
                        poke_player[1] = poke[index];
                        total_points = 10;
                        Sleep(1000);
                        cout << "This Pokémon joins your team!(cuz u r so weak "
                                "right now:("
                             << endl;
                    } else {
                        srand(index);
                        number = rand() % 10 + 1;
                        if (number > 4) {
                            battle(poke_player[0], poke[index]);
                        } else {
                            cout << "This wild Pokemon flee!" << endl;
                        }
                    }
                    valid = true;
                    break;
                }
                case 2: {
                    for (int i = 0; i < 6; i++) {
                        poke_player[i].print_Stats();
                    }
                    cout << "Which one do you want to change?" << endl;
                    while (cin >> choice) {
                        if (choice >= 0 && choice <= 5 &&
                            poke_player[choice].check_Active() == true) {
                            break;
                        } else {
                            cout << "Invalid Option! Choose again." << endl;
                        }
                    }

                    cout << "You switched to " << endl;
                    poke_player[choice].print_Stats();
                    valid = true;
                    break;
                }
                case 3: {
                    cout << "You successfully escape!" << endl;
                    valid = true;
                    break;
                }
                default: {
                    cout << "Invalid Option! Choose again." << endl;
                    break;
                }
            }
        }
    }
}

/**
 * @brief  check if player arrive a Gym or a Pokemon Center
 * @note
 * @retval return there is a Gym, Center or neither
 */
bool check_points() {
    if (map[user.get_row()][user.get_column()] == 'G') {
        cout << "You go into a gym, let's battle!" << endl;
        gym[gymcount].afterFight(gym[gymcount].result());
        return true;
    } else if (map[user.get_row()][user.get_column()] == 'C') {
        cout << "You go into a Pokemon center! All your pokemons are healed!"
             << endl;
        return true;
        center.heal();
        for (int i = 0; i < 6; i++) {
            if (poke_player[i].getname() != "") {
                poke_player[i].print_Stats();
            }
        }
    }
    return false;
}

/**
 * @brief  every turn options, include the function that define above
 * @note
 * @retval None
 */
void turn_Options() {
    int seed = 10;
    set_wild(seed);
    seed++;
    printmap();
    Sleep(2000);
    cout << "The sun is shining,​ " << user.getName()
         << "! It’s a beautiful day,we have " << user.getPokeballs()
         << "Pokéball left​ and your ​Pokémon are strong." << endl
         << "Please choose from the following options:" << endl
         << "1. Travel" << endl
         << "2. Rest" << endl
         << "3. Try your luck" << endl
         << "4. Quit the game" << endl;
    bool valid = false;
    while (valid == false) {
        cin.sync();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Please pick a travel direction." << endl
                     << "1.North" << endl
                     << "2.South" << endl
                     << "3.East" << endl
                     << "4.West" << endl;
                while (valid == false) {
                    int direction;
                    cin.sync();
                    cin >> direction;
                    if (direction == 1 &&
                        map[user.get_row() + 1][user.get_column()] != 'w' &&
                        user.get_column() >= 0) {
                        user.set_position(
                            user.get_row() + 1, user.get_column(),
                            map[user.get_row() + 1][user.get_column()]);
                        valid = true;
                        cout << "You just moved one step to North!" << endl;
                    } else if (direction == 2 &&
                               map[user.get_row() - 1][user.get_column()] !=
                                   'w' &&
                               user.get_column() < 25) {
                        user.set_position(
                            user.get_row() - 1, user.get_column(),
                            map[user.get_row() - 1][user.get_column()]);
                        valid = true;
                        cout << "You just moved one step to South!" << endl;

                    } else if (direction == 3 &&
                               map[user.get_row()][user.get_column() + 1] !=
                                   'w' &&
                               user.get_column() < 16) {
                        user.set_position(
                            user.get_row(), user.get_column() + 1,
                            map[user.get_row()][user.get_column()] + 1);
                        valid = true;
                        cout << "You just moved one step to East!" << endl;

                    } else if (direction == 4 &&
                               map[user.get_row()][user.get_column() - 1] !=
                                   'w' &&
                               user.get_column() >= 0) {
                        user.set_position(
                            user.get_row(), user.get_column() - 1,
                            map[user.get_row()][user.get_column()] - 1);
                        valid = true;
                        cout << "You just moved one step to West!" << endl;

                    } else {
                        cout << "Invalid Option because you choose a invalid "
                                "choice or the direction you choose is "
                                "invalid. Please choose again."
                             << endl;
                    }
                }
                Sleep(500);
                break;
            }
            case 2: {
                if (user.getPokeballs() > 0) {
                    for (int i = 0; i < 6; i++) {
                        if (poke[i].getname() != " ") {
                            poke_player[i].change_HP(1);
                        }
                    }
                    user.change_Pokeballs(-1);
                    cout << "You took a rest! All of your Pokémons increase "
                            "their "
                            "HP by 1, and your Pokéballs reduce 1."
                         << endl;
                    valid = true;
                } else {
                    cout << "You take a rest but no Pokémons get healed "
                            "because you have no Pokéballs!"
                         << endl;
                }
                Sleep(500);
                break;
            }
            case 3: {
                int index = -1;
                for (int i = 1; i <= 151; i++) {
                    if (poke[i].get_column() != 500) {
                        if ((poke[i].get_row() == user.get_row() ||
                             poke[i].get_row() < user.get_row() + 3 ||
                             poke[i].get_row() > user.get_row() - 3) &&
                            (poke[i].get_column() == user.get_column() ||
                             poke[i].get_column() < user.get_column() + 3 ||
                             poke[i].get_column() > user.get_column() - 3)) {
                            index = i;
                        }
                    }
                }
                if (index == -1) {
                    cout
                        << "It seems no Pokémon around you, try your luck next "
                           "time!"
                        << endl;
                    cout << endl;
                } else {
                    cout << "You find a " << poke[index].getname()
                         << " around you! Let's try to catch!" << endl;
                    srand(index);
                    int number = rand() % 10 + 1;
                    if (number > 5) {
                        // Catch;
                        cout << "Got it!" << endl;
                        cout << endl;
                    } else {
                        cout << "It seems this Pokémon does not like you, you "
                                "did not catch it for free this time! Try next "
                                "time!"
                             << endl;
                        cout << endl;
                    }
                }
                Sleep(700);
                valid = true;
                break;
            }
            case 4: {
                cout << "Thanks for playing this game! Good Bye!" << endl;
                quit = true;
                valid = true;
                break;
            }
            default: { cout << "Invalid Option! Please Choose again." << endl; }
        }
    }
}

/**
 * @brief  take the record of this round of player
 * @note
 * @retval None
 */
void record() {
    cout << "Your record is processing..." << endl;
    Sleep(2000);
    ofstream myfile;
    myfile.open("resultsPokemon.txt");
    myfile << user.getName() << ", Lose, " << total_points << "pts" << endl;
    myfile << endl;
    myfile.close();
    cout << "History records are below: " << endl;
}

/**
 * @brief  print the record of previous player(s)
 * @note
 * @retval None
 */
void print_record() {
    ifstream read("resultsPokemon.txt");
    string line;
    while (getline(read, line)) {
        cout << line << endl;
    }
    read.close();
}