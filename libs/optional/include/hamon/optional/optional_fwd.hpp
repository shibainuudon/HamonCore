/**
 *	@file	optional_fwd.hpp
 *
 *	@brief	optional の前方宣言
 */

#ifndef HAMON_OPTIONAL_OPTIONAL_FWD_HPP
#define HAMON_OPTIONAL_OPTIONAL_FWD_HPP

#include <hamon/optional/config.hpp>

#if defined(HAMON_USE_STD_OPTIONAL)

#include <optional>

namespace hamon
{

using std::optional;

}	// namespace hamon

#else

namespace hamon
{

template <typename T>
class optional;

}	// namespace hamon

#endif

#endif // HAMON_OPTIONAL_OPTIONAL_FWD_HPP
