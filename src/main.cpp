#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

class Note
{
public:
	Note()
		: created_at(system_clock::now()),
		id(++count)
	{
	}

	Note(string text)
		: created_at(system_clock::now()),
		id(++count),
		text(text)
	{
	}

	void GetInfo() const
	{
		cout << "Информация о заметке:" << endl
			<< "Время создания: " << created_at << endl
			<< "id: " << id << endl
			<< "Текст: " << text << endl
			<< endl;
	}

private:

	system_clock::time_point created_at;
	int id;
	string text;
	static int count;

	// для UI format("{:%d.%m.%Y %H:%M}", now_local);
};

int Note::count = 0;

enum state { off, on };

enum commands { exit_program, add_new_note, show_list_notes };

void printHeader()
{
	cout << endl;
	cout << "    **************************************" << endl;
	cout << "    **********  ~ ~ Forge ~  ~  **********" << endl;
	cout << "    **************************************" << endl
		<< endl;
}

void printMenu()
{
	cout << "1 - Добавить новую заметку" << endl;
	cout << "2 - Просмотреть список заметок" << endl;
	cout << "0 - Закрыть Forge" << endl << endl;
}

void addNewNote(vector<Note> &notesList)
{
	string text_note;
	cout << "Введите текст новой заметки: " << endl;

	getline(cin >> ws, text_note);

	notesList.push_back(text_note);
}

void showListNotes(const vector<Note>& notesList)
{
	cout << "Список заметок:" << endl << endl;

	for (const Note &note : notesList)
	{
		note.GetInfo();
	}

}

int main()
{
	#ifdef _WIN32
    SetConsoleCP(1251); // Установить кодировку для ввода
    SetConsoleOutputCP(1251); // Установить кодировку для вывода
	#endif

	system("cls");
	printHeader();
	printMenu();

	vector<Note> notesList;

	int state = state::on;

	int user_command;

	while (state)
	{
		cin >> user_command;

		if (cin.fail())
		{
			user_command = -1;

			cin.clear();
			cin.ignore();
		}

		system("cls");
		printHeader();
		printMenu();

		switch (user_command)
		{
		case commands::add_new_note:
			addNewNote(notesList);
			system("cls");
			printHeader();
			printMenu();
			break;
		case commands::show_list_notes:
			showListNotes(notesList);
			break;
		case commands::exit_program:
			state = state::off;
			break;
		case -1:
			cout << "Неверный ввод! Команды в виде строки - не поддерживаются." << endl;
			break;
		default:
			cout << "Команда не определена!" << endl;
		}
	}

	return 0;
}