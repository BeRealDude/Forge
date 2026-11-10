#ifdef _WIN32
#define NOMINMAX // Запрет на объявление макросов min и max
#include <Windows.h>
#endif

#include "CommandsHandle.h"

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