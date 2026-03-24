#ifndef GRAPHLYUI_IMAGE_HEADER
#define GRAPHLYUI_IMAGE_HEADER

#include "UIElement.h"

namespace GraphlyUI
{
	struct GRAPHLYUI_API ImageSettings : public UIElementSettings
	{
		ImageSettings()
		: UIElementSettings(UIElementType::Image) 
		{}
	};

	class GRAPHLYUI_API Image final : public UIElement
	{
	public:
		Image(std::string_view name, const UIElementSettings& uiElemSettings, const ImageSettings& imageSettings);
		Image(std::string_view name, UIElementSettings&& uiElemSettings, ImageSettings&& imageSettings);
		Image(const Image& other) = delete;
		Image(Image&& other) = delete;
		~Image() = default;

		Image& operator = (const Image& other) = delete;
		Image& operator = (Image&& other) = delete;

	private:
		ImageSettings _settings{};
	};

	using ImagePtr       = std::unique_ptr<Image>;
	using ImageSharedPtr = std::shared_ptr<Image>;
}

#endif // GRAPHLYUI_IMAGE_HEADER
