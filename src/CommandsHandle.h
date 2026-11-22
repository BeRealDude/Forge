#pragma once

#include <iostream>
#include "NoteRepository.h"
#include "InputHandle.h"
#include "TextUI.h"
#include "NoteFileStorage.h"


class CommandsHandle {

public:

	void Run();

private:
	NoteFileStorage store;
	NoteRepository rep;
	InputHandle inputHandler;
	TextUI ui;

	void LoadNotes();

	void AddNewNote();

	void ShowListNotes();

	void DeleteNote();
};