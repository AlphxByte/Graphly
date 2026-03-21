#ifndef GRAPHLYMATH_HEADER
#define GRAPHLYMATH_HEADER

#include "Vector.h"
#include "FloatN.h"
#include "Matrix4x4.h"
#include "FloatNxM.h"

namespace GraphlyMath
{
	/**********************************************************
	* Vector Section
	* 
	***********************************************************/

	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorZero() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorOne() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitX() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitX(float x) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitY() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitY(float y) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitZ() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitZ(float z) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitW() noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorUnitW(float w) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorReplicate(float val) noexcept;
	template<std::size_t N>
	inline bool      GRAPHLYMATH_API VectorNearEqual(const Vector<N>& v, const Vector<N>& w, float epsilon) noexcept;
	template<std::size_t N>
	inline bool      GRAPHLYMATH_API VectorNearEqual(const Vector<N>& v, const Vector<N>& w, const Vector<N>& epsilon) noexcept;
	template<std::size_t N, typename... Args>
	inline Vector<N> GRAPHLYMATH_API VectorMin(Args&&... args) noexcept;
	template<std::size_t N, typename... Args>
	inline Vector<N> GRAPHLYMATH_API VectorMax(Args&&... args) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorRound(const Vector<N>& v) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorFloor(const Vector<N>& v) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorCeil(const Vector<N>& v) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorClamp(const Vector<N>& v, float min, float max) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorClamp(const Vector<N>& v, const Vector<N>& min, const Vector<N>& max) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorNegate(const Vector<N>& v) noexcept;
	template<std::size_t N>
	inline void      GRAPHLYMATH_API VectorAbs(const Vector<N>& v) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorLerp(const Vector<N>& v, const Vector<N>& w, float t) noexcept;
	template<std::size_t N>
	inline Vector<N> GRAPHLYMATH_API VectorLerp(const Vector<N>& v, const Vector<N>& w, const Vector<N>& t) noexcept;

	/**********************************************************
	* Float Section
	*
	***********************************************************/

	template<std::size_t N>
	Float<N> GRAPHLYMATH_API FloatZero() noexcept;
	template<std::size_t N>
	Float<N> GRAPHLYMATH_API FloatOne() noexcept;
	template<std::size_t N>
	Float<N> GRAPHLYMATH_API FloatReplicate(float val) noexcept;
	template<std::size_t N>
	bool     GRAPHLYMATH_API FloatNearEqual(const Float<N>& f0, const Float<N>& f1, float epsilon) noexcept;
	template<std::size_t N>
	bool     GRAPHLYMATH_API FloatNearEqual(const Float<N>& f0, const Float<N>& f1, const Float<N>& epsilon) noexcept;
	template<std::size_t N, typename... Args>
	Float<N> GRAPHLYMATH_API FloatMin(Args&&... args) noexcept;
	template<std::size_t N, typename... Args>
	Float<N> GRAPHLYMATH_API FloatMax(Args&&... args) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatRound(const Float<N>& f) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatFloor(const Float<N>& f) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatCeil(const Float<N>& f) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatClamp(const Float<N>& f, float min, float max) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatClamp(const Float<N>& f, const Float<N>& min, const Float<N>& max) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatNegate(const Float<N>& f) noexcept;
	template<std::size_t N>
	void     GRAPHLYMATH_API FloatAbs(const Float<N>& f) noexcept;
	template<std::size_t N>
	Float<N> GRAPHLYMATH_API FloatLerp(const Float<N>& f0, const Float<N>& f1, float t) noexcept;
	template<std::size_t N>
	Float<N> GRAPHLYMATH_API FloatLerp(const Float<N>& f0, const Float<N>& f1, const Float<N>& t) noexcept;

	/**********************************************************
	* Matrix4x4 Section
	*
	***********************************************************/

	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Identity() noexcept;
	inline bool      GRAPHLYMATH_API Matrix4x4IsIdentity(const Matrix4x4& m) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Transpose(const Matrix4x4& m) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Translation(float offset) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Translation(const Vector3& v) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Scale(float scale) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4Scale(const Vector3& v) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4RotationX(float angle) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4RotationY(float angle) noexcept;
	inline Matrix4x4 GRAPHLYMATH_API Matrix4x4RotationZ(float angle) noexcept;

	/**********************************************************
	* Helper Functions Section
	*
	***********************************************************/

	inline Vector2			GRAPHLYMATH_API ConvertFloat2ToVector2(const Float2& f2) noexcept;
	inline Vector3			GRAPHLYMATH_API ConvertFloat3ToVector3(const Float3& f3) noexcept;
	inline Vector4			GRAPHLYMATH_API ConvertFloat4ToVector4(const Float4& f4) noexcept;
	inline Float2			GRAPHLYMATH_API ConvertVector2ToFloat2(const Vector2& v2) noexcept;
	inline Float3			GRAPHLYMATH_API ConvertVector3ToFloat3(const Vector3& v3) noexcept;
	inline Float4			GRAPHLYMATH_API ConvertVector4ToFloat4(const Vector4& v4) noexcept;
	inline Matrix4x4		GRAPHLYMATH_API ConvertFloat4x4ToMatrix4x4(const Float4x4& f4x4) noexcept;
	inline Float4x4			GRAPHLYMATH_API ConvertMatrix4x4ToFloat4x4(const Matrix4x4& m4x4) noexcept;
	inline Float2			GRAPHLYMATH_API ConvertFloat4ToFloat2(const Float4& f4) noexcept;
	inline Float2			GRAPHLYMATH_API ConvertFloat3ToFloat2(const Float3& f3) noexcept;
	inline Float3           GRAPHLYMATH_API ConvertFloat4ToFloat3(const Float4& f4) noexcept;
	inline Float3           GRAPHLYMATH_API ConvertFloat2ToFloat3(const Float2& f2) noexcept;
	inline Float4           GRAPHLYMATH_API ConvertFloat3ToFloat4(const Float3& f3) noexcept;
	inline Float4           GRAPHLYMATH_API ConvertFloat2ToFloat4(const Float2& f2) noexcept;
	template<std::size_t N, std::size_t M>
	Float<M>                GRAPHLYMATH_API ConvertFloatNToFloatM(const Float<N>& fn) noexcept;
	inline Float3x3         GRAPHLYMATH_API ConvertFloat3x4ToFloat3x3(const Float3x4& f3x4) noexcept;
	inline Float3x3         GRAPHLYMATH_API ConvertFloat4x3ToFloat3x3(const Float4x3& f4x3) noexcept;
	inline Float3x3         GRAPHLYMATH_API ConvertFloat4x4ToFloat3x3(const Float4x4& f4x4) noexcept;
	inline Float4x4         GRAPHLYMATH_API ConvertFloat3x3ToFloat4x4(const Float3x3& f3x3) noexcept;
	inline Float4x4         GRAPHLYMATH_API ConvertFloat3x4ToFloat4x4(const Float3x4& f3x4) noexcept;
	inline Float4x4         GRAPHLYMATH_API ConvertFloat4x3ToFloat4x4(const Float4x3& f4x3) noexcept;
	template<std::size_t N1, std::size_t M1, std::size_t N2, std::size_t M2>
	FloatNxM<N2, M2>        GRAPHLYMATH_API ConvertFloatN1xM1ToFloatN2xM2(const FloatNxM<N1, M1>& m) noexcept;
}

#endif // GRAPHLYMATH_HEADER
