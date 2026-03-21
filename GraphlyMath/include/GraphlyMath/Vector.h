#ifndef GRAPHLYMATH_VECTOR_HEADER
#define GRAPHLYMATH_VECTOR_HEADER

#include <iostream>
#include <DirectXMath.h>
#include "GraphlyMathExports.h"

namespace GraphlyMath
{
	template<std::size_t N>
	class alignas(16) Vector final
	{
	public:
		Vector() noexcept
		: _v(DirectX::XMVectorZero()) 
		{ static_assert (N >= 2 && N <= 4, "Invalid N dimension"); }

		Vector(DirectX::XMVECTOR v) noexcept
		: _v(v) 
		{ static_assert (N >= 2 && N <= 4, "Invalid N dimension"); }

		Vector(float x, float y) noexcept
		{
			static_assert (N == 2, "Invalid N dimension");
			_v = DirectX::XMVECTOR{ x, y, 0.0f, 0.0f };
		}

		Vector(float x, float y, float z) noexcept
		{
			static_assert (N == 3, "Invalid N dimension");
			_v = DirectX::XMVECTOR{ x, y, z, 0.0f };
		}

		Vector(float x, float y, float z, float w) noexcept
		{
			static_assert (N == 4, "Invalid N dimension");
			_v = DirectX::XMVECTOR{ x, y, z, w };
		}

		Vector(const Vector& other) noexcept
		: _v(other._v)
		{}

		Vector(Vector&& other) noexcept
		: _v(std::forward<DirectX::XMVECTOR>(other._v))
		{}

		~Vector() = default;

		inline float GetX() const noexcept
		{ 
			return DirectX::XMVectorGetX(_v);
		}

		inline float GetY() const noexcept
		{
			return DirectX::XMVectorGetY(_v);
		}

		inline float GetZ() const noexcept
		{
			static_assert (N >= 3, "Invalid N dimension");
			return DirectX::XMVectorGetZ(_v);
		}

		inline float GetW() const noexcept
		{
			static_assert (N == 4, "Invalid N dimension");
			return DirectX::XMVectorGetW(_v);
		}

		inline void SetX(float x) noexcept
		{
			DirectX::XMVectorSetX(_v, x);
		}

		inline void SetY(float y) noexcept
		{
			DirectX::XMVectorSetY(_v, y);
		}

		inline void SetZ(float z) noexcept
		{
			static_assert (N >= 3, "Invalid N dimension");
			DirectX::XMVectorSetZ(_v, z);
		}

		inline void SetW(float w) noexcept
		{
			static_assert (N == 4, "Invalid N dimension");
			DirectX::XMVectorSetW(_v, w);
		}

		inline Vector& operator = (const Vector& other) noexcept
		{
			_v = other._v;
			return *this;
		}

		inline Vector& operator = (Vector&& other) noexcept
		{
			_v = std::forward<DirectX::XMVECTOR>(other._v);
			return *this;
		}

		inline Vector& operator = (const DirectX::XMVECTOR& v) noexcept
		{
			_v = v;
			return *this;
		}

		inline Vector operator + (const Vector& other) noexcept
		{
			return Vector(DirectX::XMVectorAdd(_v, other._v));
		}

		inline Vector& operator += (const Vector& other) noexcept
		{
			_v = DirectX::XMVectorAdd(_v, other._v);
			return *this;
		}

		inline Vector operator - (const Vector& other) noexcept
		{
			return Vector(DirectX::XMVectorSubtract(_v, other._v));
		}

		inline Vector& operator -= (const Vector& other) noexcept
		{
			_v = DirectX::XMVectorSubtract(_v, other._v);
			return *this;
		}

		inline Vector operator * (const Vector& other) noexcept
		{
			return Vector(DirectX::XMVectorMultiply(_v, other._v));
		}

		inline Vector& operator *= (const Vector& other) noexcept
		{
			_v = DirectX::XMVectorMultiply(_v, other._v);
			return *this;
		}

		inline Vector operator * (float scalar) noexcept
		{
			return Vector(DirectX::XMVectorScale(_v, scalar));
		}

		inline Vector operator / (const Vector& other) noexcept
		{
			return Vector(DirectX::XMVectorDivide(_v, other._v));
		}

		inline Vector& operator /= (const Vector& other) noexcept
		{
			_v = DirectX::XMVectorDivide(_v, other._v);
			return *this;
		}

		inline bool operator == (const Vector& other) noexcept
		{
			static_assert(N >= 2 && N <= 4, "Invalid N dimension");

			if constexpr (N == 2)
				return DirectX::XMVector2Equal(_v, other._v);
			else if constexpr (N == 3)
				return DirectX::XMVector3Equal(_v, other._v);
			else
				return DirectX::XMVector4Equal(_v, other._v);
		}

		inline bool operator != (const Vector& other) noexcept
		{
			return !(*this == other);
		}

		inline bool operator < (const Vector& other) noexcept
		{
			static_assert(N >= 2 && N <= 4, "Invalid N dimension");

			if constexpr (N == 2)
				return DirectX::XMVector2Less(_v, other._v);
			else if constexpr (N == 3)
				return DirectX::XMVector3Less(_v, other._v);
			else
				return DirectX::XMVector4Less(_v, other._v);
		}

		inline bool operator <= (const Vector& other) noexcept
		{
			static_asser(N >= 2 && N <= 4, "Invalid N dimension");

			if constexpr (N == 2)
				return DirectX::XMVector2LessOrEqual(_v, other._v);
			else if constexpr (N == 3)
				return DirectX::XMVector3LessOrEqual(_v, other._v);
			else
				return DirectX::XMVector4LessOrEqual(_v, other._v);
		}

		inline bool operator > (const Vector& other) noexcept
		{
			static_assert(N >= 2 && N <= 4, "Invalid N dimension");

			if constexpr (N == 2)
				return DirectX::XMVector2Greater(_v, other._v);
			else if constexpr (N == 3)
				return DirectX::XMVector3Greater(_v, other._v);
			else
				return DirectX::XMVector4Greater(_v, other._v);
		}

		inline bool operator >= (const Vector& other) noexcept
		{
			static_asser(N >= 2 && N <= 4, "Invalid N dimension");

			if constexpr (N == 2)
				return DirectX::XMVector2GreaterOrEqual(_v, other._v);
			else if constexpr (N == 3)
				return DirectX::XMVector3GreaterOrEqual(_v, other._v);
			else
				return DirectX::XMVector4GreaterOrEqual(_v, other._v);
		}

		operator DirectX::XMVECTOR() const noexcept
		{
			return _v;
		}

	private:
		DirectX::XMVECTOR _v{};
	};

	using Vector2 = Vector<2>;
	using Vector3 = Vector<3>;
	using Vector4 = Vector<4>;
}

#endif // GRAPHLYMATH_VECTOR_HEADER
