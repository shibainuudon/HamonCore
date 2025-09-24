/**
 *	@file	valarray_range.hpp
 *
 *	@brief	valarray の定義
 */

#ifndef HAMON_VALARRAY_DETAIL_VALARRAY_RANGE_HPP
#define HAMON_VALARRAY_DETAIL_VALARRAY_RANGE_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 29.6.10 valarray range access[valarray.range]

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T*
begin(valarray<T>& v) HAMON_NOEXCEPT // noexcept as an extension
{
	return v.m_data;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T const*
begin(valarray<T> const& v) HAMON_NOEXCEPT // noexcept as an extension
{
	return v.m_data;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T*
end(valarray<T>& v) HAMON_NOEXCEPT // noexcept as an extension
{
	return v.m_data + v.size();
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T const*
end(valarray<T> const& v) HAMON_NOEXCEPT // noexcept as an extension
{
	return v.m_data + v.size();
}

}	// namespace hamon

#endif // HAMON_VALARRAY_DETAIL_VALARRAY_RANGE_HPP
