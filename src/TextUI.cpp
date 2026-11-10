#include "TextUI.h"

void TextUI::Print(const keysPrint& key)
{
	switch (key)
	{
	case keysPrint::incorrectId: std::cout << "Неверный ввод. id должен быть целым числом\n"; break;
	case keysPrint::eof: std::cout << "\nВвод завершён. Программа будет закрыта.\n"; break;
	case keysPrint::incorrectCommand: std::cout << "Неверный ввод. Допускаются только числовые значения.\n"; break;
	case keysPrint::commandIsNotDefined: std::cout << "Команда не определена.\n"; break;
	case keysPrint::itemWasNotFound: std::cout << "Элемент не найден.\n"; break;
	case keysPrint::incorrectConfirm: std::cout << "Неверный ввод. Введите <Y> или <N>\n"; break;
	case keysPrint::inputError: std::cout << "Не удалось прочитать ввод. Программа будет закрыта\n"; break;
	case keysPrint::menu: PrintMenu(); break;
	case keysPrint::header: PrintHeader(); break;
	default: std::cout << "Передан неизвестный тип ошибки\n";
	};
}

void TextUI::PrintHeader()
{
	std::cout << "\n"
		"    **************************************\n"
		"    **********  ~ ~ Forge ~ ~  ***********\n"
		"    **************************************\n\n";
}

void TextUI::PrintMenu()
{
	std::cout << "    1 - Добавить новую заметку\n"
		"    2 - Просмотреть список заметок\n"
		"    3 - Удалить заметку\n"
		"    0 - Закрыть Forge\n\n";
}

void TextUI::PrintNote(const Note& note)
{
	std::cout << "Информация о заметке:\n"
		<< "Время создания: " << note.GetCreatedAt() << '\n'
		<< "id: " << note.GetId() << '\n'
		<< "Текст: " << note.GetText() << "\n\n";
}

void TextUI::ClearConsole()
{
	system("cls");
}