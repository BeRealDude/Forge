#pragma once
#include <chrono>
#include <string>

class Note
{
public:

	explicit Note(int noteId, const std::string& text, std::chrono::system_clock::time_point createdAt = std::chrono::system_clock::now());

	int GetId() const;

	const std::string& GetText() const;

	std::chrono::system_clock::time_point GetCreatedAt() const;

private:

	std::chrono::system_clock::time_point created_at;
	int id;
	std::string text;
};