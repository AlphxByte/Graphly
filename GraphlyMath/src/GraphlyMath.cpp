#include "GraphlyMath/GraphlyMath.h"

#include <limits>

using namespace GraphlyMath;
using namespace DirectX;

namespace GraphlyMath
{
	/**********************************************************
	* Vector Section
	*
	***********************************************************/

	template<std::size_t N>
	inline Vector<N> VectorZero() noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(0.0f, 0.0f);
		else if constexpr (N == 3)
			return Vector3(0.0f, 0.0f, 0.0f);
		else
			return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorOne() noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(1.0f, 1.0f);
		else if constexpr (N == 3)
			return Vector3(1.0f, 1.0f, 1.0f);
		else
			return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitX() noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(1.0f, 0.0f);
		else if constexpr (N == 3)
			return Vector3(1.0f, 0.0f, 0.0f);
		else
			return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitX(float x) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(x, 0.0f);
		else if constexpr (N == 3)
			return Vector3(x, 0.0f, 0.0f);
		else
			return Vector4(x, 0.0f, 0.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitY() noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(0.0f, 1.0f);
		else if constexpr (N == 3)
			return Vector3(0.0f, 1.0f, 0.0f);
		else
			return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitY(float y) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(0.0f, y);
		else if constexpr (N == 3)
			return Vector3(0.0f, y, 0.0f);
		else
			return Vector4(0.0f, y, 0.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitZ() noexcept
	{
		static_assert(N >= 3 && N <= 4, "Invalid N dimension");

		if constexpr (N == 3)
			return Vector3(0.0f, 0.0f, 1.0f);
		else
			return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitZ(float z) noexcept
	{
		static_assert(N >= 3 && N <= 4, "Invalid N dimension");

		if constexpr (N == 3)
			return Vector3(0.0f, 0.0f, z);
		else
			return Vector4(0.0f, 0.0f, z, 0.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitW() noexcept
	{
		static_assert(N == 4, "Invalid N dimension");

		if constexpr (N == 4)
			return Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	template<std::size_t N>
	inline Vector<N> VectorUnitW(float w) noexcept
	{
		static_assert(N == 4, "Invalid N dimension");

		if constexpr (N == 4)
			return Vector4(0.0f, 0.0f, 0.0f, w);
	}

	template<std::size_t N>
	inline Vector<N> VectorReplicate(float val) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return Vector2(val, val);
		else if constexpr (N == 3)
			return Vector3(val, val, val);
		else
			return Vector4(val, val, val, val);
	}

	template<std::size_t N>
	bool VectorNearEqual(const Vector<N>& v, const Vector<N>& w, float epsilon) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return XMVector2NearEqual(v, w, XMVectorReplicate(epsilon));
		else if constexpr (N == 3)
			return XMVector3NearEqual(v, w, XMVectorReplicate(epsilon));
		else
			return XMVector4NearEqual(v, w, XMVectorReplicate(epsilon));
	}

	template<std::size_t N>
	inline bool VectorNearEqual(const Vector<N>& v, const Vector<N>& w, const Vector<N>& epsilon) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		if constexpr (N == 2)
			return XMVector2NearEqual(v, w, epsilon);
		else if constexpr (N == 3)
			return XMVector3NearEqual(v, w, epsilon);
		else
			return XMVector4NearEqual(v, w, epsilon);
	}

	template<std::size_t N, typename... Args>
	inline Vector<N> VectorMin(Args&& ...args) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		Vector<N> result = VectorReplicate<N>(std::numeric_limits<float>::max());
		for (const auto& v : args)
			result = XMVectorMin(result, v);

		return result;
	}

	template<std::size_t N, typename... Args>
	inline Vector<N> VectorMax(Args&& ...args) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");

		Vector<N> result = VectorReplicate<N>(std::numeric_limits<float>::min());
		for (const auto& v : args)
			result = XMVectorMax(result, v);

		return result;
	}

	template<std::size_t N>
	inline void VectorRound(const Vector<N>& v) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		return XMVectorRound(v);
	}

	template<std::size_t N>
	inline void VectorFloor(const Vector<N>& v) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorFloor(v);
	}

	template<std::size_t N>
	inline void VectorCeil(const Vector<N>& v) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorCeiling(v);
	}

	template<std::size_t N>
	inline void VectorClamp(const Vector<N>& v, float min, float max) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorClamp(v, XMVectorReplicate(min), XMVectorReplicate(max));
	}

	template<std::size_t N>
	inline void VectorClamp(const Vector<N>& v, const Vector<N>& min, const Vector<N>& max) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorClamp(v, min, max);
	}

	template<std::size_t N>
	inline void VectorNegate(const Vector<N>& v) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorNegate(v);
	}

	template<std::size_t N>
	inline void VectorAbs(const Vector<N>& v) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		v = XMVectorAbs(v);
	}

	template<std::size_t N>
	inline Vector<N> VectorLerp(const Vector<N>& v, const Vector<N>& w, float t) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		return XMVectorLerp(v, w, t);
	}

	template<std::size_t N>
	inline Vector<N> VectorLerp(const Vector<N>& v, const Vector<N>& w, const Vector<N>& t) noexcept
	{
		static_assert(N >= 2 && N <= 4, "Invalid N dimension");
		return XMVectorLerpV(v, w, t);
	}

	/**********************************************************
	* Float Section
	*
	***********************************************************/

	template<std::size_t N>
	Float<N> FloatZero() noexcept
	{
		if constexpr (N == 2)
			return Float2(0.0f, 0.0f);
		else if constexpr (N == 3)
			return Float3(0.0f, 0.0f, 0.0f);
		else if constexpr (N == 4)
			return Float4(0.0f, 0.0f, 0.0f, 0.0f);

		Float<N> result{};
		for (int i = 0; i < N; ++i)
			result[i] = 0.0f;
		return result;
	}

	template<std::size_t N>
	Float<N> FloatOne() noexcept
	{
		if constexpr (N == 2)
			return Float2(1.0f, 1.0f);
		else if constexpr (N == 3)
			return Float3(1.0f, 1.0f, 1.0f);
		else if constexpr (N == 4)
			return Float4(1.0f, 1.0f, 1.0f, 1.0f);

		Float<N> result{};
		for (int i = 0; i < N; ++i)
			result[i] = 1.0f;
		return result;
	}

	template<std::size_t N>
	Float<N> FloatReplicate(float val) noexcept
	{
		if constexpr (N == 2)
			return Float2(val, val);
		else if constexpr (N == 3)
			return Float3(val, val, val);
		else if constexpr (N == 4)
			return Float4(val, val, val, val);

		Float<N> result{};
		for (int i = 0; i < N; ++i)
			result[i] = val;
		return result;
	}

	template<std::size_t N>
	bool FloatNearEqual(const Float<N>& f0, const Float<N>& f1, float epsilon) noexcept
	{
		for (int i = 0; i < N; ++i)
			if (abs(f0[i] - f1[i]) >= epsilon)
				return false;
		return true;
	}

	template<std::size_t N>
	bool FloatNearEqual(const Float<N>& f0, const Float<N>& f1, const Float<N>& epsilon) noexcept
	{
		for (int i = 0; i < N; ++i)
			if (abs(f0[i] - f1[i]) >= epsilon[i])
				return false;
		return true;
	}

	template<std::size_t N, typename ...Args>
	Float<N> FloatMin(Args && ...args) noexcept
	{
		Float<N> result = FloatReplicate<N>(std::numeric_limits<float>::max());
		for (const auto& arg : args)
			if (arg < result)
				result = arg;
		return result;
	}

	template<std::size_t N, typename ...Args>
	Float<N> FloatMax(Args && ...args) noexcept
	{
		Float<N> result = FloatReplicate<N>(std::numeric_limits<float>::min());
		for (const auto& arg : args)
			if (arg > result)
				result = arg;
		return result;
	}

	template<std::size_t N>
	void FloatRound(const Float<N>& f) noexcept
	{
		for (int i = 0; i < N; ++i)
			f[i] = round(f[i]);
	}

	template<std::size_t N>
	void FloatFloor(const Float<N>& f) noexcept
	{
		for (int i = 0; i < N; ++i)
			f[i] = floor(f[i]);
	}

	template<std::size_t N>
	void FloatCeil(const Float<N>& f) noexcept
	{
		for (int i = 0; i < N; ++i)
			f[i] = ceil(f[i]);
	}

	template<std::size_t N>
	void FloatClamp(const Float<N>& f, float min, float max) noexcept
	{
		for (int i = 0; i < N; ++i)
			if (f[i] < min)
				f[i] = min;
			else if (f[i] > max)
				f[i] = max;
	}

	template<std::size_t N>
	void FloatClamp(const Float<N>& f, const Float<N>& min, const Float<N>& max) noexcept
	{
		for (int i = 0; i < N; ++i)
			if (f[i] < min[i])
				f[i] = min[i];
			else if (f[i] > max[i])
				f[i] = max[i];
	}

	template<std::size_t N>
	void FloatNegate(const Float<N>& f) noexcept
	{
		for (int i = 0; i < N; ++i)
			f[i] = -f[i];
	}

	template<std::size_t N>
	void FloatAbs(const Float<N>& f) noexcept
	{
		for (int i = 0; i < N; ++i)
			f[i] = abs(f[i]);
	}

	template<std::size_t N>
	Float<N> FloatLerp(const Float<N>& f0, const Float<N>& f1, float t) noexcept
	{
		Float<N> result{};
		for (int i = 0; i < N; ++i)
			result[i] = f0[i] + t * (f1[i] - f0[i]);
		return result;
	}

	template<std::size_t N>
	Float<N> FloatLerp(const Float<N>& f0, const Float<N>& f1, const Float<N>& t) noexcept
	{
		Float<N> result{};
		for (int i = 0; i < N; ++i)
			result[i] = f0[i] + t[i] * (f1[i] - f0[i]);
		return result;
	}

	/**********************************************************
	* Matrix4x4 Section
	*
	***********************************************************/

	inline Matrix4x4 Matrix4x4Identity() noexcept
	{
		return DirectX::XMMatrixIdentity();
	}

	inline bool Matrix4x4IsIdentity(const Matrix4x4& m) noexcept
	{
		return DirectX::XMMatrixIsIdentity(m);
	}

	inline Matrix4x4 Matrix4x4Transpose(const Matrix4x4& m) noexcept
	{
		return DirectX::XMMatrixTranspose(m);
	}

	inline Matrix4x4 Matrix4x4Translation(float offset) noexcept
	{
		return DirectX::XMMatrixTranslation(offset, offset, offset);
	}

	inline Matrix4x4 Matrix4x4Translation(const Vector3& v) noexcept
	{
		return DirectX::XMMatrixTranslationFromVector(v);
	}

	inline Matrix4x4 Matrix4x4Scale(float scale) noexcept
	{
		return DirectX::XMMatrixScaling(scale, scale, scale);
	}

	inline Matrix4x4 Matrix4x4Scale(const Vector3& v) noexcept
	{
		return DirectX::XMMatrixScalingFromVector(v);
	}

	inline Matrix4x4 Matrix4x4RotationX(float angle) noexcept
	{
		return DirectX::XMMatrixRotationX(angle);
	}

	inline Matrix4x4 Matrix4x4RotationY(float angle) noexcept
	{
		return DirectX::XMMatrixRotationY(angle);
	}

	inline Matrix4x4 Matrix4x4RotationZ(float angle) noexcept
	{
		return DirectX::XMMatrixRotationZ(angle);
	}

	/**********************************************************
	* Helper Functions Section
	*
	***********************************************************/

	inline Vector2 ConvertFloat2ToVector2(const Float2& f2) noexcept
	{
		return Vector2(f2[0], f2[1]);
	}

	inline Vector3 ConvertFloat3ToVector3(const Float3& f3) noexcept
	{
		return Vector3(f3[0], f3[1], f3[2]);
	}

	inline Vector4 ConvertFloat4ToVector4(const Float4& f4) noexcept
	{
		return Vector4(f4[0], f4[1], f4[2], f4[3]);
	}

	inline Float2 ConvertVector2ToFloat2(const Vector2& v2) noexcept
	{
		return Float2(v2.GetX(), v2.GetY());
	}

	inline Float3 ConvertVector3ToFloat3(const Vector3& v3) noexcept
	{
		return Float3(v3.GetX(), v3.GetY(), v3.GetZ());
	}

	inline Float4 ConvertVector4ToFloat4(const Vector4& v4) noexcept
	{
		return Float4(v4.GetX(), v4.GetY(), v4.GetZ(), v4.GetW());
	}

	inline Matrix4x4 ConvertFloat4x4ToMatrix4x4(const Float4x4& f4x4) noexcept
	{
		return Matrix4x4(
			ConvertFloat4ToVector4(f4x4.GetLine(0)),
			ConvertFloat4ToVector4(f4x4.GetLine(1)),
			ConvertFloat4ToVector4(f4x4.GetLine(2)),
			ConvertFloat4ToVector4(f4x4.GetLine(3))
		);
	}

	inline Float4x4 ConvertMatrix4x4ToFloat4x4(const Matrix4x4& m4x4) noexcept
	{
		return Float4x4(
			ConvertVector4ToFloat4(m4x4.GetLine(0)),
			ConvertVector4ToFloat4(m4x4.GetLine(1)),
			ConvertVector4ToFloat4(m4x4.GetLine(2)),
			ConvertVector4ToFloat4(m4x4.GetLine(3))
		);
	}

	inline Float2 ConvertFloat4ToFloat2(const Float4& f4) noexcept
	{
		return Float2(f4[0], f4[1]);
	}

	inline Float2 ConvertFloat3ToFloat2(const Float3& f3) noexcept
	{
		return Float2(f3[0], f3[1]);
	}

	inline Float3 ConvertFloat4ToFloat3(const Float4& f4) noexcept
	{
		return Float3(f4[0], f4[1], f4[2]);
	}

	inline Float3 ConvertFloat2ToFloat3(const Float2& f2) noexcept
	{
		return Float3(f2[0], f2[1], 0.0f);
	}

	inline Float4 ConvertFloat3ToFloat4(const Float3& f3) noexcept
	{
		return Float4(f3[0], f3[1], f3[2], 0.0f);
	}

	inline Float4 ConvertFloat2ToFloat4(const Float2& f2) noexcept
	{
		return Float4(f2[0], f2[1], 0.0f, 0.0f);
	}

	template<std::size_t N, std::size_t M>
	Float<M> ConvertFloatNToFloatM(const Float<N>& fn) noexcept
	{
		if constexpr (N == M)
			return fn;
		else if constexpr (N > M)
		{
			Float<M> result{};
			for (int i = 0; i < M; ++i)
				result[i] = fn[i];
			return result;
		}
		else
		{
			Float<M> result{};
			for (int i = 0; i < N; ++i)
				result[i] = fn[i];
			for (int i = N; i < M; ++i)
				result[i] = 0.0f;
			return result;
		}
	}

	inline Float3x3 ConvertFloat3x4ToFloat3x3(const Float3x4& f3x4) noexcept
	{
		return Float3x3(
			ConvertFloat4ToFloat3(f3x4.GetLine(0)),
			ConvertFloat4ToFloat3(f3x4.GetLine(1)),
			ConvertFloat4ToFloat3(f3x4.GetLine(2))
		);
	}

	inline Float3x3 ConvertFloat4x3ToFloat3x3(const Float4x3& f4x3) noexcept
	{
		return Float3x3(
			f4x3.GetLine(0),
			f4x3.GetLine(1),
			f4x3.GetLine(2)
		);
	}
	inline Float3x3 ConvertFloat4x4ToFloat3x3(const Float4x4& f4x4) noexcept
	{
		return Float3x3(
			ConvertFloat4ToFloat3(f4x4.GetLine(0)),
			ConvertFloat4ToFloat3(f4x4.GetLine(1)),
			ConvertFloat4ToFloat3(f4x4.GetLine(2))
		);
	}
	
	inline Float4x4 ConvertFloat3x3ToFloat4x4(const Float3x3& f3x3) noexcept
	{
		return Float4x4(
			ConvertFloat3ToFloat4(f3x3.GetLine(0)),
			ConvertFloat3ToFloat4(f3x3.GetLine(1)),
			ConvertFloat3ToFloat4(f3x3.GetLine(2)),
			Float4(0.0f, 0.0f, 0.0f, 0.0f)
		);
	}

	inline Float4x4 ConvertFloat3x4ToFloat4x4(const Float3x4& f3x4) noexcept
	{
		return Float4x4(
			f3x4.GetLine(0),
			f3x4.GetLine(1),
			f3x4.GetLine(2),
			Float4(0.0f, 0.0f, 0.0f, 0.0f)
		);
	}

	inline Float4x4 ConvertFloat4x3ToFloat4x4(const Float4x3& f4x3) noexcept
	{
		return Float4x4(
			ConvertFloat3ToFloat4(f4x3.GetLine(0)),
			ConvertFloat3ToFloat4(f4x3.GetLine(1)),
			ConvertFloat3ToFloat4(f4x3.GetLine(2)),
			ConvertFloat3ToFloat4(f4x3.GetLine(3))
		);
	}

	template<std::size_t N1, std::size_t M1, std::size_t N2, std::size_t M2>
	FloatNxM<N2, M2> ConvertFloatN1xM1ToFloatN2xM2(const FloatNxM<N1, M1>& m) noexcept
	{
		FloatNxM<N2, M2> result{};
		for (int i = 0; i < N2; ++i)
			for (int j = 0; j < M2; ++j)
				if (i < N1 && j < M1)
					result.Set(m.Get(i, j), i, j);
				else
					result.Set(0.0f, i, j);

		return result;
	}
}
