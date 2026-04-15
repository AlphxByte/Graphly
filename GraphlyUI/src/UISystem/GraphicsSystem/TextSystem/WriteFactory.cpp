#include "WriteFactory.h"

#include <stdexcept>

using namespace GraphlyUI;

WriteFactory::WriteFactory()
{
	HRESULT result = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory8),
		reinterpret_cast<IUnknown**>(_factory.GetAddressOf())
	);
	if (FAILED(result))
		throw std::runtime_error("WriteFactory failed to initialize.");
}

IDWriteFactory8* WriteFactory::GetFactory() const
{
	return _factory.Get();
}