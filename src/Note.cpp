#include "Note.h"

Note::Note(int noteId, const std::string& text)
	: created_at(std::chrono::system_clock::now()),
	id(noteId),
	text(text)
{
}

int Note::GetId() const
{
	return id;
}

const std::string& Note::GetText() const
{
	return text;
}

const std::chrono::system_clock::time_point& Note::GetCreatedAt() const
{
	return created_at;
}