#pragma once
#include <iostream>
#include "Note.h"

enum class keysPrint { incorrectId, eof, incorrectCommand, commandIsNotDefined, itemWasNotFound, incorrectConfirm, inputError, menu, header };

class TextUI {

public:

	void Print(const keysPrint& key);

	void PrintHeader();

	void PrintMenu();

	void PrintNote(const Note& note);

	void ClearConsole();
};