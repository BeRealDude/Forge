#pragma once

#include <fstream>
#include <string>


class NoteFileStorage {

public:
	NoteFileStorage();

	bool CheckExist();

	bool CheckEmpty();

	void Write(int id, std::string text);

	void Read();

private:

	std::fstream file;
	std::string fileName = "notes.txt";

};