#ifndef GRAPHLYMATH_TRANSFORM_HEADER
#define GRAPHLYMATH_TRANSFORM_HEADER

#include "Vector.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>

namespace GraphlyMath
{
	class GRAPHLYMATH_API Translation final
	{
	public:
		Translation(const Vector2& position = { 0.0f, 0.0f });
		Translation(const D2D1_MATRIX_3X2_F& translation);
		Translation(const Translation& other) = default;
		Translation(Translation&& other) = default;
		~Translation() = default;

		void SetTranslation(const Vector2& position);
		[[nodiscard]] const D2D1_MATRIX_3X2_F& GetTranslationMatrix() const;
		[[nodiscard]] const Vector2 GetTranslationVector() const;

		Translation& operator = (const Translation& other) = default;
		Translation& operator = (Translation&& other) = default;

	private:
		D2D1_MATRIX_3X2_F _translation = D2D1::Matrix3x2F::Identity();
	};

	class GRAPHLYMATH_API Rotation final
	{
	public:
		Rotation(float rotation = 0.0f);
		Rotation(const D2D1_MATRIX_3X2_F& rotation);
		Rotation(const Rotation& other) = default;
		Rotation(Rotation&& other) = default;
		~Rotation() = default;

		void SetRotation(float rotation);
		[[nodiscard]] const D2D1_MATRIX_3X2_F& GetRotationMatrix() const;
		[[nodiscard]] const float GetRotation() const;

		Rotation& operator = (const Rotation& other) = default;
		Rotation& operator = (Rotation&& other) = default;

	private:
		D2D1_MATRIX_3X2_F _rotation = D2D1::Matrix3x2F::Identity();
		float _angle = 0.0f;
	};

	class GRAPHLYMATH_API Scale final
	{
	public:
		Scale(const Vector2& scale = { 1.0f, 1.0f });
		Scale(const D2D1_MATRIX_3X2_F& scale);
		Scale(const Scale& other) = default;
		Scale(Scale&& other) = default;
		~Scale() = default;

		void SetScale(const Vector2& scale);
		[[nodiscard]] const D2D1_MATRIX_3X2_F& GetScaleMatrix() const;
		[[nodiscard]] const Vector2 GetScaleVector() const;

		Scale& operator = (const Scale& other) = default;
		Scale& operator = (Scale&& other) = default;

	private:
		D2D1_MATRIX_3X2_F _scale = D2D1::Matrix3x2F::Identity();
	};

	class GRAPHLYMATH_API Transform final
	{
	public:
		Transform
		(
			const Translation& translation = Translation(), 
			const Rotation& rotation = Rotation(), 
			const Scale& scale = Scale()
		);
		Transform(const D2D1_MATRIX_3X2_F& transform);
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = default;
		~Transform() = default;

		Transform& SetTranslation(const Vector2& position);
		Transform& SetRotation(float angle);
		Transform& SetScale(const Vector2& scale);
		[[nodiscard]] Translation& GetTranslation();
		[[nodiscard]] Rotation& GetRotation();
		[[nodiscard]] Scale& GetScale();
		[[nodiscard]] const D2D1_MATRIX_3X2_F GetMatrix() const;

		Transform& operator = (const Transform& other) = default;
		Transform& operator = (Transform&& other) = default;

	private:
		Translation _translation;
		Rotation _rotation;
		Scale _scale;
	};
}

#endif // GRAPHLYMATH_TRANSFORM_HEADER