#include "../include/GraphlyUI/WindowSettings.h"

using namespace GraphlyUI;
using namespace GraphlyMath;

WindowStyle::WindowStyle(WindowStyleFlags styleFlags, WindowExStyleFlags exStyleFlags)
: styleFlags(styleFlags), exStyleFlags(exStyleFlags)
{}

WindowStyle::WindowStyle(const WindowStyle & other)
: styleFlags(other.styleFlags), exStyleFlags(other.exStyleFlags)
{}

WindowStyle::WindowStyle(WindowStyle&& other)
: styleFlags(std::forward<WindowStyleFlags>(other.styleFlags)), 
  exStyleFlags(std::forward<WindowExStyleFlags>(other.exStyleFlags))
{}

WindowStyle& WindowStyle::SetStyleFlags(WindowStyleFlags flags)
{
	styleFlags = flags;
	return *this;
}

WindowStyle& WindowStyle::SetExStyleFlags(WindowExStyleFlags flags)
{
	exStyleFlags = flags;
	return *this;
}

const WindowStyleFlags& WindowStyle::GetStyleFlags() const
{
	return styleFlags;
}

const WindowExStyleFlags& WindowStyle::GetExStyleFlags() const
{
	return exStyleFlags;
}

WindowStyle& WindowStyle::operator=(const WindowStyle& other)
{
	styleFlags = other.styleFlags;
	exStyleFlags = other.exStyleFlags;
	return *this;
}

WindowStyle& WindowStyle::operator=(WindowStyle&& other)
{
	styleFlags = std::forward<WindowStyleFlags>(other.styleFlags);
	exStyleFlags = std::forward<WindowExStyleFlags>(other.exStyleFlags);
	return *this;
}

WindowIcon::WindowIcon(WindowIconFlags flags)
: iconFlags(flags), iconSmFlags(flags)
{
	icon = LoadWindowIcon(iconFlags);
	iconSm = LoadWindowIcon(iconSmFlags);
}

WindowIcon::WindowIcon(WindowIconFlags iconFlags, WindowIconFlags iconSmFlags)
: iconFlags(iconFlags), iconSmFlags(iconSmFlags)
{
	icon = LoadWindowIcon(iconFlags);
	iconSm = LoadWindowIcon(iconSmFlags);
}

WindowIcon::WindowIcon(HICON icon)
: icon(icon), iconSm(icon)
{
	if (!IsSystemIcon(icon))
	{
		isSystemIcon = false;
		isSystemIconSm = false;
		iconFlags = WindowIconFlags::Other;
		iconSmFlags = WindowIconFlags::Other;
	}
}

WindowIcon::WindowIcon(HICON icon, HICON iconSm)
: icon(icon), iconSm(iconSm)
{
	if (!IsSystemIcon(icon))
	{
		isSystemIcon = false;
		iconFlags = WindowIconFlags::Other;
	}
	if (!IsSystemIcon(iconSm))
	{
		isSystemIconSm = false;
		iconSmFlags = WindowIconFlags::Other;
	}
}

WindowIcon::WindowIcon(const WindowIcon& other)
: iconFlags(other.iconFlags), iconSmFlags(other.iconSmFlags),
  icon(other.icon), iconSm(other.iconSm),
  isSystemIcon(other.isSystemIcon), isSystemIconSm(other.isSystemIconSm)
{}

WindowIcon::WindowIcon(WindowIcon&& other)
: iconFlags(std::forward<WindowIconFlags>(other.iconFlags)), 
  iconSmFlags(std::forward<WindowIconFlags>(other.iconSmFlags)),
  icon(std::forward<HICON>(other.icon)),
  iconSm(std::forward<HICON>(other.iconSm)),
  isSystemIcon(std::forward<bool>(other.isSystemIcon)),
  isSystemIconSm(std::forward<bool>(other.isSystemIconSm))
{}

WindowIcon::~WindowIcon()
{
	if (icon && !isSystemIcon)
	{
		DestroyIcon(icon);
		icon = nullptr;
	}
	if (iconSm && !isSystemIcon)
	{
		DestroyIcon(iconSm);
		iconSm = nullptr;
	}
}

HICON WindowIcon::LoadWindowIcon(WindowIconFlags flags)
{
	switch (flags)
	{
	case WindowIconFlags::Application:
		return LoadIconW(NULL, IDI_APPLICATION);
	case WindowIconFlags::Asterisk:
		return LoadIconW(NULL, IDI_ASTERISK);
	case WindowIconFlags::Error:
		return LoadIconW(NULL, IDI_ERROR);
	case WindowIconFlags::Exclamation:
		return LoadIconW(NULL, IDI_EXCLAMATION);
	case WindowIconFlags::Hand:
		return LoadIconW(NULL, IDI_HAND);
	case WindowIconFlags::Information:
		return LoadIconW(NULL, IDI_INFORMATION);
	case WindowIconFlags::Question:
		return LoadIconW(NULL, IDI_QUESTION);
	case WindowIconFlags::Warning:
		return LoadIconW(NULL, IDI_WARNING);
	case WindowIconFlags::Winlogo:
		return LoadIconW(NULL, IDI_WINLOGO);
	case WindowIconFlags::Shield:
		return LoadIconW(NULL, IDI_SHIELD);
	case WindowIconFlags::Other:
	default:
		isSystemIcon = false;
		isSystemIconSm = false;
		return nullptr;
	}
}

bool WindowIcon::IsSystemIcon(HICON icon)
{
	const std::vector<HICON> _sysIcons = {
		LoadIconW(NULL, IDI_APPLICATION),
		LoadIconW(NULL, IDI_ASTERISK),
		LoadIconW(NULL, IDI_ERROR),
		LoadIconW(NULL, IDI_EXCLAMATION),
		LoadIconW(NULL, IDI_HAND),
		LoadIconW(NULL, IDI_INFORMATION),
		LoadIconW(NULL, IDI_QUESTION),
		LoadIconW(NULL, IDI_WARNING),
		LoadIconW(NULL, IDI_WINLOGO),
		LoadIconW(NULL, IDI_SHIELD)
	};

	for (const auto& ic : _sysIcons)
		if (ic == icon)
			return true;
	return false;
}

WindowIcon& WindowIcon::SetIcon(HICON ic)
{
	icon = ic;
	if (!IsSystemIcon(ic))
	{
		isSystemIcon = false;
		iconFlags = WindowIconFlags::Other;
	}

	return *this;
}

WindowIcon& WindowIcon::SetIconSm(HICON icSm)
{
	iconSm = icSm;
	if (!IsSystemIcon(icSm))
	{
		isSystemIconSm = false;
		iconSmFlags = WindowIconFlags::Other;
	}

	return *this;
}

WindowIcon& WindowIcon::SetIconFlags(WindowIconFlags flags)
{
	iconFlags = flags;
	icon = LoadWindowIcon(iconFlags);
	return *this;
}

WindowIcon& WindowIcon::SetIconSmFlags(WindowIconFlags flags)
{
	iconSmFlags = flags;
	iconSm = LoadWindowIcon(flags);
	return *this;
}

const HICON& WindowIcon::GetIcon() const
{
	return icon;
}

const HICON& WindowIcon::GetIconSm() const
{
	return iconSm;
}

const WindowIconFlags& WindowIcon::GetIconFlags() const
{
	return iconFlags;
}

const WindowIconFlags& WindowIcon::GetIconSmFlags() const
{
	return iconSmFlags;
}

WindowIcon& WindowIcon::operator=(const WindowIcon& other)
{
	icon = other.icon;
	iconSm = other.iconSm;
	iconFlags = other.iconFlags;
	iconSmFlags = other.iconSmFlags;
	isSystemIcon = other.isSystemIcon;
	isSystemIconSm = other.isSystemIconSm;
	return *this;
}

WindowIcon& WindowIcon::operator=(WindowIcon&& other)
{
	iconFlags = std::forward<WindowIconFlags>(other.iconFlags);
	iconSmFlags = std::forward<WindowIconFlags>(other.iconSmFlags);
	icon = std::forward<HICON>(other.icon);
	iconSm = std::forward<HICON>(other.iconSm);
	isSystemIcon = std::forward<bool>(other.isSystemIcon);
	isSystemIconSm = std::forward<bool>(other.isSystemIconSm);
	return *this;
}

WindowCursor::WindowCursor(WindowCursorFlags flags)
: flags(flags)
{
	cursor = LoadWindowCursor(flags);
}

GraphlyUI::WindowCursor::WindowCursor(HCURSOR cursor)
: cursor(cursor)
{
	if (!IsSystemCursor(cursor))
	{
		isSystemCursor = false;
		flags = WindowCursorFlags::Other;
	}
}

WindowCursor::WindowCursor(const WindowCursor& other)
: cursor(other.cursor), flags(other.flags), isSystemCursor(other.isSystemCursor)
{}

WindowCursor::WindowCursor(WindowCursor&& other)
: cursor(std::forward<HCURSOR>(other.cursor)),
  flags(std::forward<WindowCursorFlags>(other.flags)),
  isSystemCursor(std::forward<bool>(other.isSystemCursor))
{}

WindowCursor::~WindowCursor()
{
	if (cursor && !isSystemCursor)
	{
		DestroyCursor(cursor);
		cursor = nullptr;
	}
}

WindowCursor& WindowCursor::SetCursor(HCURSOR cr)
{
	cursor = cr;
	if (!IsSystemCursor(cr))
	{
		isSystemCursor = false;
		flags = WindowCursorFlags::Other;
	}

	return *this;
}

WindowCursor& WindowCursor::SetFlags(WindowCursorFlags fl)
{
	cursor = LoadWindowCursor(flags);
	flags = fl;
	return *this;
}

const HCURSOR& WindowCursor::GetCursor() const
{
	return cursor;
}

const WindowCursorFlags& WindowCursor::GetFlags() const
{
	return flags;
}

WindowCursor& WindowCursor::operator=(const WindowCursor& other)
{
	cursor = other.cursor;
	flags = other.flags;
	isSystemCursor = other.isSystemCursor;
	return *this;
}

WindowCursor& WindowCursor::operator=(WindowCursor&& other)
{
	cursor = std::forward<HCURSOR>(other.cursor);
	flags = std::forward<WindowCursorFlags>(other.flags);
	isSystemCursor = std::forward<bool>(other.isSystemCursor);
	return *this;
}

HCURSOR WindowCursor::LoadWindowCursor(WindowCursorFlags flags)
{
	switch (flags)
	{
	case WindowCursorFlags::Arrow:
		return LoadCursorW(NULL, IDC_ARROW);
	case WindowCursorFlags::IBeam:
		return LoadCursorW(NULL, IDC_IBEAM);
	case WindowCursorFlags::Wait:
		return LoadCursorW(NULL, IDC_WAIT);
	case WindowCursorFlags::Cross:
		return LoadCursorW(NULL, IDC_CROSS);
	case WindowCursorFlags::UpArrow:
		return LoadCursorW(NULL, IDC_UPARROW);
	case WindowCursorFlags::Size:
		return LoadCursorW(NULL, IDC_SIZE);
	case WindowCursorFlags::Icon:
		return LoadCursorW(NULL, IDC_ICON);
	case WindowCursorFlags::Sizenwse:
		return LoadCursorW(NULL, IDC_SIZENWSE);
	case WindowCursorFlags::Sizenesw:
		return LoadCursorW(NULL, IDC_SIZENESW);
	case WindowCursorFlags::Sizewe:
		return LoadCursorW(NULL, IDC_SIZEWE);
	case WindowCursorFlags::Sizens:
		return LoadCursorW(NULL, IDC_SIZENS);
	case WindowCursorFlags::SizeAll:
		return LoadCursorW(NULL, IDC_SIZEALL);
	case WindowCursorFlags::No:
		return LoadCursorW(NULL, IDC_NO);
	case WindowCursorFlags::Hand:
		return LoadCursorW(NULL, IDC_HAND);
	case WindowCursorFlags::Appstarting:
		return LoadCursorW(NULL, IDC_APPSTARTING);
	case WindowCursorFlags::Other:
	default:
		isSystemCursor = false;
		return nullptr;
	}
}

bool WindowCursor::IsSystemCursor(HCURSOR cursor)
{
	const std::vector<HCURSOR> sysCursors = {
		LoadCursorW(NULL, IDC_ARROW),
		LoadCursorW(NULL, IDC_IBEAM),
		LoadCursorW(NULL, IDC_WAIT),
		LoadCursorW(NULL, IDC_CROSS),
		LoadCursorW(NULL, IDC_UPARROW),
		LoadCursorW(NULL, IDC_SIZE),
		LoadCursorW(NULL, IDC_ICON),
		LoadCursorW(NULL, IDC_SIZENWSE),
		LoadCursorW(NULL, IDC_SIZENESW),
		LoadCursorW(NULL, IDC_SIZEWE),
		LoadCursorW(NULL, IDC_SIZENS),
		LoadCursorW(NULL, IDC_SIZEALL),
		LoadCursorW(NULL, IDC_NO),
		LoadCursorW(NULL, IDC_HAND),
		LoadCursorW(NULL, IDC_APPSTARTING)
	};

	for (const auto& cr : sysCursors)
		if (cr == cursor)
			return true;
	return false;
}

WindowSettings::WindowSettings(const WindowSettings& other)
: procedure(other.procedure),
  instance(other.instance),
  cursor(other.cursor),
  title(other.title),
  className(other.className),
  icon(other.icon),
  position(other.position),
  dimension(other.dimension),
  backgroundColor(other.backgroundColor),
  style(other.style),
  nCmdShow(other.nCmdShow),
  multipleInstances(other.multipleInstances)
{}

WindowSettings::WindowSettings(WindowSettings&& other)
: procedure(std::forward<WNDPROC>(other.procedure)),
  instance(std::forward<HINSTANCE>(other.instance)),
  cursor(std::forward<WindowCursor>(other.cursor)),
  title(std::forward<std::wstring>(other.title)),
  className(std::forward<std::wstring>(other.className)),
  icon(std::forward<WindowIcon>(other.icon)),
  position(std::forward<Vector2>(other.position)),
  dimension(std::forward<Vector2>(other.dimension)),
  backgroundColor(std::forward<Vector3>(other.backgroundColor)),
  style(std::forward<WindowStyle>(other.style)),
  nCmdShow(std::forward<int>(other.nCmdShow)),
  multipleInstances(std::forward<bool>(other.multipleInstances))
{}

WindowSettings& WindowSettings::SetWindowProcedure(WNDPROC wndProc)
{
	procedure = wndProc;
	return *this;
}

WindowSettings& WindowSettings::SetInstance(HINSTANCE hInstance)
{
	instance = hInstance;
	return *this;
}

WindowSettings& WindowSettings::SetCursor(const WindowCursor& windowCursor)
{
	cursor = windowCursor;
	return *this;
}

WindowSettings& WindowSettings::SetTitle(const std::wstring& windowTitle)
{
	title = windowTitle;
	return *this;
}

WindowSettings& WindowSettings::SetClassName(const std::wstring& windowClassName)
{
	className = windowClassName;
	return *this;
}

WindowSettings& WindowSettings::SetIcon(const WindowIcon& windowIcon)
{
	icon = windowIcon;
	return *this;
}

WindowSettings& WindowSettings::SetPosition(const Vector2& windowPosition)
{
	position = windowPosition;
	return *this;
}

WindowSettings& WindowSettings::SetDimension(const Vector2& windowDimension)
{
	dimension = windowDimension;
	return *this;
}

WindowSettings& WindowSettings::SetBackgroundColor(const Vector3& bgColor)
{
	backgroundColor = bgColor;
	return *this;
}

WindowSettings& WindowSettings::SetStyle(const WindowStyle& windowStyle)
{
	style = windowStyle;
	return *this;
}

WindowSettings& WindowSettings::SetCmdShow(int nShow)
{
	nCmdShow = nShow;
	return *this;
}

WindowSettings& WindowSettings::AllowMultipleInstances(bool multipleInst)
{
	multipleInstances = multipleInst;
	return *this;
}

const WNDPROC& WindowSettings::GetWindowProcedure() const
{
	return procedure;
}

const HINSTANCE& WindowSettings::GetInstance() const
{
	return instance;
}

const WindowCursor& WindowSettings::GetWindowCursor() const
{
	return cursor;
}

const std::wstring& WindowSettings::GetTitle() const
{
	return title;
}

const WindowIcon& WindowSettings::GetWindowIcon() const
{
	return icon;
}

const Vector2& WindowSettings::GetWindowPosition() const
{
	return position;
}

const Vector2& WindowSettings::GetDimension() const
{
	return dimension;
}

const Vector3& WindowSettings::GetBackgroundColor() const
{
	return backgroundColor;
}

const WindowStyle& WindowSettings::GetWindowStyle() const
{
	return style;
}

const int WindowSettings::GetCmdShow() const
{
	return nCmdShow;
}

const bool WindowSettings::IsMultipleInstancesAllowed() const
{
	return multipleInstances;
}

WindowSettings& WindowSettings::operator=(const WindowSettings& other)
{
	procedure = other.procedure;
	instance = other.instance;
	cursor = other.cursor;
	title = other.title;
	className = other.className;
	icon = other.icon;
	position = other.position;
	dimension = other.dimension;
	backgroundColor = other.backgroundColor;
	style = other.style;
	nCmdShow = other.nCmdShow;
	multipleInstances = other.multipleInstances;
	return *this;
}

WindowSettings& WindowSettings::operator=(WindowSettings&& other)
{
	procedure = std::forward<WNDPROC>(other.procedure);
	instance = std::forward<HINSTANCE>(other.instance);
	cursor = std::forward<WindowCursor>(other.cursor);
	title = std::forward<std::wstring>(other.title);
	className = std::forward<std::wstring>(other.className);
	icon = std::forward<WindowIcon>(other.icon);
	position = std::forward<Vector2>(other.position);
	dimension = std::forward<Vector2>(other.dimension);
	backgroundColor = std::forward<Vector3>(other.backgroundColor);
	style = std::forward<WindowStyle>(other.style);
	nCmdShow = std::forward<int>(other.nCmdShow);
	multipleInstances = std::forward<bool>(other.multipleInstances);
	return *this;
}
