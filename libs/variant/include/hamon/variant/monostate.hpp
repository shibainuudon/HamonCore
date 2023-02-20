/**
 *	@file	monostate.hpp
 *
 *	@brief	monostate の定義
 */

#ifndef HAMON_VARIANT_MONOSTATE_HPP
#define HAMON_VARIANT_MONOSTATE_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::monostate;

}	// namespace hamon

#else

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [variant.monostate], class monostate
struct monostate{};

// [variant.monostate.relops], monostate relational operators
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator==(monostate, monostate) HAMON_NOEXCEPT { return true; }

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(monostate, monostate) HAMON_NOEXCEPT { return hamon::strong_ordering::equal; }

#else

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator< (monostate, monostate) HAMON_NOEXCEPT { return false; }
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator> (monostate, monostate) HAMON_NOEXCEPT { return false; }
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator<=(monostate, monostate) HAMON_NOEXCEPT { return true; }
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator>=(monostate, monostate) HAMON_NOEXCEPT { return true; }
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool operator!=(monostate, monostate) HAMON_NOEXCEPT { return false; }

#endif

// [variant.hash] hash support
// TODO hash support
//template<> struct hash<monostate>;

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_MONOSTATE_HPP
