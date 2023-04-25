/**
 *	@file	tie.hpp
 *
 *	@brief	tie の定義
 */

#ifndef HAMON_TUPLE_TIE_HPP
#define HAMON_TUPLE_TIE_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::tie;
using std::ignore;

}	// namespace hamon

#else

#include <hamon/tuple/tuple.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// Tuple creation functions	[tuple.creation]

template <typename... TTypes>
inline HAMON_CXX11_CONSTEXPR hamon::tuple<TTypes&...>
tie(TTypes&... t) HAMON_NOEXCEPT
{
	// [tuple.creation]/5
	return hamon::tuple<TTypes&...>(t...);
}

namespace tuple_detail
{

struct ignore_t
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR ignore_t const&
	operator=(T const&) const HAMON_NOEXCEPT
	{
		return *this;
	}
};

}	// namespace tuple_detail

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
tuple_detail::ignore_t ignore{};

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_TIE_HPP
