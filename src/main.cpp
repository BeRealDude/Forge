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

	explicit Note(string text)
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

	notesList.emplace_back(text_note);
}

void showListNotes(const vector<Note>& notesList)
{
	cout << "Список заметок:" << endl << endl;

	if (notesList.empty())
	{
		cout << "Заметок пока нет" << endl << endl;
		return;
	}

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

	bool isRunning = true;

	while (isRunning)
	{
		int userCommand = 0;

		if (!(cin >> userCommand))
		{

			if (cin.eof())
			{
				cout << endl << "Ввод завершён" << endl;
				break;
			}

			system("cls");
			cin.clear(); // сбросить флаги ошибок потока cin
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // отбрасывает элементы до достижения указанного количества или до разделителя

			printHeader();
			printMenu();

			cout << "Неверный ввод! Команды в виде символов и строк - не поддерживаются." << endl;

			continue;
		}

		// Удаляем остаток строки после числа.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");
		printHeader();
		printMenu();

		switch (userCommand)
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
			isRunning = false;
			break;
		default:
			cout << "Команда не определена!" << endl;
			break;
		}
	}

	return 0;
}