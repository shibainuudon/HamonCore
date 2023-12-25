/**
 *	@file	as_lvalue.hpp
 *
 *	@brief	as_lvalue の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_AS_LVALUE_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_AS_LVALUE_HPP

namespace hamon {
namespace ranges {
namespace detail {

// 26.7.5 Range adaptor helpers[range.adaptor.helpers]

template <typename T>
constexpr T& as_lvalue(T&& t)
{
	return static_cast<T&>(t);
}

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_AS_LVALUE_HPP
