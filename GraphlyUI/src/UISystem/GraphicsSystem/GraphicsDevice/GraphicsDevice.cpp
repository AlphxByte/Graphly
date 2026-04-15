#include "GraphicsDevice.h"

#include <stdexcept>

using namespace GraphlyUI;

GraphicsDevice::GraphicsDevice(const AdapterSettings& adapterSettings)
: _adapterSettings(adapterSettings)
{
	if (!Initialize())
		throw std::runtime_error("Failed to initialize the GraphicsDevice.");
}

GraphicsDevice::GraphicsDevice(AdapterSettings&& adapterSettings)
: _adapterSettings(adapterSettings)
{
	if (!Initialize())
		throw std::runtime_error("Failed to initialize the GraphicsDevice.");
}

bool GraphicsDevice::Initialize()
{
	// Factory section
	try
	{
		_dxgiFactory = std::make_unique<DXGIFactory>();
		if (!_dxgiFactory)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// Adapter section
	try
	{
		_adapter = std::make_unique<Adapter>(_dxgiFactory.get(), _adapterSettings);
		if (!_adapter)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// D3DDevice section
	try
	{
		_d3dDevice = std::make_unique<D3DDevice>(_adapter.get());
		if (!_d3dDevice)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	//DXGIDevice section
	try
	{
		_dxgiDevice = std::make_unique<DXGIDevice>(_d3dDevice.get());
		if (!_dxgiDevice)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

DXGIFactory* GraphicsDevice::GetDXGIFactory() const
{
	return _dxgiFactory.get();
}

Adapter* GraphicsDevice::GetAdapter() const
{
	return _adapter.get();
}

D3DDevice* GraphicsDevice::GetD3DDevice() const
{
	return _d3dDevice.get();
}

DXGIDevice* GraphicsDevice::GetDXGIDevice() const
{
	return _dxgiDevice.get();
}
