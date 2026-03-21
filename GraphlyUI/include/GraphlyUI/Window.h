#ifndef GRAPHLYUI_WINDOW_HEADER
#define GRAPHLYUI_WINDOW_HEADER

#include <windows.h>
#include <optional>
#include <memory>

#include "WindowSettings.h"
#include "GraphlyUIExports.h"

namespace GraphlyUI
{
	class GRAPHLYUI_API Window
	{
	public:
		Window(const WindowSettings& settings);
		Window(WindowSettings&& settings);
		Window(const Window& other) = delete;
		Window(Window&& other) = delete;
		~Window();

		[[nodiscard]] WindowSettings& GetWindowSettings() const;
		[[nodiscard]] int Run();

		Window& operator = (const Window& other) = delete;
		Window& operator = (Window&& other) = delete;

	private:
		struct WindowImpl;
		std::unique_ptr<WindowImpl> _impl{};
	};

	using WindowPtr       = std::unique_ptr<Window>;
	using WindowSharedPtr = std::shared_ptr<Window>;
}

#endif // GRAPHLYUI_WINDOW_HEADER
