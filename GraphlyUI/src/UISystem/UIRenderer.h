#ifndef GRAPHLYUI_UIRENDERER_HEADER
#define GRAPHLYUI_UIRENDERER_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/UIElement.h"
#include "GraphlyUI/UISystem/Window/UIElement/Rectangle.h"
#include <memory>

namespace GraphlyUI
{
	class GraphicsSystem;

	class UIRenderer final
	{
	public:
		explicit UIRenderer(GraphicsSystem* graphicsSystem);
		UIRenderer(const UIRenderer& other) = delete;
		UIRenderer(UIRenderer&& other) = delete;
		~UIRenderer() = default;

		void Render(UIElement* element);

		UIRenderer& operator = (const UIRenderer& other) = delete;
		UIRenderer& operator = (UIRenderer&& other) = delete;

	private:
		const D2D1_POINT_2F TransformPoint(const D2D1_MATRIX_3X2_F& m, const GraphlyMath::Vector2& point) const;

	private:
		// Not owned 
		GraphicsSystem* _graphicsSystem{};
	};

	using UIRendererPtr = std::unique_ptr<UIRenderer>;
	using UIRendererSharedPtr = std::shared_ptr<UIRenderer>;
}

#endif // GRAPHLYUI_UIRENDERER_HEADER
