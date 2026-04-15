#include "SwapChain.h"
#include "../GraphicsDevice/D3DDevice.h"
#include "../D2DSystem/D2DDevice.h"
#include "../GraphicsDevice/DXGIFactory.h"

#include <stdexcept>

using namespace GraphlyUI;

SwapChain::SwapChain(const SwapChainSettings& settings)
: _allowTearing(settings.allowTearing)
{
	/*
	* NOTE: No need to pass width and height and pass 0 for both because 
	* CreateSwapChainFromHWNd function creates the swap chain with the correct size from:
	* 
	* RECT rect{};
	* GetWindowRect(&rect)
	* 
	* rect here has the top, bottom, left and right parameters where:
	* width is: right - left
	* height: bottom - top
	*/

	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.Width = 0;
	desc.Height = 0;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // Direct2D color format
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2; // Double buffering
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	desc.Scaling = DXGI_SCALING_NONE;
	if (_allowTearing)
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain{};
	HRESULT result = settings.dxgiFactory->GetFactory()->CreateSwapChainForHwnd
	(
		settings.d3dDevice->GetDevice(),
		settings.hwnd,
		&desc,
		nullptr,
		nullptr,
		&swapChain
	);
	if (FAILED(result))
		throw std::runtime_error("Swap Chain initialization failed.");

	// Update from IDXGISwapChain1 to IDXGISwapChain4
	result = swapChain->QueryInterface(IID_PPV_ARGS(&_swapChain));
	if (FAILED(result))
		throw std::runtime_error("Swap Chain initialization failed.");

	// RenderTarget section
	if (!CreateRenderTarget(settings.d2dDevice))
		throw std::runtime_error("RenderTarget creation failed.");
}

bool SwapChain::CreateRenderTarget(D2DDevice* d2dDevice)
{
	// Get back buffer from the swap chain as a surface object
	Microsoft::WRL::ComPtr<IDXGISurface1> surface{};
	HRESULT result = _swapChain->GetBuffer(0, IID_PPV_ARGS(&surface));
	if (FAILED(result))
		return false;

	/*
	* Create render target with the back buffer. We draw on the 
	* back buffer then flip the front buffer with the back buffer and 
	* present the new frame.
	*/ 
	try
	{
		_renderTarget = std::make_unique<RenderTarget>(d2dDevice->GetContext(), surface.Get());
		if (!_renderTarget)
			return false;
	}
	catch (const std::runtime_error&) 
	{
		return false;
	}

	return true;
}

bool SwapChain::Resize(UINT width, UINT height)
{
	_renderTarget->ResetRenderTarget();

	HRESULT result = _swapChain->ResizeBuffers
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN, // Keep the current format
		0
	);
	if (FAILED(result))
		return false;

	Microsoft::WRL::ComPtr<IDXGISurface1> surface{};
	result = _swapChain->GetBuffer(0, IID_PPV_ARGS(&surface));
	if (FAILED(result))
		return false;

	_renderTarget->CreateRenderTarget(surface.Get());

	return true;
}

HRESULT SwapChain::Present(bool vsync)
{
	UINT flags = 0;
	if (_allowTearing && !vsync)
		flags |= DXGI_PRESENT_ALLOW_TEARING;

	return _swapChain->Present(vsync, flags);
}

RenderTarget* GraphlyUI::SwapChain::GetRenderTarget() const
{
	return _renderTarget.get();
}

IDXGISwapChain4* GraphlyUI::SwapChain::GetSwapChain() const
{
	return _swapChain.Get();
}
