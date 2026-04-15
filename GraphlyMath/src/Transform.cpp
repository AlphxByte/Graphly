#include "GraphlyMath/Transform.h"

using namespace GraphlyMath;
using namespace D2D1;

Translation::Translation(const Vector2& position)
{
	_translation = Matrix3x2F::Translation(position.GetX(), position.GetY());
}

Translation::Translation(const D2D1_MATRIX_3X2_F& translation)
: _translation(translation)
{}

void Translation::SetTranslation(const Vector2& position)
{
	_translation = Matrix3x2F::Translation(position.GetX(), position.GetY());
}

const D2D1_MATRIX_3X2_F& Translation::GetTranslationMatrix() const
{
	return _translation;
}

const Vector2 Translation::GetTranslationVector() const
{
	return Vector2(_translation.dx, _translation.dy);
}

Rotation::Rotation(float rotation)
: _angle(rotation)
{
	_rotation = Matrix3x2F::Rotation(rotation * 180.0f);
}

Rotation::Rotation(const D2D1_MATRIX_3X2_F& rotation)
: _rotation(rotation)
{}

void Rotation::SetRotation(float rotation)
{
	_angle = rotation;
	_rotation = Matrix3x2F::Rotation(rotation * 180.0f);
}

const D2D1_MATRIX_3X2_F& Rotation::GetRotationMatrix() const
{
	return _rotation;
}

const float Rotation::GetRotation() const
{
	return _angle;
}

Scale::Scale(const Vector2& scale)
{
	_scale = Matrix3x2F::Scale(D2D1_SIZE_F(scale.GetX(), scale.GetY()));
}

Scale::Scale(const D2D1_MATRIX_3X2_F& scale)
: _scale(scale)
{}

void Scale::SetScale(const Vector2& scale)
{
	_scale = Matrix3x2F::Scale(D2D1_SIZE_F(scale.GetX(), scale.GetY()));
}

const D2D1_MATRIX_3X2_F& Scale::GetScaleMatrix() const
{
	return _scale;
}

const Vector2 Scale::GetScaleVector() const
{
	return Vector2(_scale.m11, _scale.m22);
}

Transform::Transform(const Translation& translation, const Rotation& rotation, const Scale& scale)
: _translation(translation), 
  _rotation(rotation), 
  _scale(scale)
{}

Transform::Transform(const D2D1_MATRIX_3X2_F& transform)
{

}

Transform& Transform::SetTranslation(const Vector2& position)
{
	_translation.SetTranslation(position);
	return *this;
}

Transform& Transform::SetRotation(float angle)
{
	_rotation = Rotation(angle);
	return *this;
}

Transform& Transform::SetScale(const Vector2& scale)
{
	_scale = Scale(scale);
	return *this;
}

Translation& Transform::GetTranslation()
{
	return _translation;
}

Rotation& Transform::GetRotation()
{
	return _rotation;
}

Scale& Transform::GetScale()
{
	return _scale;
}

const D2D1_MATRIX_3X2_F Transform::GetMatrix() const
{
	return _scale.GetScaleMatrix() *
		   _rotation.GetRotationMatrix() *
		   _translation.GetTranslationMatrix();
}
