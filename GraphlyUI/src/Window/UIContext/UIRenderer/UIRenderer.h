#ifndef GRAPHLYUI_UIRENDERER_HEADER
#define GRAPHLYUI_UIRENDERER_HEADER

#include <d3d11.h>
#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class UIRenderer final
	{
	public:
		UIRenderer(HWND hwnd);
		UIRenderer(const UIRenderer& other) = delete;
		UIRenderer(UIRenderer&& other) = delete;
		~UIRenderer();

		UIRenderer& operator = (const UIRenderer& other) = delete;
		UIRenderer& operator = (UIRenderer&& other) = delete;

	private:
		HWND _hwnd{};
	};

	using UIRendererPtr       = std::unique_ptr<UIRenderer>;
	using UIRendererSharedPtr = std::shared_ptr<UIRenderer>;
}

#endif // GRAPHLYUI_UIRENDERER_HEADER
