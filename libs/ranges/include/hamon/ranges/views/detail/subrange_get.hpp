/**
 *	@file	subrange_get.hpp
 *
 *	@brief	subrange_get の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_GET_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_GET_HPP

#include <hamon/config.hpp>
#include <cstddef>

namespace hamon {
namespace ranges {
namespace detail {

template <std::size_t N>
struct subrange_get;

template <>
struct subrange_get<0>
{
	template <typename R>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.begin())
	{
		return r.begin();
	}
};
template <>
struct subrange_get<1>
{
	template <typename R>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.end())
	{
		return r.end();
	}
};

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_GET_HPP
