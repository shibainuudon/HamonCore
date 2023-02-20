/**
 *	@file	holds_alternative.hpp
 *
 *	@brief	holds_alternative の定義
 */

#ifndef HAMON_VARIANT_HOLDS_ALTERNATIVE_HPP
#define HAMON_VARIANT_HOLDS_ALTERNATIVE_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::holds_alternative;

}	// namespace hamon

#else

#include <hamon/variant/detail/exactly_once.hpp>
#include <hamon/variant/detail/find_index.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [variant.get], value access
template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR bool
holds_alternative(variant<Types...> const& v) HAMON_NOEXCEPT
{
	// [variant.get]/1
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/2
	return v.index() == variant_detail::find_index<T, Types...>::value;
}

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_HOLDS_ALTERNATIVE_HPP
