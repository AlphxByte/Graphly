#include "Graphly/Application/Application.h"
#ifdef _DEBUG
#include "Graphly/MemoryTracker.h"
#endif // _DEBUG

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	Graphly::ApplicationSettings settings{};
	settings.instance = hInstance;
	settings.nCmdShow = nCmdShow;
	settings.logFilePath = Graphly::Application::GetCurrentPath() + "GraphlyLogs.txt";

	// Exit early if app is already opened
	if (Graphly::Application::AlreadyRunning())
		return 0;
	
	try
	{
	#ifdef _DEBUG
		Graphly::MemoryTracker memoryTracker{};
	#endif // _DEBUG
		int returnCode;

		// Application scope
		{
			Graphly::Application application(settings);
			returnCode = application.Run();
		}

		return returnCode;
	}
	catch (const std::runtime_error&)
	{
		return 1;
	}

	return 0;
}