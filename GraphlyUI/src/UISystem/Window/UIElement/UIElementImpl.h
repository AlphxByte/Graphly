#ifndef GRAPHLYUI_UIELEMENT_IMPL_HEADER
#define GRAPHLYUI_UIELEMENT_IMPL_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/UIElement.h"
#include "../../GraphicsSystem/D2DSystem/SolidColorBrush.h"
#include "GraphlyMath/Transform.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>

#include <functional>

namespace GraphlyUI
{
	struct UIElement::UIElementImpl
	{
		UIElementImpl() = default;
		UIElementImpl(const UIElementImpl& other) = delete;
		UIElementImpl(UIElementImpl&& other) = delete;
		~UIElementImpl() = default;

		UIElementImpl& operator = (const UIElementImpl& other) = delete;
		UIElementImpl& operator = (UIElementImpl&& other) = delete;

		// Members section
		// Settings
		UIElementSettings _settings;
		std::string _name{};

		// Resources
		SolidColorBrushPtr _brush{};
		D2D1_MATRIX_3X2_F _worldTransform = D2D1::Matrix3x2F::Identity();

		// Functions
		UIFunction _leftButtonDownFunction;
		UIFunction _leftButtonUpFunction;
		UIFunction _rightButtonDownFunction;
		UIFunction _rightButtonUpFunction;
		UIFunction _mouseMoveFunction;
		UIFunction _mouseEnterFunction;
		UIFunction _mouseLeaveFunction;
		UIFunction _activeFunction;
		UIFunction _resizeFunction;
		
		// Not owned 
		UIContext* _context{};
		UIElement* _parent{};

		// Child elements (owned)
		std::unordered_map<std::string, UIElementPtr> _uiChildren{};
	};
}

#endif // GRAPHLYUI_UIELEMENT_IMPL_HEADER