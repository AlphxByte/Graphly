#include "DXGIFactory.h"

#include <stdexcept>

using namespace GraphlyUI;

DXGIFactory::DXGIFactory()
{
	HRESULT result = CreateDXGIFactory2(0, IID_PPV_ARGS(&_factory));
	if (FAILED(result))
		throw std::runtime_error("DXGIFactory initialization failed.");
}

IDXGIFactory7* DXGIFactory::GetFactory() const
{
	return _factory.Get();
}