#pragma once
#include "Commands.h"
#include <string>
#include <array>
#include "Room.h"
#include <random>

namespace Zork
{


	inline char toupper(char c)
	{
		return static_cast<char>(::toupper(c));
	}

	Commands ToCommand(const std::string& commandString);

	class Game final
	{
	public:
		Game(const std::string& roomsFilename);
		bool Move(Commands command);
		void Run();
		const Room& CurrentRoom() const;
		void SpawnPlayer();



	private:
		std::array<std::array<Room, 3>, 3> _rooms
		{{
			{Room("Foyer"), Room("Kitchen"), Room("Dining Room")},
			{ Room("Living Room"), Room("Bedroom"), Room("Bathroom") },
			{ Room("Game Room"), Room("Laundry Room"), Room("Porch") },
			}};

		void InitializeDescriptions(const std::string& roomsFilename);

		static std::random_device _randomDevice;
		static std::default_random_engine _randomGenerator;
		static std::uniform_int_distribution<size_t> _uniformDistribution;

		size_t _locationColumn = 0;
		size_t _locationRow = 0;
	};

}