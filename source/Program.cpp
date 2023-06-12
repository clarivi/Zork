#include <iostream>
#include <string>
#include "Game.h"

//This allows us to skip writing std::in front of standard operations like cout, string, array, etc
using namespace std;
using namespace Zork;


int main()
{

    cout << "Welcome to Zork!\n\n";

    Game game("Rooms.json");
    game.Run();

    cout << "\n";
}


