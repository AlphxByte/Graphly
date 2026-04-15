#ifndef GRAPHLYMATH_MATRIX4X4_HEADER
#define GRAPHLYMATH_MATRIX4X4_HEADER

#include <DirectXMath.h>
#include "Vector.h"

#include "GraphlyMathExports.h"

namespace GraphlyMath
{
	class alignas(16) Matrix4x4 final
	{
	public:
		Matrix4x4() noexcept
		: _matrix(DirectX::XMMatrixSet(0.0f, 0.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 0.0f))
		{}

		Matrix4x4(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12, float m13,
				  float m20, float m21, float m22, float m23,
				  float m30, float m31, float m32, float m33) noexcept
		: _matrix(DirectX::XMMatrixSet(m00, m01, m02, m03,
									   m10, m11, m12, m13,
									   m20, m21, m22, m23,
									   m30, m31, m32, m33))
		{}

		Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3) noexcept
		{
			_matrix.r[0] = DirectX::XMVectorSet(v0.GetX(), v0.GetY(), v0.GetZ(), v0.GetW());
			_matrix.r[1] = DirectX::XMVectorSet(v1.GetX(), v1.GetY(), v1.GetZ(), v1.GetW());
			_matrix.r[2] = DirectX::XMVectorSet(v2.GetX(), v2.GetY(), v2.GetZ(), v2.GetW());
			_matrix.r[3] = DirectX::XMVectorSet(v3.GetX(), v3.GetY(), v3.GetZ(), v3.GetW());
		}

		Matrix4x4(DirectX::XMMATRIX m) noexcept
		: _matrix(m) {}

		Matrix4x4(DirectX::XMVECTOR v0, 
				  DirectX::XMVECTOR v1, 
				  DirectX::XMVECTOR v2, 
				  DirectX::XMVECTOR v3) noexcept
		{
			_matrix.r[0] = v0;
			_matrix.r[1] = v1;
			_matrix.r[2] = v2;
			_matrix.r[3] = v3;
		}

		Matrix4x4(const Matrix4x4& other) noexcept
		: _matrix(other._matrix)
		{}

		Matrix4x4(Matrix4x4&& other) noexcept
		: _matrix(other._matrix)
		{}

		~Matrix4x4() = default;

		[[nodiscard]] inline float Get(unsigned i, unsigned j) const noexcept
		{
			assert(i < 4 && j < 4);

			switch (j)
			{
			case 0:
				return DirectX::XMVectorGetX(_matrix.r[i]);
			case 1:
				return DirectX::XMVectorGetY(_matrix.r[i]);
			case 2:
				return DirectX::XMVectorGetZ(_matrix.r[i]);
			case 3:
				return DirectX::XMVectorGetW(_matrix.r[i]);
			}
		}

		[[nodiscard]] inline DirectX::XMVECTOR GetLine(unsigned i) const noexcept
		{
			assert(i < 4);
			return _matrix.r[i];
		}

		inline void Set(float val, unsigned i, unsigned j) noexcept
		{
			assert(i < 4 && j < 4);

			switch (j)
			{
			case 0:
				_matrix.r[i] = DirectX::XMVectorSetX(_matrix.r[i], val);
			case 1:
				_matrix.r[i] = DirectX::XMVectorSetY(_matrix.r[i], val);
			case 2:
				_matrix.r[i] = DirectX::XMVectorSetZ(_matrix.r[i], val);
			case 3:
				_matrix.r[i] = DirectX::XMVectorSetW(_matrix.r[i], val);
			}
		}

		inline Matrix4x4& operator = (const Matrix4x4& other) noexcept
		{
			_matrix = other._matrix;
			return *this;
		}

		inline Matrix4x4& operator = (Matrix4x4&& other) noexcept
		{
			if (*this == other)
				return *this;

			_matrix = std::move(other._matrix);
			return *this;
		}

		inline Matrix4x4& operator = (DirectX::XMMATRIX other) noexcept
		{
			_matrix = other;
			return *this;
		}

		inline Matrix4x4 operator + (const Matrix4x4& other) noexcept
		{
			return Matrix4x4(_matrix + other._matrix);
		}

		inline Matrix4x4& operator += (const Matrix4x4& other) noexcept
		{
			_matrix = _matrix + other._matrix;
			return *this;
		}

		inline Matrix4x4 operator - (const Matrix4x4& other) noexcept
		{
			return Matrix4x4(_matrix - other._matrix);
		}

		inline Matrix4x4& operator -= (const Matrix4x4& other) noexcept
		{
			_matrix = _matrix - other._matrix;
			return *this;
		}

		inline Matrix4x4 operator * (const Matrix4x4& other) noexcept
		{
			return Matrix4x4(DirectX::XMMatrixMultiply(_matrix, other._matrix));
		}

		inline Matrix4x4& operator *= (const Matrix4x4& other) noexcept
		{
			_matrix = DirectX::XMMatrixMultiply(_matrix, other._matrix);
			return *this;
		}

		inline bool operator == (const Matrix4x4& other) noexcept
		{
			return DirectX::XMVector4Equal(_matrix.r[0], other._matrix.r[0])
				&& DirectX::XMVector4Equal(_matrix.r[1], other._matrix.r[1])
				&& DirectX::XMVector4Equal(_matrix.r[2], other._matrix.r[2])
				&& DirectX::XMVector4Equal(_matrix.r[3], other._matrix.r[3]);
		}

		inline bool operator != (const Matrix4x4& other) noexcept
		{
			return !(*this == other);
		}

		inline operator DirectX::XMMATRIX() const
		{
			return _matrix;
		}

	private:
		DirectX::XMMATRIX _matrix{};
	};
}

#endif // GRAPHLYMATH_MATRIX4X4_HEADER
