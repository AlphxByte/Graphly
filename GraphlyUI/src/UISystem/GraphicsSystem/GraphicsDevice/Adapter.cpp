#include "Adapter.h"
#include "DXGIFactory.h"

#include <stdexcept>

using namespace GraphlyUI;

Adapter::Adapter(DXGIFactory* dxgiFactory, const AdapterSettings& settings)
: _settings(settings)
{
	switch (_settings.preference)
	{
	case AdapterPreference::LowPower:
		_gpuPreference = DXGI_GPU_PREFERENCE_MINIMUM_POWER;
		break;
	case AdapterPreference::Performance:
		_gpuPreference = DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE;
		break;
	case AdapterPreference::Balanced:
	default:
		_gpuPreference = DXGI_GPU_PREFERENCE_UNSPECIFIED;
		break;
	}

	for (UINT i = 0;
		dxgiFactory->GetFactory()->EnumAdapterByGpuPreference
		(
			i,
			_gpuPreference,
			IID_PPV_ARGS(&_adapter)
		) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DXGI_ADAPTER_DESC3 desc{};
		HRESULT result = _adapter->GetDesc3(&desc);
		if (SUCCEEDED(result))
			break;

		// Skip Software Adapters
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;
	}
}

IDXGIAdapter4* Adapter::GetAdapter() const
{
	return _adapter.Get();
}

const AdapterSettings& Adapter::GetSettings() const
{
	return _settings;
}