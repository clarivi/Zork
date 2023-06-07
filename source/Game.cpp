#include "Game.h"
#include "Commands.h"
#include <map>
#include <algorithm>
#include <iostream>


using namespace std;

namespace Zork
{
    Game::Game()
    {
        SpawnPlayer();
        InitializeDescriptions();
    }

    //random number generation 
    std::random_device Game::_randomDevice;
    std::default_random_engine Game::_randomGenerator(_randomDevice());
    std::uniform_int_distribution<size_t> Game::_uniformDistribution(0, 2);

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


        //a Map of Commands to Strings


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

    bool Game::Move(Commands command)
        //This move command uses the array of arrays to check if a move is valid (within the bounds of the 'house') and outputs a bool 
        //uses a switch statement to cover each direction.
    {
        bool isValidMove = true;
        switch (command)
        {
        case Commands::East:
            if (_locationColumn < _rooms.size() - 1)
            {
                _locationColumn++;
            }
            else isValidMove = false;
            break;

        case Commands::West:
            if (_locationColumn > 0)
            {
                _locationColumn--;
            }
            else isValidMove = false;
            break;

        case Commands::North:
            if (_locationRow < _rooms[0].size() - 1)
            {
                _locationRow++;
            }
            else isValidMove = false;
            break;

        case Commands::South:
            if (_locationRow > 0)
            {
                _locationRow--;
            }
            else isValidMove = false;
            break;

        }
        return isValidMove;
    }

    void Game::Run()
    {
        static const map<Commands, string> directionMap
        {
            { Commands::North, "NORTH"s },
            { Commands::South, "SOUTH"s },
            { Commands::East, "EAST"s },
            { Commands::West, "WEST"s }
        };
        //Game Loop
        while (true)
        {
            //prints current location based on 2D array of rooms
            cout << CurrentRoom().Name() << "\n>";

            //takes input
            string inputString;
            cin >> inputString;
            Commands command = ToCommand(inputString);
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
                outputString = CurrentRoom().Description();
                break;

                //fallthrough switch statement - since none of these have a berak statement each case falls through to the next until there is a break.
                //Not optimal normally, but not terrible for starting out until they are properly defined later. It functions but not good practice
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
    }
    const Room& Game::CurrentRoom() const
    {
        return _rooms[_locationRow][_locationColumn];
    }
    void Game::SpawnPlayer()
    {
        //uses random generator created earlier to put player in random room of the house
        _locationRow = _uniformDistribution(_randomGenerator);
        _locationColumn = _uniformDistribution(_randomGenerator);
    }

    void Game::InitializeDescriptions()
    {
        map<string, Room*> roomMap;
        for (auto& floor : _rooms)
            //range for loop - For each floor in _rooms --- makes map for us 
        {
            for (Room& room : floor)
            {
                roomMap[room.Name()] = &room;
            }
        }
        roomMap.at("Foyer"s)->SetDescription("There's a coat hook on the wall."s);
        roomMap.at("Kitchen"s)->SetDescription("You see a tidy, cozy kitchen."s);
        roomMap.at("Dining Room"s)->SetDescription("You see a table set for dinner."s);
        roomMap.at("Living Room"s)->SetDescription("You are in the living room."s);
        roomMap.at("Bedroom"s)->SetDescription("You see a bed, a dresser, and a mirror."s);
        roomMap.at("Bathroom"s)->SetDescription("You are in the bathroom. You see a toilet and a vanity."s);
        roomMap.at("Game Room"s)->SetDescription("There is a chess set on a table with two chairs on either side."s);
        roomMap.at("Laundry Room"s)->SetDescription("You see a washer and dryer."s);
        roomMap.at("Porch"s)->SetDescription("A rubber mat saying 'Welcome to Zork! lies by the door."s);
    }
}