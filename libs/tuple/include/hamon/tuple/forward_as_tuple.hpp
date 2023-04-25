/**
 *	@file	forward_as_tuple.hpp
 *
 *	@brief	forward_as_tuple の定義
 */

#ifndef HAMON_TUPLE_FORWARD_AS_TUPLE_HPP
#define HAMON_TUPLE_FORWARD_AS_TUPLE_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::forward_as_tuple;

}	// namespace hamon

#else

#include <hamon/tuple/tuple.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// Tuple creation functions	[tuple.creation]

template <typename... TTypes>
inline HAMON_CXX11_CONSTEXPR hamon::tuple<TTypes&&...>
forward_as_tuple(TTypes&&... t) HAMON_NOEXCEPT
{
	// [tuple.creation]/4
	return hamon::tuple<TTypes&&...>(hamon::forward<TTypes>(t)...);
}

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_FORWARD_AS_TUPLE_HPP
