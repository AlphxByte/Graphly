#include "DXGIDevice.h"
#include "D3DDevice.h"

#include <stdexcept>

using namespace GraphlyUI;

DXGIDevice::DXGIDevice(D3DDevice* d3dDevice)
{
	HRESULT result = d3dDevice->GetDevice()->QueryInterface(IID_PPV_ARGS(&_device));
	if (FAILED(result))
		throw std::runtime_error("DXGIDevice initialization failed.");
}

IDXGIDevice4* DXGIDevice::GetDevice() const
{
	return _device.Get();
}