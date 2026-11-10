#pragma once
#include <string>
#include <sstream>

enum class inputStatus { ok, invalid, end_of_input, input_error };

class InputHandle {

public:

	inputStatus ReadLine(std::istream& input, std::string& text);

	template<typename T>
	inputStatus ParseSymbol(std::istream& input, T& value)
	{
		std::string line;
		T extrValue{};
		char leftoverChar{};

		if (!(std::getline(input, line)))
		{
			if (input.eof()) return inputStatus::end_of_input;

			return inputStatus::input_error;
		}

		std::istringstream lineStream(line);

		if (!(lineStream >> extrValue)) return inputStatus::invalid;

		if (lineStream >> leftoverChar)	return inputStatus::invalid;

		value = extrValue;

		return inputStatus::ok;
	}
};