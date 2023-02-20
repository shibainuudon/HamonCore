/**
 *	@file	variant_npos.hpp
 *
 *	@brief	variant_npos の定義
 */

#ifndef HAMON_VARIANT_VARIANT_NPOS_HPP
#define HAMON_VARIANT_VARIANT_NPOS_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::variant_npos;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [variant.helper], variant helper classes
HAMON_INLINE_VAR HAMON_CONSTEXPR hamon::size_t
variant_npos = static_cast<hamon::size_t>(-1);

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_VARIANT_NPOS_HPP
