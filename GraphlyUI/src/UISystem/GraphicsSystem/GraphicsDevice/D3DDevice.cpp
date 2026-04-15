#include "D3DDevice.h"
#include "Adapter.h"

#include <stdexcept>

using namespace GraphlyUI;

D3DDevice::D3DDevice(Adapter* adapter)
{
	// Supported feature set
	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_12_2, // Not supported on Direct11
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // This flag is used to enable Direct2D support
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG; // Flag used for debug information
#endif // _DEBUG

	HRESULT result;
	for (UINT i = 0; i < numFeatureLevels; ++i)
	{
		result = D3D11CreateDevice
		(
			adapter->GetAdapter(),
			D3D_DRIVER_TYPE_UNKNOWN, // Unknown because we pass an adapter
			nullptr,
			flags,
			&featureLevels[i], 1,
			D3D11_SDK_VERSION,
			&_device,
			&_featureLevel,
			&_context
		);
		if (SUCCEEDED(result))
			break;
	}

	if (FAILED(result))
		throw std::runtime_error("D3DDevice initialization failed.");
}

D3DDevice::~D3DDevice()
{

}

ID3D11Device* D3DDevice::GetDevice() const
{
	return _device.Get();
}

ID3D11DeviceContext* D3DDevice::GetDeviceContext() const
{
	return _context.Get();
}

const D3D_FEATURE_LEVEL D3DDevice::GetFeatureLevel() const
{
	return _featureLevel;
}
