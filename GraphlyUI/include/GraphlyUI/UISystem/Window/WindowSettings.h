#ifndef GRAPHLYUI_WINDOW_SETTINGS_HEADER
#define GRAPHLYUI_WINDOW_SETTINGS_HEADER

#include "GraphlyMath/GraphlyMath.h"
#include "WindowFlags.h"

namespace GraphlyUI
{
	class Window;

	class GRAPHLYUI_API WindowStyle
	{
	public:
		WindowStyle() = default;
		WindowStyle(WindowStyleFlags styleFlags, WindowExStyleFlags exStyleFlags);
		WindowStyle(const WindowStyle& other);
		WindowStyle(WindowStyle&& other);
		~WindowStyle() = default;

		WindowStyle& SetStyleFlags(WindowStyleFlags flags);
		WindowStyle& SetExStyleFlags(WindowExStyleFlags flags);

		const WindowStyleFlags& GetStyleFlags() const;
		const WindowExStyleFlags& GetExStyleFlags() const;

		WindowStyle& operator = (const WindowStyle& other);
		WindowStyle& operator = (WindowStyle&& other);

	private:
		WindowStyleFlags styleFlags = WindowStyleFlags::OverlappedWindow | WindowStyleFlags::Visible;
		WindowExStyleFlags exStyleFlags = WindowExStyleFlags::None;

		friend class Window;
	};

	class GRAPHLYUI_API WindowIcon
	{
	public:
		WindowIcon() = default;
		WindowIcon(WindowIconFlags flags);
		WindowIcon(WindowIconFlags iconFlags, WindowIconFlags iconSmFlags);
		WindowIcon(HICON icon);
		WindowIcon(HICON icon, HICON iconSm);
		WindowIcon(const WindowIcon& other);
		WindowIcon(WindowIcon&& other);
		~WindowIcon();

		WindowIcon& SetIcon(HICON ic);
		WindowIcon& SetIconSm(HICON iconSm);
		WindowIcon& SetIconFlags(WindowIconFlags flags);
		WindowIcon& SetIconSmFlags(WindowIconFlags flags);

		const HICON& GetIcon() const;
		const HICON& GetIconSm() const;
		const WindowIconFlags& GetIconFlags() const;
		const WindowIconFlags& GetIconSmFlags() const;

		WindowIcon& operator = (const WindowIcon& other);
		WindowIcon& operator = (WindowIcon&& other);

	private:
		HICON LoadWindowIcon(WindowIconFlags flags);
		bool IsSystemIcon(HICON icon);

	private:
		HICON icon = LoadIcon(NULL, IDI_APPLICATION);
		HICON iconSm = LoadIcon(NULL, IDI_APPLICATION);
		WindowIconFlags iconFlags = WindowIconFlags::Application;
		WindowIconFlags iconSmFlags = WindowIconFlags::Application;
		bool isSystemIcon = true;
		bool isSystemIconSm = true;

		friend class Window;
	};

	class GRAPHLYUI_API WindowCursor
	{
	public:
		WindowCursor() = default;
		WindowCursor(WindowCursorFlags flags);
		WindowCursor(HCURSOR cursor);
		WindowCursor(const WindowCursor& other);
		WindowCursor(WindowCursor&& other);
		~WindowCursor();

		WindowCursor& SetCursor(HCURSOR cr);
		WindowCursor& SetFlags(WindowCursorFlags fl);

		const HCURSOR& GetCursor() const;
		const WindowCursorFlags& GetFlags() const;

		WindowCursor& operator = (const WindowCursor& other);
		WindowCursor& operator = (WindowCursor&& other);

	private:
		HCURSOR LoadWindowCursor(WindowCursorFlags flags);
		bool IsSystemCursor(HCURSOR cursor);

	private:
		HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
		WindowCursorFlags flags = WindowCursorFlags::Arrow;
		bool isSystemCursor = true;

		friend class Window;
	};

	class GRAPHLYUI_API WindowSettings
	{
	public:
		WindowSettings() = default;
		WindowSettings(const WindowSettings& other);
		WindowSettings(WindowSettings&& other);
		~WindowSettings() = default;

		WindowSettings& SetWindowProcedure(WNDPROC wndProc);
		WindowSettings& SetInstance(HINSTANCE hInstance);
		WindowSettings& SetCursor(const WindowCursor& windowCursor);
		WindowSettings& SetTitle(const std::wstring& windowTitle);
		WindowSettings& SetClassName(const std::wstring& windowClassName);
		WindowSettings& SetIcon(const WindowIcon& windowIcon);
		WindowSettings& SetPosition(const GraphlyMath::Vector2& windowPosition);
		WindowSettings& SetDimension(const GraphlyMath::Vector2& windowDimension);
		WindowSettings& SetStyle(const WindowStyle& windowStyle);
		WindowSettings& SetData(LPVOID data);
		WindowSettings& SetCmdShow(int nShow);
		WindowSettings& AllowMultipleInstances(bool multipleInst);

		const WNDPROC& GetWindowProcedure() const;
		const HINSTANCE& GetInstance() const;
		const WindowCursor& GetWindowCursor() const;
		const std::wstring& GetTitle() const;
		const std::wstring& GetWindowClassName() const;
		const WindowIcon& GetWindowIcon() const;
		const GraphlyMath::Vector2& GetWindowPosition() const;
		const GraphlyMath::Vector2& GetDimension() const;
		const WindowStyle& GetWindowStyle() const;
		const LPVOID GetData() const;
		const int GetCmdShow() const;
		const bool IsMultipleInstancesAllowed() const;

		WindowSettings& operator = (const WindowSettings& other);
		WindowSettings& operator = (WindowSettings&& other);

	private:
		WNDPROC procedure{};
		HINSTANCE instance{};
		WindowCursor cursor;
		std::wstring title = L"Application Window";
		std::wstring className = L"Application Window";
		WindowIcon icon;
		GraphlyMath::Vector2 position = {
			static_cast<float>(CW_USEDEFAULT),
			static_cast<float>(CW_USEDEFAULT)
		};
		GraphlyMath::Vector2 dimension{ 800, 600 };
		WindowStyle style;
		int nCmdShow{};
		bool multipleInstances = true;
		LPVOID data{};

		friend class Window;
	};
}

#endif // GRAPHLYUI_WINDOW_SETTINGS_HEADER
