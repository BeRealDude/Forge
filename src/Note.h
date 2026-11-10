#pragma once
#include <chrono>
#include <string>

class Note
{
public:

	explicit Note(int noteId, const std::string& text);

	int GetId() const;

	const std::string& GetText() const;

	const std::chrono::system_clock::time_point& GetCreatedAt() const;

private:

	std::chrono::system_clock::time_point created_at;
	int id;
	std::string text;
};