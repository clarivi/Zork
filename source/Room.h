#pragma once

#include <string>

namespace Zork
{
	class Room final
	{
	public:
		// Rule of six special methods - Constructor, Destructor, Copy constructor & Move Construtor, Copy operator & Move Operator
		Room() = delete;
		~Room() = default;
		Room(const Room&) = default;
		Room(Room&&) = default;
		Room& operator=(const Room&) = default;
		Room& operator=(Room&&) = default;
		
		//Parameterized constructor
		Room(const std::string& name, const std::string& description = "");

		//defining getters & setters 
		const std::string& Name() const;
		void SetName(const std::string& description);

		const std::string& Description() const;
		void SetDescription(const std::string& description);

	private:
		//variables - keep private to ensure they aren't messed with directly & to avoid ambiguity
		std::string  _name;
		std::string _description;
	};
}