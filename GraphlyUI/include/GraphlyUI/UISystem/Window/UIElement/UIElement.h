#ifndef GRAPHLYUI_UIELEMENT_HEADER
#define GRAPHLYUI_UIELEMENT_HEADER

#include "../../../GraphlyUIExports.h"
#include "GraphlyMath/GraphlyMath.h"
#include "UIEvent.h"

#include <windows.h>
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

namespace GraphlyUI
{
	// Forward declarations
	class UIElement;

	enum class UIElementAlignment
	{
		None,
		TopLeft,
		TopRight,
		TopCenter,
		CenterLeft,
		Center,
		CenterRight,
		BottomLeft, 
		BottomCenter,
		BottomRight
	};

	struct GRAPHLYUI_API UIElementSettings
	{
		GraphlyMath::Vector2 dimension{ 0.0f, 0.0f };
		GraphlyMath::Vector4 backgroundColor{ 255.0f, 255.0f, 255.0f, 1.0f };
		GraphlyMath::Transform transform;
		UIElementAlignment alignment = UIElementAlignment::None;
		bool isInteractable = true;
	};

	using UIElementPtr = std::unique_ptr<UIElement>;
	using UIElementSharedPtr = std::shared_ptr<UIElement>;
	using UIFunction = std::function<void(const UIEvent& e)>;

	class UIContext;
	class Rectangle;
	class Text;
	class Button;

	class GRAPHLYUI_API UIElement
	{
	public:
		using UIElementIterator = std::unordered_map<std::string, UIElementPtr>::iterator;
		using UIElementConstIterator = std::unordered_map<std::string, UIElementPtr>::const_iterator;

		UIElement(std::string_view name, const UIElementSettings& settings);
		UIElement(std::string_view name, UIElementSettings&& settings);
		UIElement(const UIElement& other) = delete;
		UIElement(UIElement&& other) = delete;
		virtual ~UIElement();

		virtual void Render();
		void SetLeftButtonDownFunction(UIFunction leftButtonDownFunction);
		void SetLeftButtonUpFunction(UIFunction leftButtonUpFunction);
		void SetRightButtonDownFunction(UIFunction rightButtonDownFunction);
		void SetRightButtonUpFunction(UIFunction rightButtonUpFunction);
		void SetMouseMoveFunction(UIFunction mouseMoveFunction);
		void SetMouseEnterFunction(UIFunction mouseEnterFunction);
		void SetMouseLeaveFunction(UIFunction mouseLeaveFunction);
		void SetActiveFunction(UIFunction activeFunction);
		void SetResizeFunction(UIFunction resizeFunction);
		void OnLeftButtonDown(const UIEvent& e);
		void OnLeftButtonUp(const UIEvent& e);
		void OnRightButtonDown(const UIEvent& e);
		void OnRightButtonUp(const UIEvent& e);
		void OnMouseMove(const UIEvent& e);
		void OnMouseEnter(const UIEvent& e);
		void OnMouseLeave(const UIEvent& e);
		void OnActive(const UIEvent& e);
		void OnResize(const UIEvent& e);

		template<typename T, typename... Args>
		T* CreateUIElement(std::string_view name, Args&&... args)
		{
			static_assert(std::is_base_of<UIElement, T>::value, "T must derive from UIElement.");
			auto element = std::make_unique<T>(name, std::forward<Args>(args)...);
			T* elem = element.get();
			CreateUIElementImpl(name, std::move(element));
			return elem;
		}

		bool DeleteUIElement(std::string_view name);
		bool DeleteUIElement(UIElement* parent, std::string_view elementName);
		[[nodiscard]] UIElement* GetUIElement(std::string_view name);
		[[nodiscard]] UIElement* GetUIElement(UIElement* parent, std::string_view elementName);

		void SetBackgroundColor(const GraphlyMath::Vector4& backgroundColor);
		void SetDimension(const GraphlyMath::Vector2& dimension);
		void SetTranslation(const GraphlyMath::Vector2& position);
		void SetRotation(float angle);
		void SetScale(const GraphlyMath::Vector2& scale);
		void SetTransform(const GraphlyMath::Transform& transform);
		void SetWorldTransform(const D2D1_MATRIX_3X2_F& worldTransform);

		[[nodiscard]] const D2D1_MATRIX_3X2_F& GetWorldTransform() const;
		[[nodiscard]] const GraphlyMath::Transform& GetTransform() const;
		[[nodiscard]] const GraphlyMath::Vector4& GetBackgroundColor() const;
		[[nodiscard]] UIElement* GetParent() const;
		[[nodiscard]] std::size_t GetChildCount() const;
		[[nodiscard]] std::size_t GetDescendantCount();
		[[nodiscard]] bool IsInteractable() const;
		[[nodiscard]] const UIElementSettings& GetUISettings() const;
		[[nodiscard]] const std::string& GetName() const;

		UIElementIterator begin();
		UIElementConstIterator begin() const;
		UIElementIterator end();
		UIElementConstIterator end() const;
 
		UIElement& operator = (const UIElement& other) = delete;
		UIElement& operator = (UIElement&& other) = delete;

	protected:
		virtual void OnInitialize() = 0;

	private:
		// Constructors for root element
		UIElement(UIContext* context, std::string_view name, const UIElementSettings& settings);
		UIElement(UIContext* context, std::string_view name, UIElementSettings&& settings);

		void SetAlignment(UIElement* elem);
		void CreateUIElementImpl(std::string_view name, UIElementPtr elem);

		struct UIElementImpl;
		std::unique_ptr<UIElementImpl> _impl{};

		friend class Rectangle;
		friend class Text;
		friend class Button;
	};
}

#endif // GRAPHLYUI_UIELEMENT_HEADER
