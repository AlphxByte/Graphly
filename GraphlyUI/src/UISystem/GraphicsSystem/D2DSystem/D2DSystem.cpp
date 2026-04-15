#include "D2DSystem.h"

#include <stdexcept>

using namespace GraphlyUI;

D2DSystem::D2DSystem(DXGIDevice* dxgiDevice)
: _dxgiDevice(dxgiDevice)
{
	if (!Initialize())
		throw std::runtime_error("D2DSystem initialization failed.");
}

bool D2DSystem::Initialize()
{
	// D2DFactory section
	try
	{
		_d2dFactory = std::make_unique<D2DFactory>();
		if (!_d2dFactory)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// D2DDevice section
	try
	{
		_d2dDevice = std::make_unique<D2DDevice>(_d2dFactory.get(), _dxgiDevice);
		if (!_d2dDevice)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

D2DFactory* D2DSystem::GetD2DFactory() const
{
	return _d2dFactory.get();
}

D2DDevice* D2DSystem::GetD2DDevice() const
{
	return _d2dDevice.get();
}
