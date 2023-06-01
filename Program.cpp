
#include <iostream>
#include <string>
#include <algorithm>
#include "Commands.h"
#include <map>
#include <array>
#include "Room.h"

//This allows us to skip writing std::in front of standard operations like cout, string, array, etc
using namespace std;


namespace Zork
{
    inline char toupper(char c)
    {
        return static_cast<char>(::toupper(c));
    }
}

using namespace Zork;

//defining methods so that they are able to be referenced before the lines they are implemented in code 
Commands ToCommand(const string&);
bool Move(Commands command);

//array of array of rooms, which are just strings for now.
static const array<array<string, 3>, 3> Rooms
{{
    {"Foyer"s, "Kitchen"s, "Dining Room"s},
    {"Living Room"s, "Bedroom"s, "Bathroom"s},
    {"Game Room"s, "Laundry Room"s, "Porch"s}
}};

size_t locationColumn = 0;
size_t locationRow = 0;

int main()
{

    //a Map of Commands to Strings
    const map<Commands, string> directionMap
    {
        { Commands::North, "NORTH"s },
        { Commands::South, "SOUTH"s },
        { Commands::East, "EAST"s },
        { Commands::West, "WEST"s }
    };

    cout << "Welcome to Zork!\n\n";

    //default command set to unknown
    Commands command = Commands::Unknown;


    Room r("Foyer", "You are in the foyer.");

    //Game Loop
    while (true)
    {
        //prints current location based on 2D array of rooms
        cout << Rooms[locationRow][locationColumn] << "\n>";

        //takes input
        string inputString;
        cin >> inputString;
        command = ToCommand(inputString);
        if (command == Commands::Quit)
        {
            break;
        }
        string outputString;

        //hard coded cases -> outputs for now, but later will be dependant on the Room class and gamestate
        switch (command)
        {
        case Commands::Quit:
            outputString = "Thank you for playing!";
            break;

        case Commands::Look:
            outputString = "This is an open field west of a white house, with a boarded front door.\nA rubber mat saying 'Welcome to Zork' lies by the door.";
            break;

        //fallthrough switch statement - since none of these have a berak statement each case falls through to the next until there is a break.
        //Not optimal normally, but not terrible for starting out until they are properly defined later. It works but not good practice
        case Commands::North:
        case Commands::South:
        case Commands::East:
        case Commands::West:
            if (Move(command) == false)
            {
                outputString = "The way is shut! \n";
            }

            else outputString = "you moved " + directionMap.at(command);
            break;
        default:
            outputString = "Unrecognized command";
            break;
        }
        cout << outputString << "\n";
    }
    cout << "\n";
}

Commands ToCommand(const string& commandString)
//ToCommand uses another map, this time from the string to the command, to parse the user's input and outputs a command .
{
    static const map<string, Commands> commandMap
    {
        { "QUIT"s, Commands::Quit },
        { "LOOK"s, Commands::Look },
        { "NORTH"s, Commands::North },
        { "SOUTH"s, Commands::South },
        { "EAST"s, Commands::East },
        { "WEST"s, Commands::West }
    };

    string uppercaseString;

    uppercaseString.resize(commandString.size());
    //Transform (where to start, where to end, where to write to, how to transform each character in string)
    transform(commandString.begin(), commandString.end(), uppercaseString.begin(), Zork::toupper);

    auto mappedString = commandMap.find(uppercaseString);
    //use auto when defining complicated types (this would normally be a const_iterator but the compiler can do type inference for us)
    return mappedString != commandMap.end() ? mappedString->second : Commands::Unknown;
    // if mappedString is a valid command, take the second value of the pair in the map ( e.q. mappedString consists of QUIT, Commands::Quit). 
    // if it is not found than use Commands::Unknown
}

bool Move(Commands command)
//This move command uses the array of arrays to check if a move is valid (within the bounds of the 'house') and outputs a bool 
//uses a switch statement to cover each direction.
{
    bool isValidMove = true;
    switch (command)
    {
    case Commands::East:
        if (locationColumn < Rooms.size() - 1)
        {
            locationColumn++;
        }
        else isValidMove = false;
        break;

    case Commands::West:
        if (locationColumn > 0)
        {
            locationColumn--;
        }
        else isValidMove = false;
        break;

    case Commands::North:
        if (locationRow < Rooms[0].size() - 1)
        {
            locationRow++;
        }
        else isValidMove = false;
        break;

    case Commands::South:
        if (locationRow > 0)
        {
            locationRow--;
        }
        else isValidMove = false;
        break;

    }
    return isValidMove;
}


