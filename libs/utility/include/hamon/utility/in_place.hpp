/**
 *	@file	in_place.hpp
 *
 *	@brief	in_place を定義
 */

#ifndef HAMON_UTILITY_IN_PLACE_HPP
#define HAMON_UTILITY_IN_PLACE_HPP

#include <hamon/config.hpp>

#if HAMON_CXX_STANDARD >= 17

#include <utility>

namespace hamon
{

using std::in_place_t;
using std::in_place;

}	// namespace hamon

#else

namespace hamon
{

struct in_place_t
{
	explicit in_place_t() = default;
};

HAMON_STATIC_CONSTEXPR hamon::in_place_t in_place{};

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_IN_PLACE_HPP
