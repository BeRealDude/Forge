#include "NoteRepository.h"
#include <algorithm>

void NoteRepository::Add(const std::string& text)
{
	notesList.emplace_back(nextId, text);
	++nextId;
}

const std::vector<Note>& NoteRepository::GetAll() const
{
	return notesList;
}

bool NoteRepository::DeleteById(int id)
{
	const std::vector<Note>::iterator it = FindById(id);

	if (it != notesList.end())
	{
		notesList.erase(it);
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<Note>::iterator NoteRepository::FindById(int id)
{
	return std::find_if(notesList.begin(), notesList.end(), [id](const Note& note)
		{
			return note.GetId() == id;
		});
}

std::vector<Note>& NoteRepository::GetNotesList()
{
	return notesList;
}

void NoteRepository::CalculateNextId()
{
	if (notesList.size() == 0) return;

	for (Note& item : notesList)
	{
		if (nextId <= item.GetId())
		{
			nextId = item.GetId();
			++nextId;
		}
	}
}