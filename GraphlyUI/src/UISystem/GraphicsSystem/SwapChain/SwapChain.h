#ifndef GRAPHLYUI_SWAPCHAIN_HEADER
#define GRAPHLYUI_SWAPCHAIN_HEADER

#include "RenderTarget.h"

#include <dxgi1_6.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class D3DDevice;
	class D2DDevice;
	class DXGIFactory;

	struct SwapChainSettings final
	{
		D3DDevice* d3dDevice{};
		D2DDevice* d2dDevice{};
		DXGIFactory* dxgiFactory{};
		HWND hwnd{};
		bool allowTearing = false;
	};

	class SwapChain final
	{
	public:
		SwapChain(const SwapChainSettings& settings);
		SwapChain(const SwapChain& other) = delete;
		SwapChain(SwapChain&& other) = delete;
		~SwapChain() = default;

		bool Resize(UINT width, UINT height);
		HRESULT Present(bool vsync = false);

		[[nodiscard]] RenderTarget* GetRenderTarget() const;
		[[nodiscard]] IDXGISwapChain4* GetSwapChain() const;

		SwapChain& operator = (const SwapChain& other) = delete;
		SwapChain& operator = (SwapChain&& other) = delete;

	private:
		[[nodiscard]] bool CreateRenderTarget(D2DDevice* d2dDevice);

	private:
		bool _allowTearing = false;

		// Owned resources
		RenderTargetPtr _renderTarget{};
		Microsoft::WRL::ComPtr<IDXGISwapChain4> _swapChain{};
	};

	using SwapChainPtr = std::unique_ptr<SwapChain>;
	using SwapChainSharedPtr = std::shared_ptr<SwapChain>;
}

#endif // GRAPHLYUI_SWAPCHAIN_HEADER
