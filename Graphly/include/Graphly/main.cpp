#include "App.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	Graphly::AppSettings settings{};
	settings.instance = hInstance;
	settings.nCmdShow = nCmdShow;
	settings.logFilePath = Graphly::App::GetCurrentPath() + "GraphlyLogs.txt";
	
	if (!Graphly::App::AlreadyRunning())
	{
		try
		{
			Graphly::App app(settings);
			return app.Run();
		}
		catch (const std::runtime_error& e)
		{
			return 1;
		}
	}

	return 0;
}