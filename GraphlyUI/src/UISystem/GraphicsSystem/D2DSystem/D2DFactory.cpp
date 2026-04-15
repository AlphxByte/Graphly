#include "D2DFactory.h"

#include <stdexcept>

using namespace GraphlyUI;

D2DFactory::D2DFactory()
{
	D2D1_FACTORY_OPTIONS options{};
#ifdef _DEBUG
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	HRESULT result = D2D1CreateFactory
	(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(&_factory),
		&options,
		&_factory
	);
	if (FAILED(result))
		throw std::runtime_error("D2DFactory initialization failed.");
}

ID2D1Factory7* D2DFactory::GetFactory() const
{
	return _factory.Get();
}
