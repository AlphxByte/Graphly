#ifndef GRAPHLYUI_UIELEMENT_HEADER
#define GRAPHLYUI_UIELEMENT_HEADER

#include "GraphlyMath/GraphlyMath.h"
#include "GraphlyUIExports.h"

#include <windows.h>
#include <unordered_map>
#include <string>
#include <memory>

namespace GraphlyUI
{
	// Forward declarations
	class UIContext;
	class UIFactory;
	class UIElement;

	enum class GRAPHLYUI_API UIElementType
	{
		TextField, Button, Image
	};

	struct GRAPHLYUI_API UIElementSettings
	{
		UIElement* parent{};
		std::wstring text{};
		GraphlyMath::Vector2 position{ 0, 0 };
		GraphlyMath::Vector2 dimension{ 50, 50 };

	protected:
		UIElementType type = UIElementType::TextField;

		UIElementSettings(UIElementType type = UIElementType::TextField)
		: type(type) {}

		friend class UIElement;
	};

	using UIElementPtr       = std::unique_ptr<UIElement>;
	using UIElementSharedPtr = std::shared_ptr<UIElement>;

	class GRAPHLYUI_API UIElement
	{
	public:
		UIElement(std::string_view name, const UIElementSettings& settings);
		UIElement(std::string_view name, UIElementSettings&& settings);
		UIElement(const UIElement& other) = delete;
		UIElement(UIElement&& other) = delete;
		virtual ~UIElement() = default;

		UIElement* AddUIElement(std::string_view name, const UIElementSettings& settings);
		UIElement* AddUIElement(std::string_view name, UIElementSettings&& settings);
		bool DeleteUIElement(std::string_view name);
		bool DeleteUIElement(UIElement* parent, std::string_view elementName);
		[[nodiscard]] UIElement* GetUIElement(std::string_view name);
		[[nodiscard]] UIElement* GetUIElement(UIElement* parent, std::string_view elementName);
		[[nodiscard]] UIElement* GetParent() const;
		[[nodiscard]] std::size_t GetChildCount() const;
		[[nodiscard]] std::size_t GetDescendantCount();
 
		UIElement& operator = (const UIElement& other) = delete;
		UIElement& operator = (UIElement&& other) = delete;

	protected:
		UIElementSettings _settings;
		std::string _name{};

	private:
		// Root constructors
		UIElement(UIFactory* factory, std::string_view name, const UIElementSettings& settings);
		UIElement(UIFactory* factory, std::string_view name, UIElementSettings&& settings);

		// Helper Functions
		[[nodiscard]] bool Initialize();

		UIFactory* _factory{};
		UIElement* _parent{};
		std::unordered_map<std::string, UIElementPtr> _uiChildren{};

		friend class UIContext;

		using UIElementIterator      = std::unordered_map<std::string, UIElementPtr>::iterator;
		using UIElementConstIterator = std::unordered_map<std::string, UIElementPtr>::const_iterator;
	};
}

#endif // GRAPHLYUI_UIELEMENT_HEADER
