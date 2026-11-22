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

	try
	{
		CommandsHandle app;
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Ошибка Forge: " << e.what() << '\n';
		return 1;
	}

	return 0;
}