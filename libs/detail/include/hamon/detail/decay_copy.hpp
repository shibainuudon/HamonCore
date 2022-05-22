/**
 *	@file	decay_copy.hpp
 *
 *	@brief	decay_copy の定義
 */

#ifndef HAMON_DETAIL_DECAY_COPY_HPP
#define HAMON_DETAIL_DECAY_COPY_HPP

#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR typename std::decay<T>::type
decay_copy(T&& t)
HAMON_NOEXCEPT_IF((hamon::is_nothrow_convertible<T, typename std::decay<T>::type>::value))
{
	return std::forward<T>(t);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_DECAY_COPY_HPP
