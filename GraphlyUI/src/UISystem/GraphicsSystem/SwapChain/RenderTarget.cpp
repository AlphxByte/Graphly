#include "RenderTarget.h"

#include <stdexcept>

using namespace GraphlyUI;

RenderTarget::RenderTarget(ID2D1DeviceContext6* context, IDXGISurface1* surface)
: _context(context)
{
	CreateRenderTarget(surface);
}

void RenderTarget::CreateRenderTarget(IDXGISurface1* surface)
{
	D2D1_BITMAP_PROPERTIES1 props{};
	props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

	HRESULT result = _context->CreateBitmapFromDxgiSurface
	(
		surface,
		&props,
		&_bitmap
	);
	if (FAILED(result))
		throw std::runtime_error("RenderTarget creation failed.");

	_context->SetTarget(_bitmap.Get());
}

void RenderTarget::ResetRenderTarget()
{
	_context->SetTarget(nullptr);
	_bitmap.Reset();
}

ID2D1Bitmap1* RenderTarget::GetBitmap() const
{
	return _bitmap.Get();
}
