#ifndef GRAPHLYMATH_FLOATNxM_HEADER
#define GRAPHLYMATH_FLOATNxM_HEADER

#include "FloatN.h"
#include "GraphlyMathExports.h"

namespace GraphlyMath
{
	template<std::size_t N, std::size_t M>
	class FloatNxM final
	{
	public:
		FloatNxM() = default;

		FloatNxM(const std::initializer_list<std::initializer_list<float>>& initList)
		{
			*this = initList;
		}

		FloatNxM(const Float3& f0, const Float3& f1, const Float3& f2)
		{
			static_assert(N == 3 && M == 3, "Invalid dimensions");
			for (int i = 0; i < M; ++i)
			{
				_data[0][i] = f0[i];
				_data[1][i] = f1[i];
				_data[2][i] = f2[i];
			}
		}

		FloatNxM(const Float4& f0, const Float4& f1, const Float4& f2, const Float4& f3)
		{
			static_assert(N == 4 && M == 4, "Invalid dimensions");
			for (int i = 0; i < M; ++i)
			{
				_data[0][i] = f0[i];
				_data[1][i] = f1[i];
				_data[2][i] = f2[i];
				_data[3][i] = f3[i];
			}
		}

		FloatNxM(const std::array<std::array<float, M>, N>& array)
		: _data(array) {}

		FloatNxM(const std::array<Float<M>, N>& array)
		{
			*this = array;
		}

		FloatNxM(const std::vector<std::vector<float>>& vector)
		{
			*this = vector;
		}

		FloatNxM(const std::vector<Float<M>>& vector)
		{
			*this = vector;
		}

		FloatNxM(const FloatNxM& other)
		: _data(other._data) {}

		FloatNxM(FloatNxM&& other)
		: _data(std::forward<std::array<std::array<float, M>, N>>(other._data)) {}

		~FloatNxM() = default;

		FloatNxM& operator = (const std::initializer_list<std::initializer_list<float>>& initList)
		{
			assert(initList.size() == N);
			for (int i = 0; i < N; ++i)
			{
				assert(initList[i].size() == M);
				int j = 0;
				for (const auto& elem : initList[i])
				{
					_data[i][j] = elem;
					++j;
				}
			}

			return *this;
		}

		FloatNxM& operator = (const std::array<std::array<float, M>, N>& array)
		{
			_data = array;
			return *this;
		}

		FloatNxM& operator = (const std::array<Float<M>, N>& array)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] = array[i][j];

			return *this;
		}

		FloatNxM& operator = (const std::vector<std::vector<float>>& vector)
		{
			assert(vector.size() == N);
			for (int i = 0; i < N; ++i)
			{
				assert(vector[i].size() == M);
				for (int j = 0; j < M; ++j)
					_data[i][j] = vector[i][j];
			}

			return *this;
		}

		FloatNxM& operator = (const std::vector<Float<M>>& vector)
		{
			assert(vector.size() == N);
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] = vector[i][j];

			return *this;
		}

		FloatNxM& operator = (const FloatNxM& other)
		{
			if (*this == other)
				return *this;

			_data = other._data;
			return *this;
		}

		FloatNxM& operator = (FloatNxM&& other)
		{
			if (*this == other)
				return *this;

			_data = std::move(other._data);
			return *this;
		}

		FloatNxM operator + (float val)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					result._data[i][j] = _data[i][j] + val;

			return result;
		}

		FloatNxM operator + (const FloatNxM& other)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					result._data[i][j] = _data[i][j] + other._data[i][j];

			return result;
		}

		FloatNxM operator - (float val)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					result._data[i][j] = _data[i][j] - val;

			return result;
		}

		FloatNxM operator - (const FloatNxM& other)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					result._data[i][j] = _data[i][j] - other._data[i][j];

			return result;
		}

		FloatNxM operator * (float val)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					result._data[i][j] = _data[i][j] * val;

			return result;
		}

		FloatNxM operator * (const FloatNxM& other)
		{
			FloatNxM<N, M> result{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					for (int k = 0; k < M; ++k)
						result._data[i][j] += _data[i][j] * other._data[j][k];

			return result;
		}

		FloatNxM& operator += (float val)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] += val;

			return *this;
		}

		FloatNxM& operator += (const FloatNxM& other)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] += other._data[i][j];

			return *this;
		}

		FloatNxM& operator -= (float val)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] -= val;

			return *this;
		}

		FloatNxM& operator -= (const FloatNxM& other)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] -= other._data[i][j];

			return *this;
		}

		FloatNxM& operator *= (float val)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] *= val;

			return *this;
		}

		FloatNxM& operator *= (const FloatNxM& other)
		{
			FloatNxM<N, M> temp{};
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					for (int k = 0; k < M; ++k)
						temp._data[i][j] += _data[i][j] * other._data[j][k];

			_data = temp._data;
			return *this;
		}

		FloatNxM& operator ++ ()
		{
			*this += 1;
			return *this;
		}

		FloatNxM operator ++ (int)
		{
			FloatNxM<N, M> temp = *this + 1;
			return temp;
		}

		FloatNxM& operator -- ()
		{
			*this -= 1;
			return *this;
		}

		FloatNxM  operator -- (int)
		{
			FloatNxM<N, M> temp = *this - 1;
			return temp;
		}

		bool operator == (const FloatNxM& other)
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					if (_data[i][j] != other._data[i][j])
						return false;
			return true;
		}

		bool operator != (const FloatNxM& other)
		{
			return !(*this == other);
		}

		friend FloatNxM operator + (float val, const FloatNxM& f);
		friend FloatNxM operator * (float val, const FloatNxM& f);

		[[nodiscard]] float Get(unsigned i, unsigned j) const
		{
			assert(i < N && j < M);
			return _data[i][j];
		}

		[[nodiscard]] Float<M> GetLine(unsigned i) const
		{
			assert(i < N);
			return Float<M>(_data[i]);
		}

		void Set(float val, unsigned i, unsigned j)
		{
			assert(i < N && j < M);
			_data[i][j] = val;
		}

	private:
		std::array<std::array<float, M>, N> _data{};
	};

	using Float3x3 = FloatNxM<3, 3>;
	using Float3x4 = FloatNxM<3, 4>;
	using Float4x3 = FloatNxM<4, 3>;
	using Float4x4 = FloatNxM<4, 4>;

	template<std::size_t N, std::size_t M>
	FloatNxM<N, M> operator + (float val, const FloatNxM<N, M>& f)
	{
		return f + val;
	}

	template<std::size_t N, std::size_t M>
	FloatNxM<N, M> operator * (float val, const FloatNxM<N, M>& f)
	{
		return f * val;
	}
}

#endif // GRAPHLYMATH_FLOATNXM_HEADER