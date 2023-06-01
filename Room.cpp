#include "Room.h"

namespace Zork
{
	Room::Room(const std::string& name, const std::string& description) : _name(name), _description(description) 
		//Use : -> initialize variables. If put in between the parenthesis, it constructs once then constructs again, the second time initializing
	{
	}
	//getters & setters implementation
	const std::string& Room::Name()
	{
		return _name;
	}
	void Room::SetName(const std::string& name)
	{
		_name = name;
	}

	const std::string& Room::Description()
	{
		return _description;
	}
	void Room::SetDescription(const std::string& description)
	{
		_description = description;
	}
}