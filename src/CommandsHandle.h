#pragma once

#include <iostream>
#include "NoteRepository.h"
#include "InputHandle.h"
#include "TextUI.h"
//#include "NoteFileStorage.h"


class CommandsHandle {

public:

	void Run();

private:
	NoteRepository rep;
	InputHandle inputHandler;
	TextUI ui;
	//NoteFileStorage store;



	void AddNewNote();

	void ShowListNotes();

	void DeleteNote();
};