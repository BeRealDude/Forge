#include "Note.h"

Note::Note(int noteId, const std::string& text, std::chrono::system_clock::time_point createdAt)
	: created_at(createdAt),
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

 std::chrono::system_clock::time_point Note::GetCreatedAt() const
{
	return created_at;
}