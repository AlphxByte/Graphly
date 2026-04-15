#include "GraphicsSystem.h"
#include "GraphlyUI/UISystem/Window/Window.h"
#include "GraphlyUI/UISystem/Window/UIElement/Rectangle.h"

#include <stdexcept>

using namespace GraphlyUI;

GraphicsSystem::GraphicsSystem(const GraphicsSystemSettings& settings)
: _settings(settings)
{
	if (!Initialize())
		throw std::runtime_error("GraphicsSystem initialization failed.");
}

GraphicsSystem::GraphicsSystem(GraphicsSystemSettings&& settings)
: _settings(std::move(settings))
{
	if (!Initialize())
		throw std::runtime_error("GraphicsSystem initialization failed.");
}

bool GraphicsSystem::Initialize()
{
	// GraphicsDevice section
	try
	{
		_graphicsDevice = std::make_unique<GraphicsDevice>(_settings.adapterSettings);
		if (!_graphicsDevice)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	HRESULT result = _graphicsDevice->GetDXGIFactory()->GetFactory()->CheckFeatureSupport
	(
		DXGI_FEATURE_PRESENT_ALLOW_TEARING,
		&_allowTearing,
		sizeof(_allowTearing)
	);

	// D2DSystem section
	try
	{
		_d2dSystem = std::make_unique<D2DSystem>(_graphicsDevice->GetDXGIDevice());
		if (!_d2dSystem)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// TextSystem section
	try
	{
		_textSystem = std::make_unique<TextSystem>();
		if (!_textSystem)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

GraphicsSystem::~GraphicsSystem()
{

}

void GraphicsSystem::BeginDraw(Window* window)
{
	_d2dSystem->GetD2DDevice()->BeginDraw();
}

void GraphicsSystem::EndDraw(Window* window)
{
	_d2dSystem->GetD2DDevice()->EndDraw();

	SwapChainIterator it = _swapChains.find(window->GetHWND());
	if (it == _swapChains.end())
		throw std::runtime_error("Invalid window handle.");

	it->second.get()->Present(_settings.vsync);
}

SwapChain* GraphicsSystem::CreateSwapChain(HWND hwnd)
{
	SwapChainIterator it = _swapChains.find(hwnd);
	if (it != _swapChains.end())
		return it->second.get();

	SwapChainSettings settings{};
	settings.hwnd = hwnd;
	settings.allowTearing = _allowTearing;
	settings.d3dDevice = _graphicsDevice->GetD3DDevice();
	settings.dxgiFactory = _graphicsDevice->GetDXGIFactory();
	settings.d2dDevice = _d2dSystem->GetD2DDevice();

	return _swapChains.emplace(hwnd, std::make_unique<SwapChain>(settings)).first->second.get();
}

bool GraphicsSystem::DestroySwapChain(HWND hwnd)
{
	SwapChainIterator it = _swapChains.find(hwnd);
	if (it == _swapChains.end())
		return false;

	_swapChains.erase(hwnd);
	return true;
}

SwapChain* GraphicsSystem::GetSwapChain(HWND hwnd) const
{
	SwapChainConstIterator it = _swapChains.find(hwnd);
	if (it != _swapChains.end())
		return it->second.get();
	return nullptr;
}

bool GraphicsSystem::ResizeSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainIterator it = _swapChains.find(hwnd);
	if (it == _swapChains.end())
		return false;

	return it->second.get()->Resize(width, height);
}

GraphicsDevice* GraphicsSystem::GetGraphicsDevice() const
{
	return _graphicsDevice.get();
}

D2DSystem* GraphicsSystem::GetD2DSystem() const
{
	return _d2dSystem.get();
}

TextSystem* GraphicsSystem::GetTextSystem() const
{
	return _textSystem.get();
}

bool GraphicsSystem::AllowTearing() const
{
	return _allowTearing;
}