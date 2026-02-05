// Main μέσω της οποίας τρέχει το παιχνίδι
#include <iostream>
#include "Game.h"

int main()
{
    Game game;
    
    try
    {
        // Διαλέγουμε αρχείο χάρτι
        game.loadMap("map1.txt");
        game.run();
   
    } catch (const std::exception& e) {
        std::cerr << "Error:" << e.what() << std::endl;
        return 1;
    }

    return 0;
}