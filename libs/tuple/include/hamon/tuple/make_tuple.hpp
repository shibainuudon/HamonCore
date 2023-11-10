/**
 *	@file	make_tuple.hpp
 *
 *	@brief	make_tuple の定義
 */

#ifndef HAMON_TUPLE_MAKE_TUPLE_HPP
#define HAMON_TUPLE_MAKE_TUPLE_HPP

#include <hamon/tuple/config.hpp>
#include <hamon/tuple/tuple.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::make_tuple;

}	// namespace hamon

#else

#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// Tuple creation functions	[tuple.creation]

template <typename... TTypes>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::tuple<hamon::unwrap_ref_decay_t<TTypes>...>
make_tuple(TTypes&&... t)
{
	// [tuple.creation]/1
	return hamon::tuple<hamon::unwrap_ref_decay_t<TTypes>...>(hamon::forward<TTypes>(t)...);
}

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_MAKE_TUPLE_HPP
