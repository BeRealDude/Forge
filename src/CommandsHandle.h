#pragma once

#include <iostream>
#include "NoteRepository.h"
#include "InputHandle.h"
#include "TextUI.h"

class CommandsHandle {

public:

	void Run();

private:
	NoteRepository rep;
	InputHandle inputHandler;
	TextUI ui;

	void AddNewNote();

	void ShowListNotes();

	void DeleteNote();
};