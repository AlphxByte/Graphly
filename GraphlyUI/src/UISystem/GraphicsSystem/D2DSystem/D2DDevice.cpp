#include "D2DDevice.h"
#include "D2DFactory.h"
#include "../GraphicsDevice/DXGIDevice.h"

#include <stdexcept>

using namespace GraphlyUI;
using namespace GraphlyMath;
using namespace D2D1;

D2DDevice::D2DDevice(D2DFactory* d2dFactory, DXGIDevice* dxgiDevice)
{
	HRESULT result = d2dFactory->GetFactory()->CreateDevice
	(
		dxgiDevice->GetDevice(),
		&_device
	);
	if (FAILED(result))
		throw std::runtime_error("D2DDevice initialization failed.");

	result = _device->CreateDeviceContext
	(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&_context
	);
	if (FAILED(result))
		throw std::runtime_error("D2DDevice initialization failed.");	
}

void D2DDevice::BeginDraw()
{
	_context->BeginDraw();
}

void D2DDevice::EndDraw()
{
	_context->EndDraw();
}

void D2DDevice::PushAxisAlignedClip(const Vector4& rect)
{
	_context->PushAxisAlignedClip
	(
		D2D1::RectF(rect.GetX(), rect.GetY(), rect.GetZ(), rect.GetW()),
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
	);
}

void D2DDevice::PopAxisAlignedClip()
{
	_context->PopAxisAlignedClip();
}

void D2DDevice::Clear(const GraphlyMath::Vector4& color)
{
	_context->Clear(D2D1_COLOR_F(color.GetX(), color.GetY(), color.GetZ(), color.GetW()));
}

void D2DDevice::SetTransform(const D2D1_MATRIX_3X2_F& transform)
{
	_context->SetTransform(transform);
}

void D2DDevice::GetTransform(D2D1_MATRIX_3X2_F& transform)
{
	_context->GetTransform(&transform);
}

void D2DDevice::FillRectangle(const Vector4& rect, SolidColorBrush* brush)
{
	_context->FillRectangle
	(
		D2D1::RectF(rect.GetX(), rect.GetY(), rect.GetZ(), rect.GetW()),
		brush->GetBrush()
	);
}

ID2D1Device6* D2DDevice::GetDevice() const
{
	return _device.Get();
}

ID2D1DeviceContext6* D2DDevice::GetContext() const
{
	return _context.Get();
}
