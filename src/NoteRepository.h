#pragma once

#include "Note.h"
#include <string>
#include <vector>

#include "NoteFileStorage.h"

class NoteRepository
{
public:

	void Add(const std::string& text);

	const std::vector<Note>& GetAll() const;

	bool DeleteById(int id);

private:
	std::vector<Note> notesList;
	int nextId = 1;
	NoteFileStorage store;

	std::vector<Note>::iterator FindById(int id);
};