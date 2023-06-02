/**
 *	@file	nullopt.hpp
 *
 *	@brief	nullopt の定義
 */

#ifndef HAMON_OPTIONAL_NULLOPT_HPP
#define HAMON_OPTIONAL_NULLOPT_HPP

#include <hamon/optional/config.hpp>

#if defined(HAMON_USE_STD_OPTIONAL)

#include <optional>

namespace hamon
{

using std::nullopt_t;
using std::nullopt;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// [optional.nullopt], no-value state indicator
struct nullopt_t
{
	// [optional.nullopt]/1
	// [optional.nullopt]/2
	struct CtorTag {};
	explicit HAMON_CXX11_CONSTEXPR nullopt_t(CtorTag) HAMON_NOEXCEPT {}
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
nullopt_t nullopt{nullopt_t::CtorTag{}};

}	// namespace hamon

#endif

#endif // HAMON_OPTIONAL_NULLOPT_HPP
