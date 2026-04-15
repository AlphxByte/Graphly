#include "SolidColorBrush.h"
#include "D2DDevice.h"

#include <stdexcept>

using namespace GraphlyUI;
using namespace GraphlyMath;

SolidColorBrush::SolidColorBrush(D2DDevice* d2dDevice, const Vector4& color)
{
	// Normalize RGB values
	HRESULT result = d2dDevice->GetContext()->CreateSolidColorBrush
	(
		D2D1::ColorF
		(
			color.GetX() / 255.0f, 
			color.GetY() / 255.0f, 
			color.GetZ() / 255.0f, 
			color.GetW()
		),
		&_brush
	);
	if (FAILED(result))
		throw std::runtime_error("SolidColorBrush failed to initialize.");
}

SolidColorBrush::SolidColorBrush(D2DDevice* d2dDevice, Vector4&& color)
{
	// Normalize RGB values
	HRESULT result = d2dDevice->GetContext()->CreateSolidColorBrush
	(
		D2D1::ColorF
		(
			color.GetX() / 255.0f,
			color.GetY() / 255.0f,
			color.GetZ() / 255.0f,
			color.GetW()
		),
		&_brush
	);
	if (FAILED(result))
		throw std::runtime_error("SolidColorBrush failed to initialize.");
}

void SolidColorBrush::SetColor(const Vector4& color)
{
	_brush->SetColor(D2D1::ColorF
	(
		color.GetX() / 255.0f,
		color.GetY() / 255.0f,
		color.GetZ() / 255.0f,
		color.GetW()
	));
}

void SolidColorBrush::SetColor(Vector4&& color)
{
	_brush->SetColor(D2D1::ColorF
	(
		color.GetX() / 255.0f,
		color.GetY() / 255.0f,
		color.GetZ() / 255.0f,
		color.GetW()
	));
}

const Vector4& SolidColorBrush::GetColor() const
{
	D2D1_COLOR_F color = _brush->GetColor();
	return Vector4
	(
		color.r * 255.0f,
		color.g * 255.0f,
		color.b * 255.0f,
		color.a
	);
}

ID2D1SolidColorBrush* SolidColorBrush::GetBrush() const
{
	return _brush.Get();
}
