/**
 *	@file	sorted_equivalent.hpp
 *
 *	@brief	sorted_equivalent の定義
 */

#ifndef HAMON_FLAT_MAP_SORTED_EQUIVALENT_HPP
#define HAMON_FLAT_MAP_SORTED_EQUIVALENT_HPP

#include <hamon/flat_map/config.hpp>

#if defined(HAMON_USE_STD_FLAT_MAP)

#include <flat_map>

namespace hamon
{

using std::sorted_equivalent_t;
using std::sorted_equivalent;

}	// namespace hamon

#else


namespace hamon
{

// 23.6.7 Header <flat_map> synopsis[flat.map.syn]

struct sorted_equivalent_t { explicit sorted_equivalent_t() = default; };
inline constexpr sorted_equivalent_t sorted_equivalent{};

}	// namespace hamon

#endif

#endif // HAMON_FLAT_MAP_SORTED_EQUIVALENT_HPP
