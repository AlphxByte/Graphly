#ifndef GRAPHLY_APPLICATION_HEADER
#define GRAPHLY_APPLICATION_HEADER

#include "Logger.h"
#include "GraphlyUI/GraphlyUIInclude.h"
#include "GraphlyMainWindow.h"
#include "../SystemMetrics.h"

#include <optional>
#include <memory>
#include <fstream>

namespace Graphly
{
	struct ApplicationSettings final
	{
		HINSTANCE instance{};
		int nCmdShow{};
		std::optional<std::string> logFilePath{};
	};

	class Application final
	{
	public:
		Application(const ApplicationSettings& settings);
		Application(ApplicationSettings&& settings);
		Application(const Application& other) = delete;
		Application(Application&& other) = delete;
		~Application();

		static LRESULT CALLBACK GraphlyMainWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		static bool AlreadyRunning();
		[[nodiscard]] int Run();

		static std::string GetCurrentPath();

		Application& operator = (const Application& other) = delete;
		Application& operator = (Application&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		// Members section
		ApplicationSettings _settings{};
		static HANDLE _mutex;
		
		// Components
		LoggerPtr _logger{};
		GraphlyUI::UISystemPtr _uiSystem{};

		// Owned by UISystem
		GraphlyMainWindow* _mainWindow{};
		GraphlyUI::Rectangle* _childElement{};
		GraphlyUI::Text* _secondChild{};
		GraphlyUI::Button* _button{};
	};
}

#endif // GRAPHLY_APPLICATION_HEADER
