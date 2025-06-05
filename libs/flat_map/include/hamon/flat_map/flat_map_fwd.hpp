/**
 *	@file	flat_map_fwd.hpp
 *
 *	@brief	flat_map の前方宣言
 */

#ifndef HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP
#define HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP

#include <hamon/flat_map/config.hpp>

#if defined(HAMON_USE_STD_FLAT_MAP)

#include <flat_map>

namespace hamon
{

using std::flat_map;

}	// namespace hamon

#else


namespace hamon
{

}	// namespace hamon

#endif

#endif // HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP
