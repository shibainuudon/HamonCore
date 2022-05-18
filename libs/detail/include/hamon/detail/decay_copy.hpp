/**
 *	@file	decay_copy.hpp
 *
 *	@brief	decay_copy の定義
 */

#ifndef HAMON_DETAIL_DECAY_COPY_HPP
#define HAMON_DETAIL_DECAY_COPY_HPP

#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR typename std::decay<T>::type
decay_copy(T&& t)
HAMON_NOEXCEPT_IF((std::is_nothrow_convertible<T, typename std::decay<T>::type>::value))
{
	return std::forward<T>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_DETAIL_DECAY_COPY_HPP
