#ifndef GRAPHLYUI_GRAPHICS_SYSTEM_SETTINGS_HEADER
#define GRAPHLYUI_GRAPHICS_SYSTEM_SETTINGS_HEADER

#include "../GraphlyUIExports.h"

#include <string>

namespace GraphlyUI
{
	enum class AdapterPreference
	{
		LowPower,
		Balanced,
		Performance
	};

	struct GRAPHLYUI_API AdapterSettings final
	{
		AdapterPreference preference = AdapterPreference::LowPower;
	};

	struct GRAPHLYUI_API GraphicsSystemSettings final
	{
		AdapterSettings adapterSettings{};
		bool vsync = false;
	};
}

#endif // GRAPHLYUI_GRAPHICS_SYSTEM_SETTINGS_HEADER
