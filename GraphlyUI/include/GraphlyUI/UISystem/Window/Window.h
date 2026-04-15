#ifndef GRAPHLYUI_WINDOW_HEADER
#define GRAPHLYUI_WINDOW_HEADER

#include "WindowSettings.h"
#include "WindowEvent.h"
#include "../../GraphlyUIExports.h"

#include <windows.h>
#include <optional>
#include <memory>
#include <functional>

namespace GraphlyUI
{
	class GraphicsSystem;
	class UISystem;
	class WindowFactory;
	class Rectangle;

	using WindowFunction = std::function<void(const WindowEvent& e)>;

	class GRAPHLYUI_API Window
	{
	public:
		Window(const WindowSettings& settings);
		Window(WindowSettings&& settings);
		Window(const Window& other) = delete;
		Window(Window&& other) = delete;
		~Window();

		void SetCloseFunction(WindowFunction closeFunction);
		void SetMouseMoveFunction(WindowFunction mouseMoveFunction);
		void SetMinimizeFunction(WindowFunction minimizeFunction);
		void SetMaximizeFunction(WindowFunction maximizeFunction);
		void SetResizeFunction(WindowFunction resizeFunction);
		void OnClose(const WindowEvent& e);
		void OnMouseMove(const WindowEvent& e);
		void OnMinimize(const WindowEvent& e);
		void OnMaximize(const WindowEvent& e);
		void OnResize(const WindowEvent& e);

		template<typename T>
		static inline void SetWindowData(HWND hwnd, LPARAM lParam, T* data)
		{
			CREATESTRUCTW* pcsw = reinterpret_cast<CREATESTRUCTW*>(lParam);
			data = reinterpret_cast<T*>(pcsw->lpCreateParams);
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)data);
		}
		template<typename T>
		[[nodiscard]] static inline T* GetWindowData(HWND hwnd)
		{
			T* data = reinterpret_cast<T*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
			return data;
		}
		[[nodiscard]] Rectangle* GetRootElement() const;
		[[nodiscard]] HWND GetHWND() const;
		[[nodiscard]] const WindowSettings& GetSettings() const;

		Window& operator = (const Window& other) = delete;
		Window& operator = (Window&& other) = delete;

	private:
		void Initialize(GraphicsSystem* graphics_system);

		struct WindowImpl;
		std::unique_ptr<WindowImpl> _impl{};

		friend class UISystem;
		friend class WindowFactory;
		friend class Rectangle;
	};

	using WindowPtr = std::unique_ptr<Window>;
	using WindowSharedPtr = std::shared_ptr<Window>;
}

#endif // GRAPHLYUI_WINDOW_HEADER
