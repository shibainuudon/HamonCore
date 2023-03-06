/**
 *	@file	decay_copy.hpp
 *
 *	@brief	decay_copy の定義
 */

#ifndef HAMON_DETAIL_DECAY_COPY_HPP
#define HAMON_DETAIL_DECAY_COPY_HPP

#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR hamon::decay_t<T>
decay_copy(T&& t)
HAMON_NOEXCEPT_IF((hamon::is_nothrow_convertible<T, hamon::decay_t<T>>::value))
{
	return hamon::forward<T>(t);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_DECAY_COPY_HPP
