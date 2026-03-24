#ifndef GRAPHLY_APP_HEADER
#define GRAPHLY_APP_HEADER

#include "GraphlyWindow.h"
#include "Logger.h"
#include "MemoryTracker.h"
#include "../SystemMetrics.h"

#include <optional>
#include <memory>
#include <fstream>

namespace Graphly
{
	struct AppSettings final
	{
		HINSTANCE instance{};
		int nCmdShow{};
		std::optional<std::string> logFilePath{};
	};

	class App final
	{
	public:
		App(const AppSettings& settings);
		App(AppSettings&& settings);
		App(const App& other) = delete;
		App(App&& other) = delete;
		~App();

		static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		static bool AlreadyRunning();
		[[nodiscard]] int Run();

		static std::string GetCurrentPath();

		App& operator = (const App& other) = delete;
		App& operator = (App&& other) = delete;

	private:
		bool Initialize();

	private:
		// Members section
		AppSettings _settings{};
		static HANDLE _mutex;
		
		// Components
		MemoryTrackerPtr _memoryTracker{};
		LoggerPtr _logger{};

		// GraphlyUI Members
		GraphlyWindowPtr _window{};
	};
}

#endif // GRAPHLY_APP_HEADER
