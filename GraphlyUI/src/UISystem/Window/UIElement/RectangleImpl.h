#ifndef GRAPHLYUI_RECTANGLE_IMPL_HEADER
#define GRAPHLYUI_RECTANGLE_IMPL_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/Rectangle.h"

namespace GraphlyUI
{
	struct Rectangle::RectangleImpl
	{
		RectangleImpl() = default;
		RectangleImpl(const RectangleImpl& other) = delete;
		RectangleImpl(RectangleImpl&& other) = delete;

		[[nodiscard]] bool Initialize();

		RectangleImpl& operator = (const RectangleImpl& other) = delete;
		RectangleImpl& operator = (RectangleImpl&& other) = delete;
	};
}

#endif // GRAPHLYUI_RECTANGLE_IMPL_HEADER
