#pragma once

#include <fstream>
#include <string>
#include "Note.h" 


class NoteFileStorage {

public:
	NoteFileStorage();

	bool CheckExist();

	bool CheckEmpty();

	void Write(std::vector<Note>& list);

	void Read(std::vector<Note>& list);

	std::string CreateJson();

private:

	std::fstream file;
	std::string fileName = "notes.txt";

};