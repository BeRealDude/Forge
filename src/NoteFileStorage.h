#pragma once

#include <vector>
#include <string>
#include "Note.h" 

class NoteFileStorage {

public:
	NoteFileStorage();

	void Read(std::vector<Note>& list) const;

	void Write(const std::vector<Note>& list) const;

private:

	std::string fileName = "notes.txt";
	std::string tempPath = fileName + ".temp";

	void Initialize() const;
};