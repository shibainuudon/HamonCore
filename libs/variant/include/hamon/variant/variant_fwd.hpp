/**
 *	@file	variant_fwd.hpp
 *
 *	@brief	variant の前方宣言
 */

#ifndef HAMON_VARIANT_VARIANT_FWD_HPP
#define HAMON_VARIANT_VARIANT_FWD_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::variant;

}	// namespace hamon

#else

namespace hamon
{

template <typename... Types>
class variant;

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_VARIANT_FWD_HPP
