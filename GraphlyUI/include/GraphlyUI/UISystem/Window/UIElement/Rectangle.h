#ifndef GRAPHLYUI_RECTANGLE_HEADER
#define GRAPHLYUI_RECTANGLE_HEADER

#include "UIElement.h"

#include <string>

namespace GraphlyUI
{
	class Window;
	class UIContext;

	class GRAPHLYUI_API Rectangle : public UIElement
	{
	public:
		Rectangle(std::string_view name, const UIElementSettings& settings);
		Rectangle(std::string_view name, UIElementSettings&& settings);
		Rectangle(const Rectangle& other) = delete;
		Rectangle(Rectangle&& other) = delete;
		~Rectangle();

		void Render() override;

		Rectangle& operator = (const Rectangle& other) = delete;
		Rectangle& operator = (Rectangle&& other) = delete;

	private:
		// Constructors for root element
		Rectangle(UIContext* context, std::string_view name, const UIElementSettings& settings);
		Rectangle(UIContext* context, std::string_view name, UIElementSettings&& settings);

		void OnInitialize() override;

		struct RectangleImpl;
		std::unique_ptr<RectangleImpl> _impl{};

		friend class Window;
	};

	using RectanglePtr = std::unique_ptr<Rectangle>;
	using RectangleSharedPtr = std::shared_ptr<Rectangle>;
}

#endif // GRAPHLYUI_RECTANGLE_HEADER
