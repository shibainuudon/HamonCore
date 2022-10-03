/**
 *	@file	decay_copy.hpp
 *
 *	@brief	decay_copy の定義
 */

#ifndef HAMON_RANGES_DETAIL_DECAY_COPY_HPP
#define HAMON_RANGES_DETAIL_DECAY_COPY_HPP

#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename T>
HAMON_CONSTEXPR hamon::decay_t<T>
decay_copy(T&& t)
HAMON_NOEXCEPT_IF((hamon::is_nothrow_convertible<T, hamon::decay_t<T>>::value))
{
	return std::forward<T>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_DECAY_COPY_HPP
