/**
 *	@file	valarray_binary.hpp
 *
 *	@brief	valarray の定義
 */

#ifndef HAMON_VALARRAY_DETAIL_VALARRAY_BINARY_HPP
#define HAMON_VALARRAY_DETAIL_VALARRAY_BINARY_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.3.1 Binary operators[valarray.binary]

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator*(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] * rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator*(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] * rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator*(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs * rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator/(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] / rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator/(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] / rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator/(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs / rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator%(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] % rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator%(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] % rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator%(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs % rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator+(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] + rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator+(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] + rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator+(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs + rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator-(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] - rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator-(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] - rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator-(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs - rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator^(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] ^ rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator^(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] ^ rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator^(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs ^ rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator&(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] & rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator&(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] & rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator&(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs & rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator|(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] | rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator|(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs[i] | rhs;
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator|(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = lhs | rhs[i];
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator<<(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs[i] << rhs[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator<<(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs[i] << rhs);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator<<(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs << rhs[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator>>(valarray<T> const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs[i] >> rhs[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator>>(valarray<T> const& lhs, typename valarray<T>::value_type const& rhs)
{
	hamon::size_t const size = lhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs[i] >> rhs);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
operator>>(typename valarray<T>::value_type const& lhs, valarray<T> const& rhs)
{
	hamon::size_t const size = rhs.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = static_cast<T>(lhs >> rhs[i]);
	}
	return result;
}

}	// namespace hamon

#endif // HAMON_VALARRAY_DETAIL_VALARRAY_BINARY_HPP
