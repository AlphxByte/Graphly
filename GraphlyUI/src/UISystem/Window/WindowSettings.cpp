#include "GraphlyUI/UISystem/Window/WindowSettings.h"

using namespace GraphlyUI;
using namespace GraphlyMath;

WindowStyle::WindowStyle(WindowStyleFlags styleFlags, WindowExStyleFlags exStyleFlags)
: styleFlags(styleFlags), exStyleFlags(exStyleFlags)
{}

WindowStyle::WindowStyle(const WindowStyle & other)
: styleFlags(other.styleFlags), exStyleFlags(other.exStyleFlags)
{}

WindowStyle::WindowStyle(WindowStyle&& other)
: styleFlags(std::move(other.styleFlags)), 
  exStyleFlags(std::move(other.exStyleFlags))
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
	styleFlags = std::move(other.styleFlags);
	exStyleFlags = std::move(other.exStyleFlags);
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
: iconFlags(std::move(other.iconFlags)),
  iconSmFlags(std::move(other.iconSmFlags)),
  icon(std::move(other.icon)),
  iconSm(std::move(other.iconSm)),
  isSystemIcon(std::move(other.isSystemIcon)),
  isSystemIconSm(std::move(other.isSystemIconSm))
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
		return LoadIcon(NULL, IDI_APPLICATION);
	case WindowIconFlags::Asterisk:
		return LoadIcon(NULL, IDI_ASTERISK);
	case WindowIconFlags::Error:
		return LoadIcon(NULL, IDI_ERROR);
	case WindowIconFlags::Exclamation:
		return LoadIcon(NULL, IDI_EXCLAMATION);
	case WindowIconFlags::Hand:
		return LoadIcon(NULL, IDI_HAND);
	case WindowIconFlags::Information:
		return LoadIcon(NULL, IDI_INFORMATION);
	case WindowIconFlags::Question:
		return LoadIcon(NULL, IDI_QUESTION);
	case WindowIconFlags::Warning:
		return LoadIcon(NULL, IDI_WARNING);
	case WindowIconFlags::Winlogo:
		return LoadIcon(NULL, IDI_WINLOGO);
	case WindowIconFlags::Shield:
		return LoadIcon(NULL, IDI_SHIELD);
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
		LoadIcon(NULL, IDI_APPLICATION),
		LoadIcon(NULL, IDI_ASTERISK),
		LoadIcon(NULL, IDI_ERROR),
		LoadIcon(NULL, IDI_EXCLAMATION),
		LoadIcon(NULL, IDI_HAND),
		LoadIcon(NULL, IDI_INFORMATION),
		LoadIcon(NULL, IDI_QUESTION),
		LoadIcon(NULL, IDI_WARNING),
		LoadIcon(NULL, IDI_WINLOGO),
		LoadIcon(NULL, IDI_SHIELD)
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
	iconFlags = std::move(other.iconFlags);
	iconSmFlags = std::move(other.iconSmFlags);
	icon = std::move(other.icon);
	iconSm = std::move(other.iconSm);
	isSystemIcon = std::move(other.isSystemIcon);
	isSystemIconSm = std::move(other.isSystemIconSm);
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
: cursor(std::move(other.cursor)),
  flags(std::move(other.flags)),
  isSystemCursor(std::move(other.isSystemCursor))
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
	cursor = std::move(other.cursor);
	flags = std::move(other.flags);
	isSystemCursor = std::move(other.isSystemCursor);
	return *this;
}

HCURSOR WindowCursor::LoadWindowCursor(WindowCursorFlags flags)
{
	switch (flags)
	{
	case WindowCursorFlags::Arrow:
		return LoadCursor(NULL, IDC_ARROW);
	case WindowCursorFlags::IBeam:
		return LoadCursor(NULL, IDC_IBEAM);
	case WindowCursorFlags::Wait:
		return LoadCursor(NULL, IDC_WAIT);
	case WindowCursorFlags::Cross:
		return LoadCursor(NULL, IDC_CROSS);
	case WindowCursorFlags::UpArrow:
		return LoadCursor(NULL, IDC_UPARROW);
	case WindowCursorFlags::Size:
		return LoadCursor(NULL, IDC_SIZE);
	case WindowCursorFlags::Icon:
		return LoadCursor(NULL, IDC_ICON);
	case WindowCursorFlags::Sizenwse:
		return LoadCursor(NULL, IDC_SIZENWSE);
	case WindowCursorFlags::Sizenesw:
		return LoadCursor(NULL, IDC_SIZENESW);
	case WindowCursorFlags::Sizewe:
		return LoadCursor(NULL, IDC_SIZEWE);
	case WindowCursorFlags::Sizens:
		return LoadCursor(NULL, IDC_SIZENS);
	case WindowCursorFlags::SizeAll:
		return LoadCursor(NULL, IDC_SIZEALL);
	case WindowCursorFlags::No:
		return LoadCursor(NULL, IDC_NO);
	case WindowCursorFlags::Hand:
		return LoadCursor(NULL, IDC_HAND);
	case WindowCursorFlags::Appstarting:
		return LoadCursor(NULL, IDC_APPSTARTING);
	case WindowCursorFlags::Other:
	default:
		isSystemCursor = false;
		return nullptr;
	}
}

bool WindowCursor::IsSystemCursor(HCURSOR cursor)
{
	const std::vector<HCURSOR> sysCursors = {
		LoadCursor(NULL, IDC_ARROW),
		LoadCursor(NULL, IDC_IBEAM),
		LoadCursor(NULL, IDC_WAIT),
		LoadCursor(NULL, IDC_CROSS),
		LoadCursor(NULL, IDC_UPARROW),
		LoadCursor(NULL, IDC_SIZE),
		LoadCursor(NULL, IDC_ICON),
		LoadCursor(NULL, IDC_SIZENWSE),
		LoadCursor(NULL, IDC_SIZENESW),
		LoadCursor(NULL, IDC_SIZEWE),
		LoadCursor(NULL, IDC_SIZENS),
		LoadCursor(NULL, IDC_SIZEALL),
		LoadCursor(NULL, IDC_NO),
		LoadCursor(NULL, IDC_HAND),
		LoadCursor(NULL, IDC_APPSTARTING)
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
  style(other.style),
  nCmdShow(other.nCmdShow),
  multipleInstances(other.multipleInstances)
{}

WindowSettings::WindowSettings(WindowSettings&& other)
: procedure(std::move(other.procedure)),
  instance(std::move(other.instance)),
  cursor(std::move(other.cursor)),
  title(std::move(other.title)),
  className(std::move(other.className)),
  icon(std::move(other.icon)),
  position(std::move(other.position)),
  dimension(std::move(other.dimension)),
  style(std::move(other.style)),
  nCmdShow(std::move(other.nCmdShow)),
  multipleInstances(std::move(other.multipleInstances))
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

WindowSettings& WindowSettings::SetStyle(const WindowStyle& windowStyle)
{
	style = windowStyle;
	return *this;
}

WindowSettings& GraphlyUI::WindowSettings::SetData(LPVOID data)
{
	this->data = data;
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

const std::wstring& WindowSettings::GetWindowClassName() const
{
	return className;
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

const WindowStyle& WindowSettings::GetWindowStyle() const
{
	return style;
}

const LPVOID GraphlyUI::WindowSettings::GetData() const
{
	return data;
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
	style = other.style;
	nCmdShow = other.nCmdShow;
	multipleInstances = other.multipleInstances;
	data = other.data;
	return *this;
}

WindowSettings& WindowSettings::operator=(WindowSettings&& other)
{
	procedure = std::move(other.procedure);
	instance = std::move(other.instance);
	cursor = std::move(other.cursor);
	title = std::move(other.title);
	className = std::move(other.className);
	icon = std::move(other.icon);
	position = std::move(other.position);
	dimension = std::move(other.dimension);
	style = std::move(other.style);
	nCmdShow = std::move(other.nCmdShow);
	multipleInstances = std::move(other.multipleInstances);
	data = std::move(other.data);
	return *this;
}
