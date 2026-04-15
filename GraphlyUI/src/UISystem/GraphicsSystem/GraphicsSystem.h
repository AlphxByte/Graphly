#ifndef GRAPHLYUI_GRAPHICS_SYSTEM_HEADER
#define GRAPHLYUI_GRAPHICS_SYSTEM_HEADER

#include "GraphlyUI/UISystem/GraphicsSystemSettings.h"
#include "GraphicsDevice/GraphicsDevice.h"
#include "SwapChain/SwapChain.h"
#include "D2DSystem/D2DSystem.h"
#include "TextSystem/TextSystem.h"

#include <unordered_map>
#include <memory>

namespace GraphlyUI
{
	class Window;

	class GraphicsSystem final
	{
		using SwapChainIterator = std::unordered_map<HWND, SwapChainPtr>::iterator;
		using SwapChainConstIterator = std::unordered_map<HWND, SwapChainPtr>::const_iterator;

	public:
		GraphicsSystem(const GraphicsSystemSettings& settings);
		GraphicsSystem(GraphicsSystemSettings&& settings);
		GraphicsSystem(const GraphicsSystem& other) = delete;
		GraphicsSystem(GraphicsSystem&& other) = delete;
		~GraphicsSystem();

		void BeginDraw(Window* window);
		void EndDraw(Window* window);
		SwapChain* CreateSwapChain(HWND hwnd);
		bool DestroySwapChain(HWND hwnd);
		[[nodiscard]] SwapChain* GetSwapChain(HWND hwnd) const;
		bool ResizeSwapChain(HWND hwnd, UINT width, UINT height);

		[[nodiscard]] GraphicsDevice* GetGraphicsDevice() const;
		[[nodiscard]] D2DSystem* GetD2DSystem() const;
		[[nodiscard]] TextSystem* GetTextSystem() const;
		bool AllowTearing() const;

		GraphicsSystem& operator = (const GraphicsSystem& other) = delete;
		GraphicsSystem& operator = (GraphicsSystem&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		GraphicsSystemSettings _settings{};
		std::unordered_map<HWND, SwapChainPtr> _swapChains{};
		bool _allowTearing = false;

		GraphicsDevicePtr _graphicsDevice{};
		D2DSystemPtr _d2dSystem{};
		TextSystemPtr _textSystem{};
	};

	using GraphicsSystemPtr = std::unique_ptr<GraphicsSystem>;
	using GraphicsSystemSharedPtr = std::shared_ptr<GraphicsSystem>;
}

#endif // GRAPHLYUI_GRAPHICS_SYSTEM_HEADER
