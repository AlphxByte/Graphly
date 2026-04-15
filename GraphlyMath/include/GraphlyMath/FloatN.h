#ifndef GRAPHLYMATH_FLOATN_HEADER
#define GRAPHLYMATH_FLOATN_HEADER

#include <tuple>
#include <array>
#include <vector>
#include <initializer_list>

#include "GraphlyMathExports.h"

namespace GraphlyMath
{
	template<std::size_t N>
	class Float final
	{
	public:
		Float() = default;

		Float(const std::initializer_list<float>& initList)
		{
			*this = initList;
		}

		Float(float x, float y)
		{
			static_assert(N == 2, "Invalid N dimension");
			_data[0] = x;
			_data[1] = y;
		}

		Float(float x, float y, float z)
		{
			static_assert(N == 3, "Invalid N dimension");
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
		}

		Float(float x, float y, float z, float w)
		{
			static_assert(N == 4, "Invalid N dimension");
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
			_data[3] = w;
		}

		Float(const std::vector<float>& vector)
		{
			*this = vector;
		}

		Float(const std::array<float, N>& array)
		: _data(array) {}

		Float(std::array<float, N>&& array)
		: _data(std::move(array)) {}

		template<typename Iterator>
		Float(Iterator first, Iterator last)
		{
			for (int i = 0; i < N && first != last; ++i)
			{
				_data[i] = *first;
				first++;
			}
		}

		Float(const Float& other)
		: _data(other._data) {}

		Float(Float&& other)
		: _data(std::move(other._data)) {}

		~Float() = default;

		Float& operator = (const std::initializer_list<float>& initList)
		{
			assert(initList.size() == N);

			int i = 0;
			for (const auto& elem : initList)
			{
				_data[i] = elem;
				++i;
			}

			return *this;
		}

		Float& operator = (const std::vector<float>& vector)
		{
			assert(vector.size() == N);

			for (int i = 0; i < N; ++i)
				_data[i] = vector[i];
		}

		Float& operator = (const std::array<float, N>& array)
		{
			_data = array;
			return *this;
		}

		Float& operator = (std::array<float, N>&& array)
		{
			_data = std::move(array);
			return *this;
		}

		Float& operator = (const Float& other)
		{
			if (*this == other)
				return *this;

			_data = other._data;
			return *this;
		}

		Float& operator = (Float&& other)
		{
			if (*this == other)
				return *this;

			_data = std::move(other._data);
			return *this;
		}

		Float operator + (float val)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] + val;

			return result;
		}

		Float operator + (const Float& other)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] + other._data[i];

			return result;
		}

		Float operator - (float val)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] - val;

			return result;
		}

		Float operator - (const Float& other)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] - other._data[i];

			return result;
		}

		Float operator * (float val)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] * val;

			return result;
		}

		Float operator * (const Float& other)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] * other._data[i];

			return result;
		}

		Float operator / (float val)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] / val;

			return result;
		}

		Float operator / (const Float& other)
		{
			Float<N> result{};
			for (int i = 0; i < N; ++i)
				result._data[i] = this->_data[i] / other._data[i];

			return result;
		}

		Float& operator += (float val)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] += val;

			return *this;
		}

		Float& operator += (const Float& other)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] += other._data[i];

			return *this;
		}

		Float& operator -= (float val)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] -= val;

			return *this;
		}

		Float& operator -= (const Float& other)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] -= other._data[i];

			return *this;
		}

		Float& operator *= (float val)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] *= val;

			return *this;
		}

		Float& operator *= (const Float& other)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] *= other._data[i];

			return *this;
		}

		Float& operator /= (float val)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] /= val;

			return *this;
		}

		Float& operator /= (const Float& other)
		{
			for (int i = 0; i < N; ++i)
				this->_data[i] /= other._data[i];

			return *this;
		}

		Float& operator ++ ()
		{
			*this += 1;
			return *this;
		}

		Float  operator ++ (int)
		{
			Float<N> copy{};
			copy = *this + 1;
			return copy;
		}

		Float& operator -- ()
		{
			*this -= 1;
			return *this;
		}

		Float  operator -- (int)
		{
			Float<N> copy{};
			copy = *this - 1;
			return copy;
		}

		bool operator == (const Float& other)
		{
			for (int i = 0; i < N; ++i)
				if (_data[i] != other._data[i])
					return false;
			return true;
		}

		bool operator != (const Float& other)
		{
			return !(*this == other);
		}

		auto operator <=> (const Float& other)
		{
			auto res = _data[0] <=> other._data;
			for (int i = 1; i < N; ++i)
				if (_data[i] <=> other._data[i] != res)
					return _data[i] <=> other._data[i];
			return res;
		}

		friend Float operator + (float val, const Float& f);
		friend Float operator * (float val, const Float& f);

		[[nodiscard]] float& operator [] (unsigned i)
		{
			assert(i < N);
			return _data[i];
		}

		[[nodiscard]] const float& operator [] (unsigned i) const
		{
			assert(i < N);
			return _data[i];
		}

		[[nodiscard]] float Get(unsigned index)
		{
			assert(index < N);
			return _data[index];
		}

		void Set(float val, unsigned index)
		{
			assert(index < N);
			_data[index] = val;
		}

	private:
		std::array<float, N> _data{};
	};

	using Float2 = Float<2>;
	using Float3 = Float<3>;
	using Float4 = Float<4>;

	template<std::size_t N>
	Float<N> operator + (float val, const Float<N>& f)
	{
		return f + val;
	}

	template<std::size_t N>
	Float<N> operator * (float val, const Float<N>& f)
	{
		return f * val;
	}

	template<std::size_t N>
	std::istream& operator >> (std::istream& in, Float<N>& f)
	{
		std::vector<float> v{};
		for (int i = 0; i < N; ++i)
		{
			float val;
			in >> val;
			v.push_back(val);
		}

		f = Float<N>(v);
		return in;
	}

	template<std::size_t N>
	std::ostream& operator << (std::ostream& out, const Float<N>& f)
	{
		std::vector<float> v{};
		for (int i = 0; i < N; ++i)
			out << f[i] << ' ';
		out << '\n';

		return out;
	}
}

#endif // GRAPHLYMATH_FLOATN_HEADER
