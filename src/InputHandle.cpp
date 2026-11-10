#include "InputHandle.h"

inputStatus InputHandle::ReadLine(std::istream& input, std::string& text)
{
	std::string line;

	if (!(std::getline(input, line)))
	{
		if (input.eof())
			return inputStatus::end_of_input;

		return inputStatus::input_error;
	}

	text = std::move(line);

	return inputStatus::ok;
}