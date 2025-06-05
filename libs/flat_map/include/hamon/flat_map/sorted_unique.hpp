/**
 *	@file	sorted_unique.hpp
 *
 *	@brief	sorted_unique の定義
 */

#ifndef HAMON_FLAT_MAP_SORTED_UNIQUE_HPP
#define HAMON_FLAT_MAP_SORTED_UNIQUE_HPP

#include <hamon/flat_map/config.hpp>

#if defined(HAMON_USE_STD_FLAT_MAP)

#include <flat_map>

namespace hamon
{

using std::sorted_unique_t;
using std::sorted_unique;

}	// namespace hamon

#else

namespace hamon
{


}	// namespace hamon

#endif

#endif // HAMON_FLAT_MAP_SORTED_UNIQUE_HPP
