#ifdef _WIN32
#define NOMINMAX // Запрет на объявление макросов min и max
#include <Windows.h>
#endif

#include "CommandsHandle.h"

int main()
{
	#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	#endif

	CommandsHandle app;
	app.Run();	

	return 0;
}