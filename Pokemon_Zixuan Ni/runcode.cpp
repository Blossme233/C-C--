#include "Game_function.cpp"

int main() {
    cout << "Before you begin this game, you need to understand this is only a "
            "kind of demo, some of game features are only showed in the code "
            "itself. Please read the code after playing this.";
    Sleep(1500);
    cout << endl;
    cout << "Loading map..." << endl;
    readmap();
    Sleep(1000);
    cout << "Map loaded;" << endl;
    cout << "Loading Pokémon and Gyms..." << endl;
    initialize_poke();
    initialize_gym(5);
    Sleep(2000);
    cout << "Pokémon and Gyms loaded." << endl;
    // printmap();
    Sleep(1500);
    cout << "Your amazing journey will begin in 3 seconds..." << endl;
    for (int i = 3; i >= 1; i--) {
        cout << i << "..." << endl;
        Sleep(1000);
    }
    greeting();
    while (1) {
        if (badge == 6) {
            cout << "You won!" << endl;
            break;
        }
        turn_Options();
        if (quit == true) {
            break;
        }
        Sleep(1000);
        if (check_points() == false) {
            check_encounter();
        }
    }
    Sleep(150);
    record();
    print_record();
}