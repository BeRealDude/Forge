#include "CommandsHandle.h"

void CommandsHandle::Run()
{
	enum commands { exit_program = 0, add_new_note = 1, show_list_notes = 2, delete_note = 3 };

	bool isRunning = true;

	ui.ClearConsole();
	ui.Print(keysPrint::header);
	ui.Print(keysPrint::menu);

	while (isRunning)
	{
		int userCommand{};

		inputStatus status = inputHandler.ParseSymbol(std::cin, userCommand);

		if (status == inputStatus::end_of_input)
		{
			ui.Print(keysPrint::eof);
			break;
		}
		else if (status == inputStatus::invalid)
		{
			ui.ClearConsole();
			ui.Print(keysPrint::header);
			ui.Print(keysPrint::menu);
			ui.Print(keysPrint::incorrectCommand);
			continue;
		}
		else if (status == inputStatus::input_error)
		{
			ui.Print(keysPrint::inputError);
			break;
		}

		ui.ClearConsole();
		ui.Print(keysPrint::header);
		ui.Print(keysPrint::menu);

		switch (userCommand)
		{
		case commands::add_new_note:
			AddNewNote();
			break;
		case commands::show_list_notes:
			ShowListNotes();
			break;
		case commands::delete_note:
			DeleteNote();
			break;
		case commands::exit_program:
			isRunning = false;
			break;
		default:
			ui.Print(keysPrint::commandIsNotDefined);
			break;
		}
	}
}

void CommandsHandle::AddNewNote()
{
	std::cout << "Введите текст новой заметки:\n";
	std::string text;

	if (inputHandler.ReadLine(std::cin, text) != inputStatus::ok)
	{
		return;
	}

	rep.Add(text);
	ui.ClearConsole();
	ui.Print(keysPrint::header);
	ui.Print(keysPrint::menu);
}

void CommandsHandle::ShowListNotes()
{
	const std::vector<Note>& notes = rep.GetAll();

	if (notes.empty())
	{
		std::cout << "Заметок пока нет" << '\n' << '\n';
		return;
	}

	std::cout << "Список заметок:" << '\n' << '\n';

	for (const Note& note : notes)
	{
		ui.PrintNote(note);
	}
}

void CommandsHandle::DeleteNote()
{
	std::cout << "Введите id заметки, чтобы её удалить: " << '\n';

	int id{};

	inputStatus statusId = inputHandler.ParseSymbol(std::cin, id);

	if (statusId != inputStatus::ok)
	{
		if (statusId == inputStatus::invalid)
			ui.Print(keysPrint::incorrectId);

		return;
	}


	char confirm{};

	std::cout << "Вы действительно хотите удалить заметку?" << '\n';

	std::cout << " Введите <Y> или <N>" << '\n';

	inputStatus status = inputHandler.ParseSymbol(std::cin, confirm);

	if (status != inputStatus::ok)
	{
		if (status == inputStatus::invalid)
			ui.Print(keysPrint::incorrectConfirm);

		return;
	}

	if (confirm == 'Y' || confirm == 'y')
	{
		if (rep.DeleteById(id))
		{
			std::cout << "Заметка удалена!" << '\n';
		}
		else
		{
			ui.Print(keysPrint::itemWasNotFound);
		}
	}
	else if (confirm == 'N' || confirm == 'n')
	{
		std::cout << "Отмена удаления заметки пользователем." << '\n';
	}
	else
	{
		ui.Print(keysPrint::incorrectConfirm);
	}
}