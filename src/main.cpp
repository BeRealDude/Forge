#ifdef _WIN32
#define NOMINMAX // Запрет на объявление макросов min и max
#include <Windows.h>
#endif

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

enum commands { exit_program = 0, add_new_note = 1, show_list_notes = 2, delete_note = 3 };

enum class inputStatus { ok, invalid, end_of_input, input_error };

enum class keysPrint { incorrectId, eof, incorrectCommand, commandIsNotDefined, itemWasNotFound, incorrectConfirm, inputError, menu, header };

class Note
{
public:
	
	explicit Note(int noteId, const std::string& text)
		: created_at(std::chrono::system_clock::now()),
		id(noteId),
		text(text)
	{
	}

	int GetId() const
	{
		return id;
	}

	const std::string& GetText() const
	{
		return text;
	}

	const std::chrono::system_clock::time_point& GetCreatedAt() const
	{
		return created_at;
	}

private:

	std::chrono::system_clock::time_point created_at;
	int id;
	std::string text;
};

class NoteRepository
{
	public:

		void Add(const std::string& text)
		{
			notesList.emplace_back(nextId, text);
			++nextId;
		}

		const std::vector<Note>& GetAll() const
		{
			return notesList;
		}

		bool DeleteById(int id)
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
		

private:
	std::vector<Note> notesList;
	int nextId = 1;

	std::vector<Note>::iterator FindById(int id)
	{
		return std::find_if(notesList.begin(), notesList.end(), [id](const Note& note)
			{
				return note.GetId() == id;
			});
	}
};

class InputHandle {

public:

	inputStatus ReadLine(std::istream& input, std::string& text)
	{
		std::string line;

		if (!(std::getline(input, line)))
		{
			if (input.eof())
				return inputStatus::end_of_input;

			return inputStatus::input_error;
		}

		text = std::move(line);

		return inputStatus::ok;
	}

	template<typename T>
	inputStatus ParseSymbol(std::istream& input, T& value)
	{
		std::string line;
		T extrValue{};
		char leftoverChar{};

		if (!(std::getline(input, line)))
		{
			if (input.eof()) return inputStatus::end_of_input;

			return inputStatus::input_error;
		}

		std::istringstream lineStream(line);

		if (!(lineStream >> extrValue)) return inputStatus::invalid;

		if (lineStream >> leftoverChar)	return inputStatus::invalid;

		value = extrValue;

		return inputStatus::ok;
	}
};

class TextUI {

public:

	void Print(const keysPrint& key)
	{
		switch (key)
		{
		case keysPrint::incorrectId: std::cout << "Неверный ввод. id должен быть целым числом" << '\n'; break;
		case keysPrint::eof: std::cout << "\nВвод завершён. Программа будет закрыта." << '\n'; break;
		case keysPrint::incorrectCommand: std::cout << "Неверный ввод. Допускаются только числовые значения." << '\n'; break;
		case keysPrint::commandIsNotDefined: std::cout << "Команда не определена." << '\n'; break;
		case keysPrint::itemWasNotFound: std::cout << "Элемент не найден." << '\n'; break;
		case keysPrint::incorrectConfirm: std::cout << "Неверный ввод. Введите <Y> или <N>" << '\n'; break;
		case keysPrint::inputError: std::cout << "Не удалось прочитать ввод. Программа будет закрыта" << '\n'; break;
		case keysPrint::menu: PrintMenu(); break;
		case keysPrint::header: PrintHeader(); break;
		default: std::cout << "Передан неизвестный тип ошибки" << '\n';

		}
	}

	void PrintHeader()
	{
		std::cout << '\n';
		std::cout << "    **************************************" << '\n';
		std::cout << "    **********  ~ ~ Forge ~ ~  ***********" << '\n';
		std::cout << "    **************************************" << '\n'
			<< '\n';
	}

	void PrintMenu()
	{
		std::cout << "1 - Добавить новую заметку" << '\n';
		std::cout << "2 - Просмотреть список заметок" << '\n';
		std::cout << "3 - Удалить заметку" << '\n';
		std::cout << "0 - Закрыть Forge" << '\n' << '\n';
	}

	void PrintNote(const Note& note)
	{
		std::cout << "Информация о заметке:" << '\n'
			<< "Время создания: " << note.GetCreatedAt()<< '\n'
			<< "id: " << note.GetId() << '\n'
			<< "Текст: " << note.GetText() << '\n'
			<< '\n';
	}

	void ClearConsole()
	{
		system("cls");
	}
};

class CommandsHandle {

public:

	void Run()
	{

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

private:
	NoteRepository rep;
	InputHandle inputHandler;
	TextUI ui;

	void AddNewNote()
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

	void ShowListNotes()
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

	void DeleteNote()
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
};

int main()
{
	#ifdef _WIN32
    SetConsoleCP(1251); // Установить кодировку для ввода
    SetConsoleOutputCP(1251); // Установить кодировку для вывода
	#endif

	CommandsHandle app;
	app.Run();	

	return 0;
}