#pragma once
#include<vector>
#include<string>
#include<sstream>

namespace Zork
{

	class Utility final
	{
	public:
		//vector (in this context) is a dynamic array, as seen in lists in Python  & arrayList in Java
		static inline std::vector<std::string> split(const std::string& s, char delimiter)
		{
		//this function takes a line of a file and splits it into two fields depending on the delimiter, putting the fields in a vector.
			std::stringstream inputStream(s);
			std::string item;
			std::vector<std::string> items;
			while (getline(inputStream, item, delimiter))
			{
				items.push_back(item);
			}

			return items;
		}
		
	};
}
